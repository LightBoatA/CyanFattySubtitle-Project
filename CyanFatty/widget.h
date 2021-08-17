#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class QButtonGroup;
class MakeImgThread;
class Subtitle;
class AboutWidget;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void paintEvent(QPaintEvent *event) override;

    void closeEvent(QCloseEvent *event) override;

private:

    /*根据字幕对象更新界面*/
    void initUI();

    /*更新位置spinBox*/
    void updateTextPositionSpinBox();

    /*更新位置slider*/
    void updateTextPositionSlider();

    /*更新屏幕尺寸文本框*/
    void updateScreenSizeLineEdit();


public slots:

    /*屏幕尺寸更改处理*/
    void resizeScreen();

    /*设置进度条*/
    void setProgress(int value);

    /*对齐方式单选框处理*/
    void onAlignButtonGroupChanged();


private slots:

    void on_pushButton_outlineColor_clicked();

    void on_pushButton_shadowColor_clicked();

    void on_pushButton_pngSequence_clicked();

    void on_pushButton_outputFileDir_clicked();

    void on_pushButton_userSize_clicked();

    void on_pushButton_textBgColor_clicked();

    void on_pushButton_loadBackGroundImg_clicked();

    void on_pushButton_loadBackGroundImg_2_clicked();

    void on_pushButton_fontColor_clicked();

    void on_pushButton_saveSets_clicked();

    void on_pushButton_importSets_clicked();

    void on_pushButton_clicked();

    void on_pushButton_about_clicked();


    void on_checkBox_outline_stateChanged(int arg1);

    void on_checkBox_shadow_stateChanged(int arg1);

    void on_checkBox_fontBold_stateChanged(int arg1);

    void on_checkBox_textBg_stateChanged(int arg1);

    void on_checkBox_helpLine_stateChanged(int arg1);

    void on_checkBox_center_stateChanged(int arg1);


    void on_lineEdit_srcText_textChanged(const QString &arg1);

    void on_lineEdit_height_returnPressed();

    void on_lineEdit_width_returnPressed();

    void on_lineEdit_textChanged(const QString &arg1);



    void on_spinBox_FongSize_valueChanged(int arg1);

    void on_spinBox_letterSpace_valueChanged(int arg1);

    void on_spinBox_outlineWidth_valueChanged(int arg1);

    void on_spinBox_shadowOffset_valueChanged(int arg1);

    void on_spinBox_positionX_valueChanged(int arg1);

    void on_spinBox_positionY_valueChanged(int arg1);


    void on_fontComboBox_currentFontChanged(const QFont &f);


    void on_horizontalSlider_x_valueChanged(int value);

    void on_horizontalSlider_y_valueChanged(int value);



private:
    Ui::Widget *ui;

    MakeImgThread * makeImgThread;          //输出字幕线程
    Subtitle *      subtitle;               //字幕对象
    QButtonGroup *  buttonGroup;            //单选按钮组
    QImage *        m_backGroundImage;      //屏幕图片
    QString         m_subtitleName;         //字幕文件输出名称
    QString         m_outputDirPath;        //字幕文件输出路径

    AboutWidget*    m_aboutWidget;          //[关于软件]窗口



};
#endif // WIDGET_H
