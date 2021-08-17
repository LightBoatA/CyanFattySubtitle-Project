#ifndef GLOBALVALUE_H
#define GLOBALVALUE_H

#include <QString>

extern int g_screenWidth;
extern int g_screenHeight;

extern double g_adjustPix;//文字背景位置矫正系数

extern double g_textXratio;
extern double g_textYratio;
extern double g_lineXratio;
extern double g_lineYratio;


extern float g_screenToWindowRatio;

extern QString g_configPath;//配置文件路径
extern QString g_defaultSetsPath;//默认预设文件路径

extern QString g_defaultBgImgFileName;//默认背景图片
extern QString g_userBgImgFileName;//用户选择的背景图片

extern QString g_subtitleDefaultText;
extern QString g_textPastTips;
extern QString g_setNameTips;


#endif // GLOBALVALUE_H
