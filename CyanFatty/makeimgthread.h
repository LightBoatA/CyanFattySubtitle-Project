#ifndef MAKEIMGTHREAD_H
#define MAKEIMGTHREAD_H

#include <QThread>
#include <QMutex>

class Subtitle;
class QPaintDevice;
class QPainter;
class MakeImgThread : public QThread
{
    Q_OBJECT
public:
    MakeImgThread(QWidget* parent = nullptr);

    void stop(bool s);

    void initSubtitle(Subtitle* st,const QString& text,const QString& titleName,const QString& dirPath);

signals:

    /*进度向主线程传递*/
    void progress(int value);

public:
    volatile bool stopped;
    QMutex mutex;

private:
    void makePNG(const QString &word,const int i);
    void drawText(QPaintDevice * painterDevice,const QString & word);

private:

    QString     outputDirPath;      //输出路径
    QString     subtitleName;       //输出名称
    QString     subtitleText;       //要处理的全部字符串
    Subtitle *  subtitle;           //字幕对象（包含各种参数设置）

protected:
    void run() override;
};

#endif // MAKEIMGTHREAD_H
