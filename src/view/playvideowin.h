#ifndef CPLAYVIDEO_H
#define CPLAYVIDEO_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <QListWidget>
#include <QSlider>
#include <QDateTime>
#include <QTimer>
#include <QProgressBar>
#include "controller/decodevideo.h"
#include "view/managewin.h"

class CPlayVideo : public QWidget
{
    Q_OBJECT
public:
    CPlayVideo(QStringList videoList, int countNum);
private:
    QWidget *preWidget;         //上一个窗口
    QWidget* mpShadeWindow;     //遮罩窗口

    QPushButton *videoBtn;      //视频播放窗口
    QPushButton *lastBtn;       //上一个视频按钮
    QPushButton *videoPlayFileBtn;       //文件清单按钮
    QPushButton *saveBtn;       //保存按钮
    QPushButton *playBtn;       //播放视频按钮
    QPushButton *nextBtn;       //下一个视频按钮
    QPushButton *photoBtn;      //截图按钮
    QLabel *photoLab;           //拍照提示
    QPushButton *changeSpeedBtn;      //速度按钮
    QPushButton *exitBtn;       //返回按钮

    QProgressBar *playProgress;  //播放器进度条

    QListWidget *fileListWidget;//文件上拉狂
    QString uId;                //设置当前登录用户
    QStringList videoList;      //播放的文件清单
    QImage img;                 //设置每一帧的图像

    QTimer *tHider;              //用以隐藏拍照提示
    QTimer *tShink;             //启动定时器使遮罩窗户关闭

    QDateTime curDateTime;      //当前系统的时间

    CGetSetInfo s;              //调用单例
    CMyController* control;     //调用控制器信息
    CDecodeVideo * playDecode;      //解码器对象

    QString url;
    int num;                    //定义当前播放的视频位置
    int fileNameCount;          //定义文件夹文件数量
    int AllTime;                //设定总时长
    int currentTime;            //设置当前的播放时间
    bool getPic;                //保存图片
    bool listWidgetFlag;        //下拉窗口标识符
    bool stop;                  //是否播放

private:
    void paintEvent(QPaintEvent *);     //绘制视频的播放窗口
    void changeVideo();                 //设置播放视频
    void listWinAddItem();              //下拉窗口添加控件

signals:
    void saveVideoName(QString VideoName);  //发射视频名称

public slots:
    void isPlay();                      //是否播放
    void stopPlay();                    //停止播放视频
    void exitWin();                     //退出窗口
    void saveScreenShoot();             //保存屏幕截图
    void saveVideo();                   //保存视频
    void reciveSlot(QImage img);        //更新槽函数的图片
    void prePlay();                     //播放上一段视频
    void nextPlay();                    //播放下一段视频
    void changeSpeed();                 //改变倍速
    void showListWidget();              //展示下拉窗
    void chooseFile(QListWidgetItem*);  //选择文件播放
    void hideMpShadeWin();              //产生一闪而过的遮罩窗口
    void hidePhotoWin();                //隐藏拍照窗口
    void flashFrame(int);               //更新进度条
};

#endif // CPLAYVIDEO_H
