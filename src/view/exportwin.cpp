#include "exportwin.h"
#include <QMessageBox>
#include <QFileDialog>

/*
    函数说明:导出文件初始化
*/
CExportWin::CExportWin()
{  
    //窗口的基本设置
    this->setWindowTitle(tr("转码导出"));                 //设置窗体标题
    this->setWindowIcon(QIcon(":/images/icon.jpg"));    //生成窗口图标
    this->setFixedSize(640, 600);                       //设置尺寸

    //初始变量设置
    this->control = CMyController::getInstence();//调用控制器信息
    this->s = CGetSetInfo::Instance();           //调用设置信息单例
    this->f = CFileTool::getInstence();          //调用单例
    this->fileNameCount = 0;
    this->fileName = "";
    this->steps = 0;                           //设置进度条步进值
    this->recode = new CRecodeVideo();         //定义转码器

    //打开Qss文件
    QString qss = "";
    CFileTool::readQSS(":/QSS/picAndVideo.qss", qss);

    //设置字体大小设置
    font.setPointSize(18);
    font1.setPointSize(12);

    //设置字体类型设置
    font.setFamily(QString::fromUtf8("msyh"));
    font1.setFamily(QString::fromUtf8("msyh"));

    //设置标题
    titleLabel = new QLabel("转码导出",this);
    titleLabel->setGeometry(QRect(260, 30, 151, 41));
    titleLabel->setFont(font);

    //视频标签
    videoLabel = new QLabel("转码格式: ", this);
    videoLabel->setObjectName(QString::fromUtf8("videoLabel"));
    videoLabel->setGeometry(QRect(60, 451, 65, 16));
    videoLabel->setFont(font1);

    //视频类型下拉框
    videoType = new QComboBox(this);
    videoType->setObjectName(QString::fromUtf8("videoType"));
    videoType->setGeometry(QRect(130, 450, 91, 21));
    videoType->addItem("MP4");
    videoType->addItem("AVI");
    videoType->addItem("h264");

    exportUrl = new QLineEdit(this);
    exportUrl->setObjectName(QString::fromUtf8("exportUrl"));
    exportUrl->setGeometry(QRect(60, 485, 281, 31));

    chooseUrl = new QPushButton(this);
    chooseUrl->setObjectName(QString::fromUtf8("chooseUrl"));
    chooseUrl->setGeometry(QRect(350, 485, 31, 31));
    chooseUrl->setStyleSheet("border-image:url(:/icon/choosefile.png)"); //设置按钮背景

    exportBtn = new QPushButton(this);
    exportBtn->setObjectName(QString::fromUtf8("chooseUrl"));
    exportBtn->setGeometry(QRect(385, 485, 31, 31));
    exportBtn->setStyleSheet("border-image:url(:/icon/publish.png)"); //设置按钮背景

    //进度条设置
    progressBar = new QProgressBar(this);
    progressBar->setObjectName(QString::fromUtf8("progressBar"));
    progressBar->setGeometry(QRect(60, 520, 350, 23));
    progressBar->setValue(0);
    progressBar->setInvertedAppearance(false);
    progressBar->setTextDirection(QProgressBar::TopToBottom);
    progressBar->setWindowModality(Qt::WindowModal);    //设置进度对话框采用模态方式进行，即显示进度的同时，其他窗口将不响应输入信号
    progressBar->hide();

    listWidget = new QListWidget(this);
    listWidget->setObjectName(QString::fromUtf8("videoItem"));
    listWidget->setGeometry(QRect(0, 115, 580, 315));
    listWidget->setSortingEnabled(true);            //设置自动排序
    listWidget->setCurrentRow(0);                   //设置当前选择行为第0行
    listWidget->setViewMode(QListView::IconMode);   //设置为图标模式
    listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//设置垂直滚动条常开
    listWidget->setStyleSheet(qss);
    listWidget->setIconSize(QSize(180, 180));

    //日历窗口的设置
    calendarWin = new QCalendarWidget(this);
    calendarWin->setObjectName(QString::fromUtf8("calendarWin"));
    calendarWin->setGeometry(QRect(50, 130, 50, 50));
    calendarWin->setMinimumDate(QDate(2000, 1, 1));
    calendarWin->setMaximumDate(QDate::currentDate().addDays(0));
    calendarWin->setFirstDayOfWeek(Qt::Monday);
    calendarWin->setGridVisible(true);
    calendarWin->setHorizontalHeaderFormat(QCalendarWidget::ShortDayNames);
    calendarWin->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    calendarWin->setNavigationBarVisible(true);
    calendarWin->setDateEditEnabled(true);
    calendarWin->setDateEditAcceptDelay(1500);

    //日期编辑框控件的设置
    dateEdit = new CDateEdit(this);
    dateEdit->setNullable(true);
    dateEdit->toSetNUll(true);
    dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
    dateEdit->setDisplayFormat("yyyy-MM-dd");
    dateEdit->setGeometry(QRect(75, 80, 150, 31));
    dateEdit->setFont(font1);
    dateEdit->setMinimumDate(calendarWin->minimumDate());
    dateEdit->setMaximumDate(calendarWin->maximumDate());
    dateEdit->setCalendarPopup(true);
    dateEdit->setCalendarWidget(calendarWin);
    dateEdit->setStyleSheet(qss);

    //搜索按钮的设置
    calendarBtn = new QPushButton(this);
    calendarBtn->setObjectName(QString::fromUtf8("calendarBtn"));
    calendarBtn->setGeometry(QRect(227, 81, 28, 28));//QRect(49, 107, 32, 32)
    calendarBtn->setStyleSheet("border-image:url(:/icon/search.png)"); //设置按钮背景

    //显示全部按钮
    showAllVideoBtn = new QPushButton(this);
    showAllVideoBtn->setObjectName(QString::fromUtf8("showAllPicBtn"));
    showAllVideoBtn->setGeometry(QRect(44, 81, 28, 28));//QRect(321, 108, 29, 29)
    showAllVideoBtn->setStyleSheet("border-image:url(:/icon/video-gallery2.png)"); //设置按钮背景

    //菜单下拉清单
    menuListWidget = new CMenuListWidget(this);
    menuListWidget->setObjectName(QString::fromUtf8("showAllPicBtn"));
    menuListWidget->setGeometry(QRect(568, 104, 95, 507));//QRect(321, 108, 29, 29)

    decideBtn = new QPushButton("确定", this);
    decideBtn->setObjectName(QString::fromUtf8("decideBtn"));
    decideBtn->setGeometry(QRect(450, 485, 93, 31));

    //点击搜索文件进行搜索
    connect(calendarBtn, SIGNAL(clicked()), this, SLOT(searchVideo()));
    //显示所有的视频
    connect(showAllVideoBtn,SIGNAL(clicked()),this,SLOT(getAllFile()));
    //点击文件按钮时,选择文件路径
    connect(chooseUrl, SIGNAL(clicked()), this, SLOT(chooseExportUrl()));
    //点击小箭头时或者确定时,进行转码导出
    connect(exportBtn, SIGNAL(clicked()), this, SLOT(doExport()));
    connect(decideBtn, SIGNAL(clicked()), this, SLOT(doExport()));
    //日期编辑框更新
    connect(dateEdit,  SIGNAL(dateChanged(QDate)), this, SLOT(getTimeFile(QDate)));
    //当视频被选中时的相关操作
    connect(listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(chooseVideo(QListWidgetItem*)));
    //刷新文件总帧数
    connect(recode, SIGNAL(frameNumFindChange(int)), this, SLOT(flashFrame(int)));
    //文件类型更改时, 后缀
    connect(videoType,SIGNAL(activated(int)),this,SLOT(flashExportUrl(int)));
    //点击退出时返回
    connect(menuListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(exitFun(QListWidgetItem*)));

}

