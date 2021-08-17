#include "textparse.h"
#include <QRegExp>

TextParse::TextParse()
{

}

void TextParse::Parse(QString& resText, const QString &srcText)
{
    //wordList = srcText.replace(",","");
    resText = "";
    QStringList words;
    words = srcText.split(QRegExp("，|。|？|！|、|-|——|……|；|;| |:|…|」|「|“|”|\n|\t"));

    //修改字体检查框
    QStringList::iterator it;
    int i = 0;
    //QString showStr;
    for(it = words.begin();it!=words.end();++it,i++)
    {
        //makePNG(*it,i);
        //if((*it)=="\n")
        if(!(*it).isEmpty())
        {
            resText.append(*it);
            resText.append("\n");

        }

    }
    //wordList = srcText.split("，");
}

void TextParse::splitLines(QStringList &list, const QString &text)
{
    if(text.isEmpty())
        return;
    list = text.split("\n");
}
