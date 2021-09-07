#include "exportwidget.h"
#include <QFileDialog>
#include <QMessageBox>
#include "managewin.h"
/*
    函数说明: 构造函数初始化相关变量
*/
CExportWidget::CExportWidget(QString videoName, QStringList vList, int num)
{
    //窗口的基本设置
    QString winTitle = "转码导出视频: " + videoName;
    this->setWindowTitle(winTitle);                 //设置窗体标题
    this->setWindowIcon(QIcon(":/images/icon.jpg"));    //生成窗口图标
    this->setFixedSize(600, 150);                       //设置尺寸

    //初始变量设置
    this->control = CMyController::getInstence();//调用控制器信息
    this->s = CGetSetInfo::Instance();           //调用设置信息单例
    this->fileNameCount = 0;
    this->fileName = videoName;
    this->steps = 0;                           //设置进度条步进值
    this->recode = new CRecodeVideo();         //定义转码器
    this->videoList = vList;
    this->num = num;

    //视频标签
    videoLabel = new QLabel("转码格式: ", this);
    videoLabel->setObjectName(QString::fromUtf8("videoLabel"));
    videoLabel->setGeometry(QRect(60, 22, 65, 16));

    //视频类型下拉框
    videoType = new QComboBox(this);
    videoType->setObjectName(QString::fromUtf8("videoType"));
    videoType->setGeometry(QRect(130, 20, 91, 21));
    videoType->addItem("MP4");
    videoType->addItem("AVI");
    videoType->addItem("h264");

    exportUrl = new QLineEdit(this);
    exportUrl->setObjectName(QString::fromUtf8("exportUrl"));
    exportUrl->setGeometry(QRect(60, 53, 281, 31));

    chooseUrl = new QPushButton(this);
    chooseUrl->setObjectName(QString::fromUtf8("chooseUrl"));
    chooseUrl->setGeometry(QRect(350, 53, 31, 31));
    chooseUrl->setStyleSheet("border-image:url(:/icon/choosefile.png)"); //设置按钮背景

    exportBtn = new QPushButton(this);
    exportBtn->setObjectName(QString::fromUtf8("chooseUrl"));
    exportBtn->setGeometry(QRect(385, 53, 31, 31));
    exportBtn->setStyleSheet("border-image:url(:/icon/publish.png)"); //设置按钮背景

    //进度条设置
    progressBar = new QProgressBar(this);
    progressBar->setObjectName(QString::fromUtf8("progressBar"));
    progressBar->setGeometry(QRect(60, 103, 350, 23));
    progressBar->setValue(0);
    progressBar->setInvertedAppearance(false);
    progressBar->setTextDirection(QProgressBar::TopToBottom);
    progressBar->setWindowModality(Qt::WindowModal);    //设置进度对话框采用模态方式进行，即显示进度的同时，其他窗口将不响应输入信号
    progressBar->show();

    decideBtn = new QPushButton("确定", this);
    decideBtn->setObjectName(QString::fromUtf8("decideBtn"));
    decideBtn->setGeometry(QRect(450, 73, 93, 31));

    //点击文件按钮时,选择文件路径
    connect(chooseUrl, SIGNAL(clicked()), this, SLOT(chooseExportUrl()));
    //点击小箭头时或者确定时,进行转码导出
    connect(exportBtn, SIGNAL(clicked()), this, SLOT(doExport()));
    connect(decideBtn, SIGNAL(clicked()), this, SLOT(doExport()));
    //刷新文件总帧数
    connect(recode, SIGNAL(frameNumFindChange(int)), this, SLOT(flashFrame(int)));
    //文件类型更改时, 后缀
    connect(videoType,SIGNAL(activated(int)),this,SLOT(flashExportUrl(int)));
}

/*
    函数说明: 选择导入的文件
*/
void CExportWidget::chooseExportUrl()
{
    fileFull = QFileDialog::getExistingDirectory(this);//选择目录名
    if(fileFull.length() == 0)
    {
        return;
    }
    QString newUrl = fileFull + '/'+ fileName.mid(0, fileName.length() - 4) + videoType->currentText();
    this->exportUrl->setText(newUrl);
}


/*
    函数说明:进行导出
*/
void CExportWidget::doExport()
{
    int pos = fileName.lastIndexOf('.');
    if(this->exportUrl->text().length() == 0)
    {
        QMessageBox::warning(this, "注意:", "未选择导出的目录", QMessageBox::Yes);
        return;
    }
    else if(fileName.mid(pos+1) == videoType->currentText())
    {
        QMessageBox::warning(this, "注意:", "所选择导出的视频类型与原视频类型一致", QMessageBox::Yes);
        return;
    }
    else
    {
        //导出初始化
        QString orgFile = s.getVideoUrlInfo();
        orgFile += '/' + fileName;
        if(this->recode->openH264File(orgFile) == false)
        {
            QMessageBox::warning(this, "注意:", "初始化该视频失败, 该视频无法转码", QMessageBox::Yes);
            return;
        }
        //获得帧数总数
        this->frameAllNum = this->control->queryVideoFrameNum(fileName.mid(0, 14));
        if(frameAllNum <= 0)
        {
            QMessageBox::warning(this, "注意:", "导出视频总帧数读取失败, 进度条无法开启", QMessageBox::Yes);
            //开始导出
            this->recode->tranceToFormat(exportUrl->text());
        }
        else
        {
            //开始进度条
            progressBar->show();
            //开始导出
            this->recode->tranceToFormat(exportUrl->text());
        }
        //导出完成
        QMessageBox:: StandardButton result = QMessageBox::information(this, "注意:", "导出完成,是否返回播放窗口", QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
        if (result == QMessageBox::Yes)
        {
            //返回播放窗口
            CPlayVideo* playWin = new CPlayVideo(this->videoList, this->num);
            playWin->show();
        }
        this->close();
    }
}


/*
    函数说明: 刷新文件总帧数
*/
void CExportWidget::flashFrame(int curFrameNum)
{
    //设置步进值
    this->steps = (curFrameNum / this->frameAllNum)*100;
    //更新进度条步进值
    progressBar->setValue(this->steps);
    //更新窗口
    this->update();
}


/*
    函数说明:刷新导出URL文件
*/
void CExportWidget::flashExportUrl(int)
{
    if(this->exportUrl->text().length() != 0 && fileName.length() != 0)
    {
        QString newUrl = fileFull + '/'+ fileName.mid(0, fileName.length() - 4) + videoType->currentText();
        this->exportUrl->setText(newUrl);
    }
}

