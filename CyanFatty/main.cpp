#include "widget.h"

#include <QApplication>
#include <QFile>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":/qss/cyan.qss");
    file.open(QFile::ReadOnly);
    a.setStyleSheet(file.readAll());
    Widget w;
    w.show();

    //窗口居中
    w.move ((QApplication::desktop()->width() - w.width())/2,
            (QApplication::desktop()->height() - w.height())/2);
    return a.exec();
}
