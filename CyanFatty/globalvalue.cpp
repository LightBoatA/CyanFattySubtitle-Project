#include "globalvalue.h"

int g_screenWidth = 1920;
int g_screenHeight = 1080;

double g_adjustPix = 0.2;

double g_textYratio = 0.08;
double g_textXratio = 0.03;
double g_lineXratio = 0.01;
double g_lineYratio = 0.025;

float g_screenToWindowRatio = 0.7;


QString g_configPath = "./configs/preSet.xml";
QString g_defaultSetsPath = "./configs/defaultSet.xml";


QString g_defaultBgImgFileName = ":/imgs/bgImg_blue.jpg";//默认背景图片
QString g_userBgImgFileName = ":/imgs/bgImg_blue.jpg";//用户选择的背景图片

QString g_subtitleDefaultText = "文本粘贴后将自动生成...";
QString g_textPastTips = "粘贴文本到此处";
QString g_setNameTips = "请输入字幕文件名称";
