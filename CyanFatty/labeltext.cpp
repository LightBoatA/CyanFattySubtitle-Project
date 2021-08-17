#include "labeltext.h"
#include "subtitle.h"


LabelText::LabelText(QWidget* parent,Subtitle* st)
        :QLabel(parent),
         subtitle(st)
{

}

void LabelText::mousePressEvent(QMouseEvent *ev)
{

}

void LabelText::mouseMoveEvent(QMouseEvent *ev)
{

}

void LabelText::paintEvent(QPaintEvent *)
{
    drawText(this,"我发誓要做老大");
}

void LabelText::drawText(QPaintDevice *painterDevice, const QString &word)
{
    const QRect rectangle = QRect(200, 200, 500, 60);
    QRect boundingRect;

    QPainter *painter = new QPainter(painterDevice);

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->setRenderHints(QPainter::TextAntialiasing, true);

    painter->save();

    //字体
    QFont myFont;
    myFont.setFamily(subtitle->myFont);

    myFont.setPixelSize(subtitle->myFontSize);
    //字体粗细
    myFont.setBold(subtitle->bMyBold);
    //设置间距
    myFont.setLetterSpacing(QFont::PercentageSpacing,subtitle->myLetterSpace);
    painter->setFont(myFont);
    //描边
    if(subtitle->bMyOutline)
    {
        QFontMetricsF fm(myFont);

//      //基线以上的高度
        double textHeight = fm.ascent();
        //获取文字位置
        double textX = rectangle.x();
        double textY = rectangle.y()+textHeight;
        QPainterPath path;
        //注意文字的位置点设置
        path.addText(QPointF(textX, textY), painter->font(), word);

        QPen pen;
        pen.setWidth(subtitle->myOutlineWidth);
        pen.setColor(subtitle->myOutlineColor);
        painter->setPen(pen);
        painter->setBrush(subtitle->myOutlineColor);
        //绘制黑边
        painter->drawPath(path);
    }

    //阴影
    if(subtitle->bMyShadow)
    {
        QFontMetricsF fm(myFont);

//      //基线以上的高度
        double textHeight = fm.ascent();
        //QPen pen;
        //pen.setWidth(m_shadowOffset);
        //pen.setColor(m_shadowColor);
        painter->setPen(subtitle->myShadowColor);
        painter->setBrush(subtitle->myShadowColor);
        QPointF p(rectangle.x()+subtitle->myShadowOffset,rectangle.y()+textHeight+subtitle->myShadowOffset);
        painter->drawText(p,word);
    }
    //设置字体颜色
    painter->setPen(subtitle->myTextColor);
    qDebug()<<"颜色："<<painter->pen().color().name();

    //QColor c()


    painter->drawText(rectangle,0,word,&boundingRect);


    painter->restore();
    painter->end();
    update();
}