/*
    函数说明: 得到用户下, 全部文件信息
*/
void CExportWin::getAllFile()
{
    this->uId = s.getUserName();
    //更新fileInfo信息
    this->fileNameCount = CFileTool::fGetAllFile(this->uId, "video", fileInfo);
    //加入Item内
    CFileTool::listWinAddItem(fileInfo, listWidget, videoList, coverList);
}


/*
    函数说明: 得到用户下, 时间约束文件信息
*/
void CExportWin::getTimeFile(QDate curTime)
{
    this->uId = s.getUserName();
    //更新fileInfo信息
    this->fileNameCount = CFileTool::fGetTimeFile(uId, curTime, "video", fileInfo);
    //加入Item内
    CFileTool::listWinAddItem(fileInfo, listWidget, videoList, coverList);
}

/*
    函数说明: 点击搜索按钮后进行文件的搜索
*/
void CExportWin::searchVideo()
{
    getTimeFile(dateEdit->date());
    QString text = "查找出 " + QString::number(this->fileNameCount) + " 个结果";
    QMessageBox::information(this, "查找完毕: ", text, QMessageBox::Yes);
}


/*
    函数说明:获取选择导出的文件名
*/
void CExportWin::chooseVideo(QListWidgetItem *)
{
    this->fileName = listWidget->currentItem()->text();
    if(this->exportUrl->text().length() != 0)
    {
        QString newUrl = fileFull + '/'+ fileName.mid(0, fileName.length() - 4) + videoType->currentText();
        this->exportUrl->setText(newUrl);
    }
}

