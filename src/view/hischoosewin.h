#ifndef CHISCHOOSE_H
#define CHISCHOOSE_H

#include <QDateEdit>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QCalendarWidget>
#include <QStackedLayout>
#include <QWidget>
#include "controller/getsetinfo.h"
#include "controller/filetool.h"
#include "controller/dateedit.h"
#include "playvideowin.h"
#include "pagewidget.h"
#include "menulistwidget.h"

class CHisChoose : public QWidget
{
    Q_OBJECT
public:
    CHisChoose();                //历史窗口构造函数
    QStringList& getVideoList(); //得到视频列表
    QStringList& getCoverList(); //照片封面

private:
    QFont font, font1;            //字体设置
    QLabel *titleLab;             //标题设置

    QPushButton *calendarBtn;     //日历按钮设置
    QPushButton *showAllVideoBtn; //显示全部图片

    CDateEdit *dateEdit;          //日历编辑框设置
    QCalendarWidget *calendarWin; //日历界面的设置

    QStackedLayout *stackedLayout;//分页布局
    QListWidget *listWidget;      //滚动界面设置
    CPageWidget* pageWidget;      //翻页按钮设置
    CMenuListWidget* menuListWidget; //菜单按钮

    CFileTool* f ;                //调用文件单例
    CMyController* control;       //调用获取控制器单例文件
    CGetSetInfo s;                //调用获取设置信息单例

    QString uId;                  //登录用户名
    QList<QString> fileInfo;      //存储视频文件信息
    QStringList coverList;        //照片封面
    QStringList videoList;        //视频历史

    bool getPic;                  //保存图片
    int fileNameCount;            //定义搜索到的文件信息

public slots:

    void listWinAddItem(int num);    //更新Item类
    void getAllFile();               //获取控件和视频的地址列表
    void getTimeFile(QDate curTime); //查找是否有相同日期的文件
    void searchVideo();              //点击搜寻按钮搜索视频
    void playVideo(QListWidgetItem*);//播放视频窗口
    void exitFun(QListWidgetItem*);  //退出

};
#endif // CHISCHOOSE_H
