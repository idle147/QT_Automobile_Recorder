#include "picturewin.h"
#include <QMessageBox>
#include "managewin.h"
CPictureWin::CPictureWin()
{
    //初始变量设置
    this->s = CGetSetInfo::Instance(); //调用单例
    this->control = CMyController::getInstence();//调用控制器信息

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
    titleLab = new QLabel("照片列表", this);
    titleLab->setObjectName(QString::fromUtf8("titleLab"));
    titleLab->setGeometry(QRect(260, 30, 151, 41));
    titleLab->setFont(font);

    //回放的设置
    listWidget = new QListWidget(this);
    listWidget->setObjectName(QString::fromUtf8("listWidget"));
    listWidget->setGeometry(QRect(0, 115, 580, 485));
    listWidget->setSortingEnabled(true);            //设置自动排序
    listWidget->setCurrentRow(0);                   //设置当前选择行为第0行
    listWidget->setViewMode(QListView::IconMode);   //设置为图标模式
    listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//设置垂直滚动条常开
    listWidget->setStyleSheet(qss);
    listWidget->setIconSize(QSize(180, 180));

    //日历窗口的设置
    calendarWin = new QCalendarWidget(this);
    calendarWin->setObjectName(QString::fromUtf8("calendarWin"));
    calendarWin->setGeometry(QRect(50, 140, 50, 50));
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
    showAllPicBtn = new QPushButton(this);
    showAllPicBtn->setObjectName(QString::fromUtf8("showAllPicBtn"));
    showAllPicBtn->setGeometry(QRect(44, 81, 28, 28));//QRect(321, 108, 29, 29)
    showAllPicBtn->setStyleSheet("border-image:url(:/icon/photo_gallery2.png)"); //设置按钮背景

    //菜单下拉清单
    menuListWidget = new CMenuListWidget(this);
    menuListWidget->setObjectName(QString::fromUtf8("showAllPicBtn"));
    menuListWidget->setGeometry(QRect(568, 104, 95, 507));//QRect(321, 108, 29, 29)

    //放大展示界面
    showBtn = new QPushButton(this);
    showBtn->setGeometry(listWidget->geometry());
    showBtn->hide();//控件默认隐藏

    connect(calendarBtn,SIGNAL(clicked()),this,SLOT(searchPic()));
    connect(showAllPicBtn,SIGNAL(clicked()),this,SLOT(getAllFile()));
    connect(dateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(getTimeFile(QDate)));
    connect(listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(amplifyPicture(QListWidgetItem*)));
    connect(showBtn,SIGNAL(clicked()),this,SLOT(shinkPicture()));
    connect(menuListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(exitFun(QListWidgetItem*)));
}

/*
    函数说明: 得到用户下, 全部文件信息
*/
void CPictureWin::getAllFile()
{
    listWidget->clear();
    this->uId = s.getUserName();
    //更新fileInfo信息,并计数
    this->fileNameCount = CFileTool::fGetAllFile(this->uId, "photo", fileInfo);
    //加入Item内
    CFileTool::listWinAddItem(fileInfo, listWidget, photoList);
}


/*
    函数说明: 得到用户下, 时间约束文件信息
*/
void CPictureWin::getTimeFile(QDate curTime)
{
    listWidget->clear();
    this->uId = s.getUserName();
    //更新fileInfo信息, 并计数
    this->fileNameCount = CFileTool::fGetTimeFile(uId, curTime, "photo", fileInfo);
    //加入list窗口
    CFileTool::listWinAddItem(fileInfo, listWidget, photoList);
}


/*
    函数说明: 点击搜索按钮后进行文件的搜索
*/
void CPictureWin::searchPic()
{
    getTimeFile(dateEdit->date());
    QString text = "查找出 " + QString::number(this->fileNameCount) + " 个结果";
    QMessageBox::information(this, "查找完毕", text, QMessageBox::Yes);
}


/*
    函数功能: 点击图片放大
*/
void CPictureWin::amplifyPicture(QListWidgetItem*)
{
    //设置地址
    QString desUrl = s.getPhotoUrlInfo();
    QString IconUrl = "border-image:url(" + desUrl + "/" + listWidget->currentItem()->text() + ")";//定义图标的地址
    this->showBtn->setStyleSheet(IconUrl); //设置按钮背景
    showBtn->show();    //展示控件
}

/*
    函数功能: 点击缩小图片
*/
void CPictureWin::shinkPicture()
{
    //还原图片
    showBtn->hide();
}

void CPictureWin::exitFun(QListWidgetItem*)
{
    this->listWidget->clear();
    this->hide();
}




