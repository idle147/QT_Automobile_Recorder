#ifndef CEXPORTWIDGET_H
#define CEXPORTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include "controller/getsetinfo.h"
#include "controller/recodevideo.h"


/****************************
       该类属于导出小窗口
****************************/
class CExportWidget: public QWidget
{
    Q_OBJECT
public:
    CExportWidget(QString videoName, QStringList vList, int num);   //导出窗口构造函数

private:
    QLabel *videoLabel;          //视频标签
    QComboBox *videoType;        //视频类型

    QLineEdit *exportUrl;        //导出URL

    QProgressBar *progressBar;   //进度条处理

    QPushButton *chooseUrl;      //选择URL

    QPushButton *exportBtn;      //导出确认按钮
    QPushButton *decideBtn;      //决定导出按钮

private:
    CGetSetInfo s;                //调用获取设置信息单例
    CMyController* control;       //调用获取控制器单例文件

    CRecodeVideo* recode;         //定义转码器

    QString fileName;             //获得选择导出的文件名
    QString fileFull;
    QStringList videoList;
    int num;
    int fileNameCount;            //定义文件的数量
    int frameAllNum;              //获取总帧数
    int steps;                    //更新进度条的步进值

public slots:
    void chooseExportUrl();       //选择导出的文件
    void doExport();              //进行导出
    void flashFrame(int curFrameNum); //更新总帧数
    void flashExportUrl(int);     //刷新导出的文件
};

#endif // CEXPORTWIDGET_H
