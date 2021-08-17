#include "subtitle.h"
#include "globalvalue.h"


Subtitle::Subtitle()
{
    initSubtitle(g_configPath);
}

Subtitle::~Subtitle()
{

}

void Subtitle::initSubtitle(const QString &fileName)
{
    //QFile file(configPath);
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug()<<"Error:Connot read file: "
                <<qPrintable(file.errorString());
        return;
    }

    QXmlStreamReader reader(&file);
    while (!reader.atEnd())
    {

        if (reader.isStartElement()) {
            if (reader.name() == "subtitle") {
                //解析开始：
                while(!reader.atEnd())
                {
                    reader.readNext();
                    if(reader.name()=="str")
                        myStr = reader.readElementText();
                    if(reader.name()=="font")
                        myFont = reader.readElementText();
                    if(reader.name()=="fontSize")
                        myFontSize = reader.readElementText().toInt();
                    if(reader.name()=="textColor")
                        myTextColor = reader.readElementText();
                    if(reader.name()=="bBold")
                    {
                        int temp = reader.readElementText().toInt();
                        if(temp == 1)
                            bMyBold = true;
                        else
                            bMyBold = false;
                    }
                    if(reader.name()=="bOutline")
                    {
                        int temp = reader.readElementText().toInt();
                        if(temp == 1)
                            bMyOutline = true;
                        else
                            bMyOutline = false;
                    }
                    if(reader.name()=="outlineWidth")
                        myOutlineWidth = reader.readElementText().toInt();
                    if(reader.name()=="outlineColor")
                        myOutlineColor = reader.readElementText();
                    if(reader.name()=="bShadow")
                    {
                        int temp = reader.readElementText().toInt();
                        if(temp == 1)
                            bMyShadow = true;
                        else
                            bMyShadow = false;
                    }
                    if(reader.name()=="shadowOffset")
                        myShadowOffset = reader.readElementText().toInt();
                    if(reader.name()=="shadowColor")
                        myShadowColor = reader.readElementText();
                    if(reader.name()=="bBg")
                    {
                        int temp = reader.readElementText().toInt();
                        if(temp == 1)
                            bMyBg = true;
                        else
                            bMyBg = false;
                    }
                    if(reader.name()=="bgColor")
                        myBgColor = reader.readElementText();
                    if(reader.name()=="letterSpace")
                        myLetterSpace = reader.readElementText().toInt();
                    if(reader.name()=="positionX")
                        myPositionX = reader.readElementText().toInt();
                    if(reader.name()=="positionY")
                        myPositionY = reader.readElementText().toInt();
                    if(reader.name()=="paperWidth")
                        myPaperWidth = reader.readElementText().toInt();
                    if(reader.name()=="paperHeight")
                        myPaperHeight = reader.readElementText().toInt();
                    if(reader.name()=="align")
                    {
                        switch (reader.readElementText().toInt())
                        {
                            case 0 : myAlign = align::e_Left;
                            break;
                            case 1 : myAlign = align::e_Center;
                            break;
                            case 2 : myAlign = align::e_Right;
                            break;
                        }
                    }
                }
            }
            else
            {
                reader.raiseError("Not a subtitle sets file");
            }
        }
        else //排除文件头的一些标签
        {
            reader.readNext();
        }
    }
    file.close();
    if (reader.hasError())
    {
        qDebug()<<QObject::tr("Error")<<QObject::tr("Failed to parse file %1").arg(fileName);
        return;

    }
    else if (file.error() != QFile::NoError)
    {
        qDebug()<<QObject::tr("Error")<<QObject::tr("Cannot read file %1").arg(fileName);
        return;
    }
}

bool Subtitle::writeSets(const QString &configPath)
{
    QFile file(configPath);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "Error: Cannot write file: "
                 << qPrintable(file.errorString());
        return false;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("subtitle");
    xmlWriter.writeTextElement("str", myStr);
    xmlWriter.writeTextElement("font", myFont);
    xmlWriter.writeTextElement("fontSize", QString::number(myFontSize));
    xmlWriter.writeTextElement("textColor", myTextColor.name());

    if(bMyBold)
        xmlWriter.writeTextElement("bBold", "1");
    else
        xmlWriter.writeTextElement("bBold", "0");

    if(bMyOutline)
        xmlWriter.writeTextElement("bOutline", "1");
    else
        xmlWriter.writeTextElement("bOutline", "0");
    xmlWriter.writeTextElement("outlineWidth", QString::number(myOutlineWidth));
    xmlWriter.writeTextElement("outlineColor", myOutlineColor.name());

    if(bMyShadow)
        xmlWriter.writeTextElement("bShadow", "1");
    else
        xmlWriter.writeTextElement("bShadow", "0");

    xmlWriter.writeTextElement("shadowOffset", QString::number(myShadowOffset));
    xmlWriter.writeTextElement("shadowColor", myShadowColor.name());

    if(bMyBg)
        xmlWriter.writeTextElement("bBg", "1");
    else
        xmlWriter.writeTextElement("bBg", "0");

    xmlWriter.writeTextElement("bgColor", myBgColor.name());
    xmlWriter.writeTextElement("letterSpace", QString::number(myLetterSpace));

    xmlWriter.writeTextElement("positionX",QString::number(myPositionX));
    xmlWriter.writeTextElement("positionY", QString::number(myPositionY));

    xmlWriter.writeTextElement("paperWidth", QString::number(myPaperWidth));
    xmlWriter.writeTextElement("paperHeight", QString::number(myPaperHeight));

    xmlWriter.writeTextElement("align",QString::number(myAlign));
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();
    if (file.error()) {
        qDebug() << "Error: Cannot write file: "
                 << qPrintable(file.errorString());
        return false;
    }
}

bool Subtitle::debug_writeSets(const QString &configPath)
{
    QFile file(configPath);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "Error: Cannot write file: "
                 << qPrintable(file.errorString());
        return false;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("subtitle");
    xmlWriter.writeTextElement("str", "红伞伞白杆杆吃完一起躺板板");
    xmlWriter.writeTextElement("font", "微软雅黑");
    xmlWriter.writeTextElement("fontSize", "30");
    xmlWriter.writeTextElement("textColor", "#0022ff");
    xmlWriter.writeTextElement("bBold", "0");
    xmlWriter.writeTextElement("bOutline", "0");
    xmlWriter.writeTextElement("outlineWidth", "1");
    xmlWriter.writeTextElement("outlineColor", "#000000");
    xmlWriter.writeTextElement("bShadow", "0");
    xmlWriter.writeTextElement("shadowOffset", "1");
    xmlWriter.writeTextElement("shadowColor", "#888888");
    xmlWriter.writeTextElement("bBg", "0");
    xmlWriter.writeTextElement("bgColor", "#000000");
    xmlWriter.writeTextElement("letterSpace", "100");

    xmlWriter.writeTextElement("positionX", "10");
    xmlWriter.writeTextElement("positionY", "10");

    xmlWriter.writeTextElement("paperWidth", "1920");
    xmlWriter.writeTextElement("paperHeight", "1080");
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();
    if (file.error()) {
        qDebug() << "Error: Cannot write file: "
                 << qPrintable(file.errorString());
        return false;
    }
}
