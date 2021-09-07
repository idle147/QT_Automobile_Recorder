#ifndef CPictureWin_H
#define CPictureWin_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QWidget>
#include <QtWidgets/QCalendarWidget>
#include "controller/getsetinfo.h"
#include "controller/dateedit.h"
#include "controller/filetool.h"
#include "menulistwidget.h"

class CPictureWin : public QWidget
{
    Q_OBJECT
public:
    CPictureWin();

private:
    QFont font, font1;            //字体设置
    QLabel *titleLab;             //标题设置
    QPushButton *calendarBtn;     //日历按钮设置
    QPushButton *showBtn;         //展示界面
    QPushButton *showAllPicBtn;   //显示全部图片
    CDateEdit *dateEdit;          //日历编辑框设置
    QCalendarWidget *calendarWin; //日历界面的设置

    QListWidget *listWidget;      //滚动界面设置
    CMenuListWidget* menuListWidget; //菜单按钮

    CGetSetInfo s;                //调用单例
    CMyController* control;       //调用获取控制器单例文件

    QString uId;                  //登录用户名
    QList<QString> fileInfo;      //存储视频文件信息
    QStringList photoList;        //照片截图

    int fileNameCount;            //定义文件的数量

public slots:
    void getAllFile();                 //得到全部文件信息
    void getTimeFile(QDate curTime);   //得到用户下的时间约束条件(查找是否有相同日期的文件)
    void searchPic();                  //搜寻图片
    void amplifyPicture(QListWidgetItem*);  //放大图片
    void shinkPicture();               //缩小图片
    void exitFun(QListWidgetItem*);    //返回上个界面
};

#endif // CPictureWin_H
