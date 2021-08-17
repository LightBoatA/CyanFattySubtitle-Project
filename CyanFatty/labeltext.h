#ifndef LABELTEXT_H
#define LABELTEXT_H

#include <QLabel>

class Subtitle;

/*用于显示示例字幕*/
class LabelText : public QLabel
{
    Q_OBJECT
public:

    Subtitle * subtitle;

    LabelText(QWidget* parent,Subtitle* st);

    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;

    void paintEvent(QPaintEvent *) override;

    //void
private:
    void drawText(QPaintDevice * painterDevice,const QString & word);
};

#endif // LABELTEXT_H
