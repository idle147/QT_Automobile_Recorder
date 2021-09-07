#include "setwin.h"
#include "managewin.h"
#include <QList>
#include <QCameraInfo>
#include <QFileInfo>
#include <QFileDialog>
#include <QStyledItemDelegate>
#include <controller/ctool.h>
#include <QMessageBox>
#include <QDir>

/*
    函数说明:相关信息初始化
*/
CSetWin::CSetWin()
{

    //相关数值初始化
    camInfo = new QStringList();
    this->control = CMyController::getInstence();//控制器单例设置

    //打开Qss文件
    QString qss = "";
    CFileTool::readQSS(":/QSS/setwin.qss", qss);

    this->setWindowTitle(tr("基本信息设置"));    //设置窗体标题
    this->setWindowIcon(QIcon(":/images/icon.jpg"));    //生成窗口图标
    this->setFixedSize(901, 541);              //设置尺寸

    //Action初始化
    this->videoActionIcon = new QAction(this);
    this->photoActionIcon = new QAction(this);
    this->timeActionIcon = new QAction(this);
    this->camActionIcon = new QAction(this);
    this->videoAddPathAction = new QAction(this);
    this->photoAddPathAction = new QAction(this);
    this->nullActionIcon = new QAction(this);

    //设置图标
    this->videoActionIcon->setIcon(QIcon(":/icon/video.png"));
    this->photoActionIcon->setIcon(QIcon(":/icon/photo.png"));
    this->timeActionIcon->setIcon(QIcon(":/icon/clock.png"));
    this->camActionIcon->setIcon(QIcon(":/icon/camera.png"));
    this->videoAddPathAction->setIcon(QIcon(":/icon/queue_add.png"));
    this->photoAddPathAction->setIcon(QIcon(":/icon/queue_add.png"));

    //设置字体的类型--微软雅黑字体
    font.setFamily(QString::fromUtf8("msyh"));
    font1.setFamily(QString::fromUtf8("msyh"));
    font2.setFamily(QString::fromUtf8("msyh"));

    //设置字体的大小
    font.setPointSize(18);
    font1.setPointSize(15);
    font2.setPointSize(14);

    //标题控件相关设置
    titleLab = new QLabel("设     置", this);
    titleLab->setObjectName(QString::fromUtf8("titleLab"));
    titleLab->setGeometry(QRect(410, 30, 135, 41));
    titleLab->setFont(font);

    //视频存储位置标签设置
    videoUrlLab = new QLabel("视频存储位置： ", this);
    videoUrlLab->setObjectName(QString::fromUtf8("videoUrlLab"));
    videoUrlLab->setGeometry(QRect(70, 114, 181, 41));
    videoUrlLab->setFont(font1);
    //视频存储位置编辑框的设置
    videoUrlEdit = new QLineEdit(this);
    videoUrlEdit->setObjectName(QString::fromUtf8("videoUrlEdit"));
    videoUrlEdit->setGeometry(QRect(240, 110, 571, 51));
    videoUrlEdit->addAction(videoActionIcon, QLineEdit::LeadingPosition);//头部添加icon
    videoUrlEdit->addAction(videoAddPathAction, QLineEdit::TrailingPosition);//尾部加入"添加文件"Action
    videoUrlEdit->setClearButtonEnabled(true); //添加删除的按钮
    videoUrlEdit->setPlaceholderText("请输入视频存储位置地址");
    videoUrlEdit->setFont(font1);

    //视频存储位置标签的设置
    photoUrlLab = new QLabel("照片存储位置： ", this);
    photoUrlLab->setObjectName(QString::fromUtf8("photoUrlLab"));
    photoUrlLab->setGeometry(QRect(70, 184, 181, 41));
    photoUrlLab->setFont(font1);

    //照片存储位置编辑框的设置
    photoUrlEdit = new QLineEdit(this);
    photoUrlEdit->setObjectName(QString::fromUtf8("photoUrlEdit"));
    photoUrlEdit->setGeometry(QRect(240, 180, 571, 51));
    photoUrlEdit->addAction(photoActionIcon, QLineEdit::LeadingPosition);//头部添加icon
    photoUrlEdit->addAction(photoAddPathAction, QLineEdit::TrailingPosition);//尾部加入"添加文件"Action
    photoUrlEdit->setClearButtonEnabled(true);//添加删除的按钮
    photoUrlEdit->setPlaceholderText("请输入照片存储位置地址");
    photoUrlEdit->setFont(font1);

    //采集间隔时间标签的设置
    timeIntervalLab = new QLabel("采集时间间隔： ", this);
    timeIntervalLab->setObjectName(QString::fromUtf8("timeIntervalLab"));
    timeIntervalLab->setGeometry(QRect(70, 254, 191, 41));
    timeIntervalLab->setFont(font1);

    //采集间隔时间编辑框的设置
    timeIntervalEdit = new QLineEdit(this);
    timeIntervalEdit->setObjectName(QString::fromUtf8("timeIntervalEdit"));
    timeIntervalEdit->setGeometry(QRect(240, 250, 571, 51));
    timeIntervalEdit->addAction(timeActionIcon, QLineEdit::LeadingPosition);//头部添加icon
    timeIntervalEdit->addAction(nullActionIcon, QLineEdit::TrailingPosition);//尾部加入"空"Action
    timeIntervalEdit->setFont(font1);
    timeIntervalEdit->setMaxLength(3);
    timeIntervalEdit->setPlaceholderText("请输入视频保存间隔(1~999分钟)");
    QRegExp regx("[0-9]+$");//只能输入数字
    QValidator* validator=new QRegExpValidator(regx, timeIntervalEdit);
    timeIntervalEdit->setValidator(validator);

    //摄像头标签位置的设置
    camLab = new QLabel("摄像头配置：", this);
    camLab->setObjectName(QString::fromUtf8("camLab"));
    camLab->setGeometry(QRect(90, 324, 161, 41));
    camLab->setFont(font1);
    //摄像头下拉框的设置
    comboList = new QComboBox(this);
    comboList->setObjectName(QString::fromUtf8("comboList"));
    comboList->setGeometry(QRect(240, 320, 571, 51));
    comboList->setFont(font1);
    //设置样式表格式
    QStyledItemDelegate *delegate = new QStyledItemDelegate();
    comboList->setItemDelegate(delegate);
    comboList->setStyleSheet(qss);

    //获取摄像头信息
    getCamName();
    getSetInfo();

    //确定按钮的相关设置
    decideBtn = new QPushButton("确定", this);
    decideBtn->setObjectName(QString::fromUtf8("decideBtn"));
    decideBtn->setGeometry(QRect(210, 420, 141, 61));
    decideBtn->setFont(font2);

    //取消按钮的相关设置
    cancelBtn = new QPushButton("取消", this);
    cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
    cancelBtn->setGeometry(QRect(610, 420, 141, 61));
    cancelBtn->setFont(font2);

    //槽函数连接
    connect(photoAddPathAction, SIGNAL(triggered(bool)), this, SLOT(choosePhotoUrl(bool))); //点击小箭头时,选择文件路径
    connect(videoAddPathAction, SIGNAL(triggered(bool)), this, SLOT(chooseVideoUrl(bool))); //点击小箭头时,选择文件路径
    connect(decideBtn, SIGNAL(clicked()), this, SLOT(saveDate())); //点击确认进入保存配置界面
    connect(cancelBtn, SIGNAL(clicked()), this, SLOT(returnMainWin())); //点击确认进入保存配置界面
}


