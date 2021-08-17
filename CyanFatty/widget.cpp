#include "widget.h"
#include "ui_widget.h"
#include "globalvalue.h"
#include "textparse.h"
#include "makeimgthread.h"
#include "subtitle.h"
#include "aboutwidget.h"


#include <QtWidgets>
#include <QPainter>
#include <QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    //字幕对象
    subtitle = new Subtitle;
    //subtitle->initSubtitle("");
    ui->setupUi(this);

    //绘制屏幕参数传入
    ui->label_screen->setSubtitle(subtitle);

    //线程
    makeImgThread = new MakeImgThread(this);

    connect(makeImgThread,SIGNAL(progress(int)),this,SLOT(setProgress(int)));

    //屏幕图片
    m_backGroundImage = new QImage();

    //[关于软件]窗口
    m_aboutWidget = nullptr;

    initUI();

    connect(ui->radioButton_alignLeft,SIGNAL(clicked(bool)),this,SLOT(onAlignButtonGroupChanged()));
    connect(ui->radioButton_alignCenter,SIGNAL(clicked(bool)),this,SLOT(onAlignButtonGroupChanged()));
    connect(ui->radioButton_alignRight,SIGNAL(clicked(bool)),this,SLOT(onAlignButtonGroupChanged()));

    //布局设置
    ui->splitter_3->setStretchFactor(1,1);//最外层：右伸展
    ui->splitter->setStretchFactor(0,1);//内层：右伸展
    //窗口设置
    setWindowTitle("好胖友字幕");
    setWindowIcon(QIcon(":/imgs/icon.png"));

}


void Widget::initUI()
{
    /*****************按预设文件设置组件显示值*****************/
    //字体系列
    ui->fontComboBox->setCurrentFont(QFont(subtitle->myFont));

    //字体大小
    ui->spinBox_FongSize->setValue(subtitle->myFontSize);

    //粗体
    if(subtitle->bMyBold)
        ui->checkBox_fontBold->setCheckState(Qt::Checked);
    else
        ui->checkBox_fontBold->setCheckState(Qt::Unchecked);

    //描边
    if(subtitle->bMyOutline)
        ui->checkBox_outline->setCheckState(Qt::Checked);
    else
        ui->checkBox_outline->setCheckState(Qt::Unchecked);

    ui->spinBox_outlineWidth->setValue(subtitle->myOutlineWidth);

    //阴影
    if(subtitle->bMyShadow)
        ui->checkBox_shadow->setCheckState(Qt::Checked);
    else
        ui->checkBox_shadow->setCheckState(Qt::Unchecked);

    ui->spinBox_shadowOffset->setValue(subtitle->myShadowOffset);

    //文字背景
    if(subtitle->bMyBg)
        ui->checkBox_textBg->setCheckState(Qt::Checked);
    else
        ui->checkBox_textBg->setCheckState(Qt::Unchecked);
    ui->spinBox_letterSpace->setValue(subtitle->myLetterSpace);

    //屏幕尺寸
    ui->lineEdit_width->setText(QString::number(subtitle->myPaperWidth));
    ui->lineEdit_height->setText(QString::number(subtitle->myPaperHeight));

    //示例文字
    ui->lineEdit->setText(subtitle->myStr);

    //粘贴提示区
    ui->lineEdit_srcText->setPlaceholderText(g_textPastTips);

    //字幕生成区提示
    ui->textEdit_subtitleText->setPlaceholderText(g_subtitleDefaultText);
    //不可编辑
    ui->textEdit_subtitleText->setEnabled(false);

    //字幕名称输入提示
    ui->lineEdit_subtitleName->setPlaceholderText(g_setNameTips);

    //设置颜色选择按钮的颜色
    ui->pushButton_fontColor->setStyleSheet("background-color:"+subtitle->myTextColor.name()+";");
    ui->pushButton_outlineColor->setStyleSheet("background-color:"+subtitle->myOutlineColor.name()+";");
    ui->pushButton_shadowColor->setStyleSheet("background-color:"+subtitle->myShadowColor.name()+";");
    ui->pushButton_textBgColor->setStyleSheet("background-color:"+subtitle->myBgColor.name()+";");

    //文字位置
    updateTextPositionSpinBox();
    updateTextPositionSlider();

    //水平对齐方式
    buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(ui->radioButton_alignLeft,0);
    buttonGroup->addButton(ui->radioButton_alignCenter,1);
    buttonGroup->addButton(ui->radioButton_alignRight,2);

    switch ((int)(subtitle->myAlign))
    {
        case 0:
        ui->radioButton_alignLeft->setChecked(true);
        break;
        case 1:
        ui->radioButton_alignCenter->setChecked(true);
        break;
        case 2:
        ui->radioButton_alignRight->setChecked(true);
        break;
    }
}

Widget::~Widget()
{
    subtitle->writeSets(g_configPath);
    delete ui;
    delete subtitle;
    delete m_backGroundImage;


}

void Widget::paintEvent(QPaintEvent *event)
{

    ui->label_screen->update();
    updateTextPositionSpinBox();
    updateTextPositionSlider();

}

