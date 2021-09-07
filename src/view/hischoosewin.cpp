#include "hischoosewin.h"
#include <QMessageBox>

CHisChoose::CHisChoose()
{
    //初始变量设置
    this->control = CMyController::getInstence();//调用控制器信息
    this->s = CGetSetInfo::Instance();           //调用设置信息单例
    this->f = CFileTool::getInstence();          //调用单例
    this->fileNameCount = 0;

    //打开Qss文件
    QString qss = "";
    CFileTool::readQSS(":/QSS/picAndVideo.qss", qss);

    //窗口的基本设置
    this->setWindowTitle(tr("视频列表"));                 //设置窗体标题
    this->setWindowIcon(QIcon(":/images/icon.jpg"));    //生成窗口图标
    this->setFixedSize(640, 600);                       //设置尺寸

    //设置字体大小设置
    font.setPointSize(18);
    font1.setPointSize(12);

    //设置字体类型设置
    font.setFamily(QString::fromUtf8("msyh"));
    font1.setFamily(QString::fromUtf8("msyh"));

    //标题控件的设置
    titleLab = new QLabel("视频列表", this);
    titleLab->setObjectName(QString::fromUtf8("titleLab"));
    titleLab->setGeometry(QRect(260, 30, 151, 41));
    titleLab->setFont(font);

    //滚动界面设置
    pageWidget = new CPageWidget(3, this);
    pageWidget->setGeometry(QRect(230, 85, 640, 25));

    //回放的设置
    listWidget = new QListWidget(this);
    listWidget->setObjectName(QString::fromUtf8("listWidget"));
    listWidget->setGeometry(QRect(0, 115, 580, 485));
    listWidget->setSortingEnabled(true);            //设置自动排序
    listWidget->setCurrentRow(0);                   //设置当前选择行为第0行
    listWidget->setViewMode(QListView::IconMode);   //设置为图标模式
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

    connect(showAllVideoBtn, SIGNAL(clicked()),this,SLOT(getAllFile())); //显示所有的视频
    connect(calendarBtn, SIGNAL(clicked()), this, SLOT(searchVideo()));  //点击搜索文件进行搜索
    connect(dateEdit,    SIGNAL(dateChanged(QDate)), this, SLOT(getTimeFile(QDate)));  //日期编辑框更新
    connect(listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(playVideo(QListWidgetItem*)));
    connect(pageWidget, SIGNAL(currentPageChanged(int)), this, SLOT(listWinAddItem(int)));
    connect(menuListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(exitFun(QListWidgetItem*)));
}

/*
    函数说明: 得到视频封面
*/
QStringList &CHisChoose::getCoverList()
{
    return this->coverList;
}

/*
    函数说明: 加入控件
*/
void CHisChoose::listWinAddItem(int num)
{
    //将文件名和文件路径读取并存入stringList链表内
    videoList.clear();
    coverList.clear();
    int fileSize = fileInfo.size();
    int iNum = 0;
    while(iNum < fileSize)
    {
        //判断视频文件是否存在
        QString url = fileInfo.at(iNum + 4) + '/' + fileInfo.at(iNum + 3) + ".h264";
        if(CFileTool::isDirExist(url))
        {
            videoList << url;
        }
        else
        {
            continue;
        }
        //判断Icon的图片文件是否存在
        url = fileInfo.at(iNum + 4) + '/' + fileInfo.at(iNum + 3) + ".png";
        if(CFileTool::isDirExist(url))//如果图片文件存在,则加入
        {
            coverList << url;
        }
        //不存在则加入没有发现的Icon图标
        else
        {
            coverList << ":/icon/block.png";
        }
        iNum = iNum + 5;
    }
    //清空listWidget内所有的Item
    listWidget->setMovement(QListView::Static);
    listWidget->clear();
    //定义stringList内视频的数量
    int fileNameCount = videoList.length();
    int i = (num - 1) * 9;
    //遍历添加ITEM数据
    while(i < fileNameCount && i < num * 9)
    {
        //通过 QListWidgetItem添加文本以及Icon数据
        //H264长度为19位
        QListWidgetItem * IconItem = new QListWidgetItem(QIcon(coverList.at(i)), videoList.at(i).right(19));
        //加入QListWidget
        listWidget->insertItem(i, IconItem);
        i++;
    }
}

/*
    函数说明: 得到视频
*/
QStringList &CHisChoose::getVideoList()
{
    return this->videoList;
}

/*
    函数说明: 得到用户下, 全部文件信息
*/
void CHisChoose::getAllFile()
{
    this->uId = s.getUserName();
    //更新fileInfo信息, 并计数
    this->fileNameCount = CFileTool::fGetAllFile(this->uId, "video", fileInfo);
    if(fileNameCount == 0)
    {
        pageWidget->setMaxPage(1);
        pageWidget->setCurrentPage(1);
        return;
    }
    int itemNum = fileInfo.length() / 5;
    pageWidget->setMaxPage(itemNum / 9 + 1);
    pageWidget->setCurrentPage(1);
    //加入Item内
    listWinAddItem(1);
}

/*
    函数说明: 得到用户下, 时间约束文件信息
*/
void CHisChoose::getTimeFile(QDate curTime)
{
    this->uId = s.getUserName();
    //更新fileInfo信息, 并计数
    this->fileNameCount = CFileTool::fGetTimeFile(uId, curTime, "video", fileInfo);
    if(fileNameCount == 0)
    {
        pageWidget->setMaxPage(1);
        pageWidget->setCurrentPage(1);
        return;
    }
    //设置最大的页面数
    int itemNum = fileInfo.length() / 5;
    pageWidget->setMaxPage(itemNum / 9 + 1);
    pageWidget->setCurrentPage(1);
    //加入Item内
    listWinAddItem(1);
}

/*
    函数说明: 点击搜索按钮后进行文件的搜索
*/
void CHisChoose::searchVideo()
{
    this->listWidget->clear();
    getTimeFile(dateEdit->date());
    QString text = "查找出 " + QString::number(this->fileNameCount) + " 个结果";
    QMessageBox::information(this, "查找完毕", text, QMessageBox::Yes);
}


/*
    函数功能: 点击播放视频
*/
void CHisChoose::playVideo(QListWidgetItem*)
{
    //设置当前播放视频的地址
    QString url = s.getVideoUrlInfo();
    url += "/" + listWidget->currentItem()->text();
    this->fileNameCount = this->videoList.length();
    //遍历查找该地址在videolist里面的哪里
    int i = 0;
    while(i < fileNameCount)
    {
        if(url == videoList.at(i))
        {
            CPlayVideo* playWin = new CPlayVideo(this->videoList, i);
            playWin->show();
            return;
        }
        i++;
    }
    QMessageBox::warning(this, "注意: ", "该视频无法播放!", QMessageBox::Yes);
}

/*
    函数说明:隐藏该窗口,返回上层窗口
*/
void CHisChoose::exitFun(QListWidgetItem*)
{
    this->listWidget->clear();
    this->hide();
}