/*
    函数说明:获取设置信息
*/
void CSetWin::getSetInfo()
{
    int res = this->control->querySetTable(this->dSetInfo);
    if(res == IsFind)
    {   //设置编辑框为设置的值
        videoUrlEdit->setText(QString::fromStdString(dSetInfo[1]));
        photoUrlEdit->setText(QString::fromStdString(dSetInfo[2]));
        timeIntervalEdit->setText(QString::fromStdString(dSetInfo[3]));
        //遍历获取当前摄像头同名的索引值
        for(int i = 0; i< camInfo->size();i++)
        {
            if(camInfo->at(i) == QString::fromStdString(dSetInfo[4]))
            {
                //找到同名的
                comboList->setCurrentIndex(i);
                break;
            }
        }
    }
}

/*
    函数说明:获取摄像头名称
*/
void CSetWin::getCamName()
{
    camInfo->clear();
    //可用的摄像头
    QList<QCameraInfo> cameralist = QCameraInfo::availableCameras();
    //循环打印可用的摄像头
    for(int i=0; i < cameralist.count(); i++)
    {
        this->camInfo->append(cameralist.at(i).description());//将摄像头名字存到QList容器内
    }
    //添加图标控件
    QIcon Icon = QIcon(":/icon/camera_2.png");
    //遍历添加摄像头数据
    for(int i=0;i < camInfo->length(); i++)
    {
        //通过 QListWidgetItem添加文本以及Icon数据的
        comboList->addItem(Icon, QString("%1").arg(camInfo->at(i)));
    }
}


QString CSetWin::filePath()
{
    QString file_full, file_name, file_path;
    QFileInfo fi;

    file_full = QFileDialog::getExistingDirectory(this);//选择目录名
    fi = QFileInfo(file_full);
    file_name = fi.fileName();//选择到的名字
    file_path = fi.absolutePath();//选择到的路径
    return file_full;
}


void CSetWin::saveDate()
{
    if(this->timeIntervalEdit->text().toInt() == 0)
    {
        QMessageBox::information(nullptr, "tips:","时间间隔不可设置为0", QMessageBox::Yes);
        return;
    }
    int res = this->control->setInfo(videoUrlEdit->text(), photoUrlEdit->text(), timeIntervalEdit->text(), comboList->currentText());
    if(res == optSuccess)
    {
        //判断文件是否存在
        CGetSetInfo s = CGetSetInfo::Instance();
        if(!CFileTool::judgeExit(s.getVideoUrlInfo()))
        {
            QMessageBox::information(nullptr, "tips:","视频存储文件路径不存在, 请重新设置", QMessageBox::Yes);
            videoUrlEdit->clear();
            return;
        }
        if(!CFileTool::judgeExit(s.getPhotoUrlInfo()))
        {
            QMessageBox::information(nullptr, "tips:","图片存储文件路径不存在, 请重新设置", QMessageBox::Yes);
            photoUrlEdit->clear();
            return;
        }
        QMessageBox::information(nullptr, "tips:","设置成功, 返回主界面（若程序无法正常运行，请重启）", QMessageBox::Yes);
        if(CManageWin::getFlag() == false)
        {
            //加入窗口
            CManageWin::getInstence()->addWin();
        }
        else
        {
            //重启一下main窗口
            CManageWin::getInstence()->rebootMainWin();
        }
        returnMainWin();
    }
    else
    {
        QMessageBox::information(nullptr, "tips:","设置失败, 请检查", QMessageBox::Yes);
    }

}


void CSetWin::choosePhotoUrl(bool)
{
    this->photoUrlEdit->setText(filePath());
}


void CSetWin::returnMainWin()
{
    this->hide();
    CManageWin::getInstence()->findWin(e_mainWin)->show();
}


void CSetWin::chooseVideoUrl(bool)
{
    this->videoUrlEdit->setText(filePath());
}