void Widget::closeEvent(QCloseEvent *event)
{
    if(m_aboutWidget)
        delete m_aboutWidget;
}






void Widget::updateTextPositionSpinBox()
{

    ui->spinBox_positionY->setRange(1,subtitle->myPaperHeight);
    ui->spinBox_positionY->setValue(subtitle->myPositionY);

}

void Widget::updateTextPositionSlider()
{
    ui->horizontalSlider_y->setRange(1,subtitle->myPaperHeight);
    ui->horizontalSlider_y->setValue(subtitle->myPositionY);
}

void Widget::updateScreenSizeLineEdit()
{
    ui->lineEdit_width->setText(QString::number(subtitle->myPaperWidth));
    ui->lineEdit_height->setText(QString::number(subtitle->myPaperHeight));
}



void Widget::resizeScreen()
{
    //给变量赋值
    subtitle->myPaperWidth = ui->lineEdit_width->text().toInt();
    subtitle->myPaperHeight = ui->lineEdit_height->text().toInt();

    //文字位置重置
    ui->label_screen->setIfResizeScreen(true);
    ui->label_screen->update();
    update();


}


void Widget::setProgress(int value)
{
    ui->progressBar->setValue(value);
    if(value==100)
    {
        QMessageBox::information(this,"提示","输出完成");
        ui->progressBar->setValue(0);

        //输出中文路径
        QDesktopServices::openUrl(QUrl::fromLocalFile(m_outputDirPath));

        ui->pushButton_pngSequence->setText("字幕输出");
    }

}

void Widget::onAlignButtonGroupChanged()
{
    switch(buttonGroup->checkedId())
   {
        case 0:
            subtitle->myAlign = subtitle->align::e_Left;
        break;
        case 1:
            subtitle->myAlign = subtitle->align::e_Center;
        break;
        case 2:
            subtitle->myAlign = subtitle->align::e_Right;
        break;
   }
   ui->label_screen->setHpositionChange(true);
}






void Widget::on_pushButton_outlineColor_clicked()
{
    QColor fontColor = QColorDialog::getColor(subtitle->myOutlineColor);
    if(fontColor.isValid())
    {
        subtitle->myOutlineColor = fontColor;
        qobject_cast<QPushButton*>(sender())->setStyleSheet("background-color:"+fontColor.name()+";");
    }
}

void Widget::on_checkBox_shadow_stateChanged(int arg1)
{
    if(arg1==Qt::Checked)
        subtitle->bMyShadow = true;
    else
        subtitle->bMyShadow = false;
}

void Widget::on_pushButton_shadowColor_clicked()
{
    QColor fontColor = QColorDialog::getColor(subtitle->myShadowColor);
    if(fontColor.isValid())
    {
        subtitle->myShadowColor = fontColor;
        qobject_cast<QPushButton*>(sender())->setStyleSheet("background-color:"+fontColor.name()+";");
    }
}

void Widget::on_pushButton_pngSequence_clicked()
{
    QPushButton * button = qobject_cast<QPushButton*>(sender());
    if(button->text()=="字幕输出")
    {

        QString judgeStr = ui->textEdit_subtitleText->toPlainText();
        if(judgeStr.isEmpty())
        {
            QMessageBox::warning(this,"提示","当前无字幕，请先粘贴文本");
            return;
        }
        if(ui->lineEdit_subtitleName->text().isEmpty())
        {
            QMessageBox::warning(this,"提示","请输入字幕文件名称");
            ui->lineEdit_subtitleName->setFocus();
            return;
        }
        QString dirpath = QFileDialog::getExistingDirectory(this,"选择目录","./",QFileDialog::ShowDirsOnly);
        if(!dirpath.isEmpty())
        {
            m_outputDirPath = dirpath;
            makeImgThread->initSubtitle(subtitle,ui->textEdit_subtitleText->toPlainText(),
                                        ui->lineEdit_subtitleName->text(),dirpath);
            makeImgThread->start();
            makeImgThread->stop(false);

            button->setText("终止输出");
        }
    }
    else//停止输出
    {
        makeImgThread->stop(true);
        QMessageBox::information(this,"提示","已终止输出");

        ui->progressBar->setValue(0);
        button->setText("字幕输出");
    }


}

void Widget::on_pushButton_outputFileDir_clicked()
{

}

void Widget::on_lineEdit_srcText_textChanged(const QString &arg1)
{
    if(!arg1.isEmpty())
    {
        QString showStr;
        TextParse::Parse(showStr,arg1);

        ui->textEdit_subtitleText->setText(showStr);
        ui->textEdit_subtitleText->setEnabled(true);
    }
    else
    {
        ui->textEdit_subtitleText->setText("");
        ui->textEdit_subtitleText->setEnabled(false);
    }

}

void Widget::on_checkBox_fontBold_stateChanged(int arg1)
{
    if(arg1==Qt::Checked)
        subtitle->bMyBold = true;
    else
        subtitle->bMyBold = false;
}



void Widget::on_pushButton_userSize_clicked()
{
    resizeScreen();

}

void Widget::on_lineEdit_height_returnPressed()
{
    resizeScreen();
}

