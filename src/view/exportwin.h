#ifndef CEXPORTWIN_H
#define CEXPORTWIN_H
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <QTimer>

#include "controller/getsetinfo.h"
#include "controller/filetool.h"
#include "controller/dateedit.h"
#include "controller/recodevideo.h"
#include "menulistwidget.h"

/********************************
    函数说明: 该类属于导出窗口大类
 ******************************/
class CExportWin: public QWidget
{
    Q_OBJECT
public:
    CExportWin();

private:
    QFont font, font1;            //字体设置
    QLabel *titleLabel;           //题目标签
    QLabel *videoLabel;           //视频标签

    QComboBox *videoType;         //视频类型
    QLineEdit *exportUrl;         //导出URL

    QProgressBar *progressBar;    //进度条处理

    QPushButton *chooseUrl;       //选择URL按钮
    QPushButton *calendarBtn;     //日历按钮设置
    QPushButton *exportBtn;       //导出确认按钮(图标)
    QPushButton *decideBtn;       //导出确认按钮(文字)

    CMenuListWidget* menuListWidget; //菜单按钮

    QPushButton *showAllVideoBtn; //展示全部视频按钮

    QListWidget *listWidget;      //导出窗口类
    CDateEdit *dateEdit;          //日期编辑器
    QCalendarWidget *calendarWin; //日历界面的设置


private:
    CFileTool* f ;                //调用文件单例

    CGetSetInfo s;                //调用获取设置信息单例
    CMyController* control;       //调用获取控制器单例文件
    CRecodeVideo* recode;         //定义转码器

    QString uId;                  //登录用户名
    QString fileName;             //获得选择导出的文件名

    QList<QString> fileInfo;      //存储视频文件信息
    QStringList coverList;        //照片封面
    QStringList videoList;        //视频历史

    QString fileFull;

    int fileNameCount;            //定义文件的数量
    int frameAllNum;              //获取总帧数
    int steps;                    //更新进度条的步进值

public slots:
    void getAllFile();                //获取控件和视频的地址列表
    void getTimeFile(QDate curTime);  //查找是否有相同日期的文件
    void searchVideo();               //点击搜寻按钮搜索视频
    void chooseVideo(QListWidgetItem*);//显示播放界面
    void chooseExportUrl();           //选择导出的文件
    void doExport();                  //进行导出
    void flashFrame(int curFrameNum); //更新总帧数
    void flashExportUrl(int);         //刷新导出的文件
    void exitFun(QListWidgetItem*);   //返回上个界面

};

#endif // CEXPORTWIN_H
