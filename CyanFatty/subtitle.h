#ifndef MYWORD_H
#define MYWORD_H

#include <QtWidgets>

/*字幕*/
class Subtitle
{
public:
    Subtitle();
    ~Subtitle();
public:

    /*对齐方式*/
    enum align
    {
        e_Left = 0,
        e_Center,
        e_Right
    };

    QString myStr;
    QString myFont;             //字体系列名称
    int     myFontSize;         //字体大小
    QColor  myTextColor;        //字体颜色
    bool    bMyBold;            //是否加粗
    bool    bMyOutline;         //是否描边
    int     myOutlineWidth;     //描边宽度
    QColor  myOutlineColor;     //描边颜色
    bool    bMyShadow;          //是否加阴影
    int     myShadowOffset;     //阴影偏移值
    QColor  myShadowColor;      //阴影颜色
    bool    bMyBg;              //是否加背景
    QColor  myBgColor;          //背景颜色
    int     myLetterSpace;      //字符间距

    int     myPositionX;        //绝对位置x
    int     myPositionY;        //绝对位置Y

    int     myPaperWidth;       //纸张绝对像素宽
    int     myPaperHeight;      //纸张绝对像素高

    align   myAlign;            //文字对齐方式

public:

    /*从配置文件读入预设*/
    void initSubtitle(const QString& fileName);

    /*将设置写入配置文件*/
    bool writeSets(const QString& configPath);

    /*开发调试用于首次填写xml文件*/
    bool debug_writeSets(const QString& configPath);

};

#endif // MYWORD_H
