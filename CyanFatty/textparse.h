#ifndef TEXTPARSE_H
#define TEXTPARSE_H
#include <QStringList>

/*文本解析*/
class TextParse
{
public:
    TextParse();

    /*文本去标点和空行*/
    static void Parse(QString& resText,const QString& srcText);

    /*文本分行*/
    static void splitLines(QStringList& list,const QString& text);
};

#endif // TEXTPARSE_H
