#ifndef LABELBG_H
#define LABELBG_H

#include <QLabel>

class LabelText;
class Subtitle;

/*绘制屏幕和样例字幕*/
class LabelBg : public QLabel
{
    Q_OBJECT
public:
    LabelBg(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent *) override;

    void setSubtitle(Subtitle* st);

    /*是否更新了屏幕尺寸*/
    void setIfResizeScreen(bool r);

    /*是否画辅助线*/
    void setIfDrawHelpLine(bool r);

    /*垂直位置是否改变*/
    void setHpositionChange(bool r);

private:

    /*将位置改变写入到字幕对象*/
    void writeToSubtitlePosition();

private:

    int         m_bgX;                 //背景图片x
    int         m_bgY;                 //背景图片y
    int         m_bgWidth;             //背景图片宽
    int         m_bgHeight;            //背景图片高

    double      m_ratio;               //label/背景图片实际尺寸

    int         m_textX;               //文字x
    int         m_textY;               //文字y
    int         m_textWidth;           //文字宽
    int         m_textHeight;          //文字高


    bool        bResizeScreen;          //重置屏幕尺寸，文字位置需要重新设置
    bool        bCenter;                //是否保持文字居中
    bool        bChangeHposition;       //是否改变了文字的垂直位置
    bool        bHelpLine;              //是否画辅助线

    Subtitle*   subtitle;               //字幕对象
};

#endif // LABELBG_H
