#include "makeimgthread.h"
#include "textparse.h"
#include "subtitle.h"
#include "globalvalue.h"

#include <QtWidgets>
#include <QImage>
MakeImgThread::MakeImgThread(QWidget* parent)
                :QThread(parent)
{
    stopped = true;
}

void MakeImgThread::stop(bool s)
{
    mutex.lock();
    stopped = s;
    mutex.unlock();
}


void MakeImgThread::initSubtitle(Subtitle *st, const QString &text, const QString &titleName, const QString &dirPath)
{
    mutex.lock();
    subtitle = st;
    subtitleText = text;
    subtitleName = titleName;
    outputDirPath = dirPath;
    mutex.unlock();
}


void MakeImgThread::makePNG(const QString &word, const int i)
{
    QImage image(QSize(subtitle->myPaperWidth,subtitle->myPaperHeight),QImage::Format_ARGB32);
    drawText(&image,word);
    QString name = outputDirPath +"/"+ subtitleName +"-"+QString::number(i)+".png";
    image.save(name,"PNG",-1);

}

void MakeImgThread::drawText(QPaintDevice *painterDevice, const QString &word)
{
    QPainter painter(painterDevice);
    // 启用抗锯齿(反走样)
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHints(QPainter::TextAntialiasing, true);
    // 指定要绘制的图片
    painter.save();

    //字体
    QFont myFont;
    myFont.setFamily(subtitle->myFont);

    //字体大小
    myFont.setPointSize(subtitle->myFontSize);

    //字体粗细
    myFont.setBold(subtitle->bMyBold);

    //字体间距
    myFont.setLetterSpacing(QFont::PercentageSpacing,subtitle->myLetterSpace);

    //设置字体
    painter.setFont(myFont);


    //计算x的位置
    QFontMetrics fm(myFont);
    int textWidth = fm.width(word);
    int textHeight = fm.height();

    double textBaseHeight = fm.ascent();
    int x,y;
    y = subtitle->myPositionY+textBaseHeight;
    if(subtitle->myAlign == subtitle->align::e_Left)//左对齐
    {
        x = subtitle->myPaperWidth * g_textXratio;
    }
    else if(subtitle->myAlign == subtitle->align::e_Center)//居中
    {
        x =( subtitle->myPaperWidth - textWidth)/2;
    }
    else//右对齐
    {
        int textAndRightSpace = textWidth + subtitle->myPaperWidth * g_textXratio;
        x = subtitle->myPaperWidth - textAndRightSpace;
    }

    //背景
    if(subtitle->bMyBg)
    {
        painter.setPen(subtitle->myBgColor);
        painter.setBrush(subtitle->myBgColor);
        painter.drawRect(x-(myFont.pointSize()*g_adjustPix),
                         subtitle->myPositionY,
                         textWidth+(myFont.pointSize()*g_adjustPix),
                         textHeight+(myFont.pointSize()*g_adjustPix));
    }
    //阴影
    if(subtitle->bMyShadow)
    {
        QFontMetricsF fm(myFont);

        //基线以上的高度
        //double textHeight = fm.ascent();
        painter.setPen(subtitle->myShadowColor);
        painter.setBrush(subtitle->myShadowColor);
        QPointF p(x+subtitle->myShadowOffset,y+subtitle->myShadowOffset);
        painter.drawText(p,word);
    }

    //描边
    if(subtitle->bMyOutline)
    {

        QPainterPath path;
        //注意文字的位置点设置
        path.addText(QPointF(x, y), painter.font(), word);

        QPen pen;
        pen.setWidth(subtitle->myOutlineWidth);
        pen.setColor(subtitle->myOutlineColor);
        painter.setPen(pen);
        painter.setBrush(subtitle->myOutlineColor);
        //绘制黑边
        painter.drawPath(path);
    }



    painter.setPen(subtitle->myTextColor);

    painter.drawText(x,y,word);
    painter.restore();
    painter.end();
}

void MakeImgThread::run()
{
    while (1)
    {
        if(stopped)
             return;

        QStringList words;

        TextParse::splitLines(words,subtitleText);

        QStringList::iterator it;
        int i = 0;

        for(it = words.begin();it!=words.end();++it,i++)
        {
            mutex.lock();
            if(stopped)
            {
                mutex.unlock();
                return;
            }
            else
            {
                makePNG(*it,i);
                    emit progress(((i+1)*100)/words.size());
                mutex.unlock();
            }

        }

        stop(true);
    }
}