void Widget::on_lineEdit_width_returnPressed()
{
    resizeScreen();
}

void Widget::on_spinBox_FongSize_valueChanged(int arg1)
{
    subtitle->myFontSize = arg1;
}

void Widget::on_spinBox_letterSpace_valueChanged(int arg1)
{
    subtitle->myLetterSpace = arg1;
}

void Widget::on_spinBox_outlineWidth_valueChanged(int arg1)
{
    subtitle->myOutlineWidth = arg1;
}

void Widget::on_spinBox_shadowOffset_valueChanged(int arg1)
{
    subtitle->myShadowOffset = arg1;
}

void Widget::on_fontComboBox_currentFontChanged(const QFont &f)
{
    subtitle->myFont = f.family();
}

void Widget::on_lineEdit_textChanged(const QString &arg1)
{
    subtitle->myStr = arg1;
}

void Widget::on_spinBox_positionX_valueChanged(int arg1)
{
    subtitle->myPositionX = arg1;
    //ui->horizontalSlider_x->setValue(arg1);
}

void Widget::on_spinBox_positionY_valueChanged(int arg1)
{
    subtitle->myPositionY = arg1;
    ui->horizontalSlider_y->setValue(arg1);
}


//是否居中
void Widget::on_checkBox_center_stateChanged(int arg1)
{
    //居中
    if(arg1==Qt::Checked)
    {
        ui->label_screen->update();
        updateTextPositionSpinBox();
        updateTextPositionSlider();
    }
    else
    {
    }

}

void Widget::on_horizontalSlider_x_valueChanged(int value)
{
    subtitle->myPositionX = value;
    updateTextPositionSpinBox();
    ui->label_screen->update();
}

void Widget::on_horizontalSlider_y_valueChanged(int value)
{
    subtitle->myPositionY = value;
    updateTextPositionSpinBox();
    ui->label_screen->update();
}

void Widget::on_checkBox_textBg_stateChanged(int arg1)
{
    if(arg1==Qt::Checked)
    {
        subtitle->bMyBg = true;
    }
    else
    {
        subtitle->bMyBg = false;
    }
}

void Widget::on_pushButton_textBgColor_clicked()
{
    QColor color = QColorDialog::getColor(subtitle->myBgColor);
    if(color.isValid())
    {
        subtitle->myBgColor = color;
        qobject_cast<QPushButton*>(sender())->setStyleSheet("background-color:"+color.name()+";");
    }
}

void Widget::on_pushButton_loadBackGroundImg_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "选择文件：",
                                                    "/",
                                                    "Image Files(*.jpg *.png *.bmp *.pgm *.pbm)");
    if(!fileName.isEmpty())
    {
        if(m_backGroundImage->load(fileName))
        {
            //hasBGImage = true;
            g_userBgImgFileName = fileName;
            //drawScreen();
            subtitle->myPaperWidth = m_backGroundImage->width();
            subtitle->myPaperHeight = m_backGroundImage->height();
            updateScreenSizeLineEdit();
            //文字位置重置
            ui->label_screen->setIfResizeScreen(true);
            ui->label_screen->update();

        }
    }
}

void Widget::on_pushButton_loadBackGroundImg_2_clicked()
{
    g_userBgImgFileName = g_defaultBgImgFileName;
}

void Widget::on_checkBox_helpLine_stateChanged(int arg1)
{
    if(arg1==Qt::Checked)
    {
        ui->label_screen->setIfDrawHelpLine(true);
    }
    else
    {
        ui->label_screen->setIfDrawHelpLine(false);
    }
}

void Widget::on_pushButton_fontColor_clicked()
{
    QColor fontColor = QColorDialog::getColor(subtitle->myTextColor);
    if(fontColor.isValid())
    {
        subtitle->myTextColor = fontColor;
        qobject_cast<QPushButton*>(sender())->setStyleSheet("background-color:"+fontColor.name()+";");
    }
}

void Widget::on_checkBox_outline_stateChanged(int arg1)
{
    if(arg1==Qt::Checked)
    {
        subtitle->bMyOutline = true;
    }
    else
        subtitle->bMyOutline = false;
}

void Widget::on_pushButton_saveSets_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,"请选择文件夹：",".","Config Files (*.xml)");
    if(!fileName.isEmpty())
    {
        if(subtitle->writeSets(fileName))
        {
            QMessageBox::information(this,"提示","保存成功！");
        }
        else
        {
            QMessageBox::warning(this,"提示","保存失败！");
        }
    }
}


void Widget::on_pushButton_importSets_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"请选择文件夹：",".","Config Files (*.xml)");
    if(!fileName.isEmpty())
    {
        subtitle->initSubtitle(fileName);
        initUI();
    }
}

void Widget::on_pushButton_clicked()
{
    subtitle->initSubtitle(g_defaultSetsPath);
    initUI();
}

void Widget::on_pushButton_about_clicked()
{
    //如果已经创建了窗口，先释放掉（防止关了又不断重新建/内存无法释放）
    if(m_aboutWidget!=nullptr)
    {
        delete m_aboutWidget;
    }
    m_aboutWidget = new AboutWidget();
    m_aboutWidget->show();

}
