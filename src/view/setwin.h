#ifndef CSETWIN_H
#define CSETWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QWidget>
#include <QAction>
#include <QStringList>
#include <QListWidgetItem>
#include <QVBoxLayout>
#include <controller/myController.h>

class CSetWin : public QWidget
{
    Q_OBJECT
public:
    CSetWin();
private:
    CMyController * control;        //控制器单例

    QFont font, font1, font2;       //字体的相关设置

    //标签控件相关
    QLabel *titleLab;               //标题标签
    QLabel *videoUrlLab;            //视频存储位置标签
    QLabel *photoUrlLab;            //图片存储位置标签
    QLabel *timeIntervalLab;        //采集时间间隔标签
    QLabel *camLab;                 //摄像头配置标签

    //编辑框控件相关
    QLineEdit *videoUrlEdit;        //视频存储位置编辑框
    QLineEdit *photoUrlEdit;        //图片存储位置编辑框
    QLineEdit *timeIntervalEdit;    //采集时间间隔编辑框

    //下拉框列表
    QComboBox  *comboList;          //获取摄像头下拉列表窗口

    //按钮控件相关
    QPushButton *decideBtn;         //确定按钮
    QPushButton *cancelBtn;         //取消按钮

    //图标控件相关
    QAction *videoActionIcon;       //拍摄视频的Icon
    QAction *photoActionIcon;       //图片Icon
    QAction *timeActionIcon;        //时间Icon
    QAction *camActionIcon;         //摄像头Icon
    QAction *videoAddPathAction;    //添加保存视频的URL
    QAction *photoAddPathAction;    //添加保存图片的URL
    QAction *nullActionIcon;        //设置空的Icon

    QStringList* camInfo;           //定义存储摄像头名称的信息

    deque<string> dSetInfo;         //存储数据库当前的配置信息

private:
    void getSetInfo();              //得到设置信息
    void getCamName();              //获取摄像头名称
    void listWin();                 //生成摄像头列表
    QString filePath();             //选择文件路径

signals:
    void setOver();                 //发射设置完毕信号

public slots:
    void saveDate();                //存储数据
    void chooseVideoUrl(bool);      //选择视频文件存储路径
    void choosePhotoUrl(bool);      //选择照片文件存储路径
    void returnMainWin();           //返回主界面
};

#endif // CSETWIN_H