/*
    函数说明:选择导出的URL
*/
void CExportWin::chooseExportUrl()
{
    fileFull = QFileDialog::getExistingDirectory(this);//选择目录名
    if(fileFull.length() == 0)
    {
        return;
    }
    if(this->fileName.length() == 0)
    {
        QMessageBox::warning(this, "注意:", "未选择导出的视频", QMessageBox::Yes);
        this->exportUrl->setText(fileFull);
        return;
    }
    QString newUrl = fileFull + '/'+ fileName.mid(0, fileName.length() - 4) + videoType->currentText();
    this->exportUrl->setText(newUrl);
}

/*
    函数说明:执行导出
*/
void CExportWin::doExport()
{
    int pos = fileName.lastIndexOf('.');
    if(this->fileName.length() == 0)
    {
        QMessageBox::warning(this, "注意:", "未选择导出的视频", QMessageBox::Yes);
        return;
    }
    else if(this->exportUrl->text().length() == 0)
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
        if(frameAllNum == -1)
        {
            QMessageBox::warning(this, "注意:", "导出视频总帧数读取失败, 进度条无法开启", QMessageBox::Yes);
            //开始导出
            this->recode->tranceToFormat(exportUrl->text());
            return;
        }
        //开始进度条
        progressBar->show();
        //开始导出
        this->recode->tranceToFormat(exportUrl->text());
    }
}


/*
    函数说明: 刷新文件总帧数
*/
void CExportWin::flashFrame(int curFrameNum)
{
    //设置步进值
    this->steps = (curFrameNum / this->frameAllNum)*100;
    //更新进度条步进值
    progressBar->setValue(this->steps);
    //更新窗口
    this->update();
    //判断是否完成
    if(this->steps == 100)
    {
        QMessageBox::information(this, "注意:", "导出完成", QMessageBox::Yes);
        this->steps = 0;
        progressBar->hide();
        return;
    }
}

/*
    函数说明:刷新导出URL
*/
void CExportWin::flashExportUrl(int)
{
    if(this->exportUrl->text().length() != 0 && fileName.length() != 0)
    {
        QString newUrl = fileFull + '/'+ fileName.mid(0, fileName.length() - 4) + videoType->currentText();
        this->exportUrl->setText(newUrl);
    }
}

/*
    函数说明:退出函数
*/
void CExportWin::exitFun(QListWidgetItem *)
{
    this->hide();
}
