#include "aboutwidget.h"
#include "ui_aboutwidget.h"
#include <QIcon>

AboutWidget::AboutWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutWidget)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap(":/imgs/about.jpg"));
    ui->label->setScaledContents(true);

    setWindowTitle("软件信息");
    setWindowIcon(QIcon(":/imgs/icon.png"));
}

AboutWidget::~AboutWidget()
{
    delete ui;
}
