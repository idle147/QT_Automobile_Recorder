#ifndef CMAINWIN_H
#define CMAINWIN_H

#include <QObject>
#include <QWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include <QListWidgetItem>
#include <QTimer>
#include "QMessageBox"
#include "controller/decodevideo.h"
#include "controller/getsetinfo.h"
#include "managewin.h"

class CMainWin : public QWidget
{
    Q_OBJECT
public:
    CMainWin();
    ~CMainWin();
    void playCamera();                  //播放视像头信号

    //变量相关设置
private:
    QFont font, font1;                  //字体设置
    bool openFlag;                      //设置判断是否打开的标志
    bool getPic;                        //拍照标识符
    QImage img;                         //设置每一帧的图像
    CDecodeVideo * decode;              //解码器对象
    CEncodevideo* encode;               //编码器对象
    QString url;                        //视频播放地址
    int imgNum;                         //定义播放的图片数量

    //控件相关设置
private:
    QWidget* mpShadeWindow;             //遮罩窗口
    QPushButton *videoBtn;              //视频按钮
    QLabel *titleLab;                   //标题标签
    QLabel *dateLab;                    //日期标签框
    QLabel *recordLab;                  //正在录制lab
    QLabel *photoLab;                   //拍照logo

    QLineEdit* loginEdit;               //登录标签
    QPushButton *loginBtn;              //登录按钮
    QPushButton *toolBtn;               //工具按钮

    QListWidget *setlistWin;            //工具列表清单
    QTimer *timer;                      //启动定时器用以更新系统的时间
    QTimer *tshink;                     //启动定时器使遮罩窗户关闭
    QTimer *tHider;                     //启动定时器,以隐藏视频的标签

    QDateTime curDateTime;              //当前系统的时间
    CGetSetInfo s;                      //调用单例
    CMyController* control;             //调用控制器信息

private:
    void addItem();                     //下拉框添加相关控件
    void paintEvent(QPaintEvent *);     //绘制视频的播放窗口
    bool judgeLogin2();                 //判断是否需要登录(非注销)

public slots:
    bool judgeLogin();                     //判断是否登录(注销)
    void updateTime();                     //更新当前系统时间
    void openSetList();                    //打开设置界面
    void reciveSlot(QImage img);           //更新槽函数的图片
    void doOption(QListWidgetItem*);       //点击不同的Item执行不同的功能
    void savePic();                        //拍照
    void hideMpShadeWin();                 //产生一闪而过的遮罩窗口
    void hidePhotoWin();                 //让图片标签隐藏起来

};

#endif // CMAINWIN_H
