#include "labelbg.h"
#include "globalvalue.h"
#include "labeltext.h"
#include "subtitle.h"
#include <QtWidgets>

LabelBg::LabelBg(QWidget* parent)
        :QLabel(parent)
        ,bResizeScreen(false)
        ,bCenter(true)
        ,bHelpLine(false)
{



}

void LabelBg::paintEvent(QPaintEvent *)
{
    // 指定绘图设备为本窗口
    QPainter painter(this);
    // 启用抗锯齿(反走样)
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHints(QPainter::TextAntialiasing, true);
    // 指定要绘制的图片
    painter.save();


    double labelWidth = width();
    double labelHeight = height();



    //比例系数
    double ratioH = labelHeight/subtitle->myPaperHeight;
    double ratioW = labelWidth/subtitle->myPaperWidth;

    //double ratio = 1;
    //先缩小：哪边小以谁为准
    if(ratioH < ratioW)//以竖边为准
    {
        m_bgHeight = labelHeight;
        m_bgWidth = subtitle->myPaperWidth * ratioH;
        m_ratio = ratioH;
    }
    else
    {
        m_bgWidth = labelWidth;
        m_bgHeight = subtitle->myPaperHeight * ratioW;
        m_ratio = ratioW;
    }

    //控制背景位置
    //int x,y;
    m_bgX = (labelWidth-m_bgWidth)/2;
    m_bgY = (labelHeight-m_bgHeight)/2;
    QPixmap pixmap(g_userBgImgFileName);
    pixmap = pixmap.scaled(m_bgWidth,m_bgHeight,Qt::IgnoreAspectRatio);

    painter.drawPixmap(m_bgX,m_bgY,pixmap);

    //画辅助线

    if(bHelpLine)
    {
        QPen line;
        line.setColor(QColor("#191919"));
        line.setWidth(1);
        painter.setPen(line);


        int lineX = m_bgX +  m_bgWidth * g_textXratio;
        int lineY = m_bgY + m_bgHeight * g_textYratio;
        int lineW = m_bgWidth * (1.0-g_textXratio*2);
        int lineH = m_bgHeight * (1.0-g_textYratio*2);
        painter.drawRect(lineX,lineY,lineW,lineH);//里圈

        lineX = m_bgX +  m_bgWidth * g_lineXratio;
        lineY = m_bgY + m_bgHeight * g_lineYratio;
        lineW = m_bgWidth * (1.0-g_lineXratio*2);
        lineH = m_bgHeight * (1.0-g_lineYratio*2);
        painter.drawRect(lineX,lineY,lineW,lineH);//外圈
    }


    //画文字
    //文字位置
    //字体
    QFont myFont;
    myFont.setFamily(subtitle->myFont);

    //字体大小比例控制

    //myFont.setPointSize();

    myFont.setPointSize((subtitle->myFontSize)*m_ratio);
    //字体粗细
    myFont.setBold(subtitle->bMyBold);

    //设置间距
    myFont.setLetterSpacing(QFont::PercentageSpacing,subtitle->myLetterSpace);
    painter.setFont(myFont);

    //文字位置计算
    QFontMetricsF fm(myFont);
    m_textWidth = fm.width(subtitle->myStr);
    m_textHeight = fm.height();
    //int hei = myFont.pointSize();

    //基线以上的高度
    double textBaseHeight = fm.ascent();
    double textBaseDown = fm.descent();

    //int textX,textY;

    if(bResizeScreen)
    {
        bResizeScreen = false;
        m_textY = m_bgHeight * (1.0-g_textYratio) + m_bgY;

        //写入字幕数据
        subtitle->myPositionY = ((m_textY-m_bgY)*(subtitle->myPaperHeight))/(double)m_bgHeight;
    }
    else
    {
        m_textY = ((subtitle->myPositionY)*m_bgHeight)/((double)(subtitle->myPaperHeight))+m_bgY+textBaseHeight;
    }
    //x位置处理
    if(subtitle->myAlign==subtitle->align::e_Left)
    {
        //左对齐
        m_textX = m_bgWidth * g_textXratio + m_bgX;
    }
    else if(subtitle->myAlign==subtitle->align::e_Center)
    {
        //居中
        m_textX = (m_bgWidth-m_textWidth)/2 + m_bgX;
    }
    else
    {
        //右对齐
        int textAndRightSpace = m_bgWidth * g_textXratio + m_textWidth;
        m_textX =( m_bgWidth-textAndRightSpace)+ m_bgX;
    }

    if(bChangeHposition)
    {
        bChangeHposition = false;
        subtitle->myPositionX = ((m_textX-m_bgX)*(subtitle->myPaperWidth))/(double)m_bgWidth;
    }

    //QFontMetricsF fm(myFont);
    //背景
    if(subtitle->bMyBg)
    {
        painter.setPen(subtitle->myBgColor);
        painter.setBrush(subtitle->myBgColor);

        //背景矫正
        painter.drawRect(m_textX-(myFont.pointSize()*g_adjustPix),
                         m_textY-textBaseHeight,
                         m_textWidth,
                         m_textHeight+(myFont.pointSize()*g_adjustPix));
        //painter.drawRect(m_textX,m_textY-textBaseHeight+textBaseDown,m_textWidth,m_textHeight);
    }
    //阴影
    if(subtitle->bMyShadow)
    {


        //基线以上的高度
        //double textHeight = fm.ascent();
        painter.setPen(subtitle->myShadowColor);
        painter.setBrush(subtitle->myShadowColor);
        QPointF p(m_textX+(subtitle->myShadowOffset)*m_ratio,m_textY+(subtitle->myShadowOffset)*m_ratio);
        painter.drawText(p,subtitle->myStr);
    }
    //描边
    if(subtitle->bMyOutline)
    {

        QPainterPath path;
        //注意文字的位置点设置
        path.addText(QPointF(m_textX, m_textY), painter.font(), subtitle->myStr);

        QPen pen;
        pen.setWidth((subtitle->myOutlineWidth)*m_ratio);
        pen.setColor(subtitle->myOutlineColor);
        painter.setPen(pen);
        painter.setBrush(subtitle->myOutlineColor);
        //绘制黑边
        painter.drawPath(path);
    }







    painter.setPen(subtitle->myTextColor);

    painter.drawText(m_textX,m_textY,subtitle->myStr);
    painter.restore();
    painter.end();
}



void LabelBg::setSubtitle(Subtitle *st)
{
    subtitle = st;
}

void LabelBg::setIfResizeScreen(bool r)
{
    bResizeScreen = r;

}

void LabelBg::setIfDrawHelpLine(bool r)
{
    bHelpLine = r;
}

void LabelBg::setHpositionChange(bool r)
{
    bChangeHposition = r;
}



void LabelBg::writeToSubtitlePosition()
{
    //写入字幕数据
    subtitle->myPositionX = ((m_textX-m_bgX)*(subtitle->myPaperWidth))/(double)m_bgWidth;
    subtitle->myPositionY = ((m_textY-m_bgY)*(subtitle->myPaperHeight))/(double)m_bgHeight;
}
