#include "mainwin.h"
#include <QPainter>

CMainWin::CMainWin()
{
    //相关变量初始化
    openFlag = false;      //默认不打开下拉设置界面
    getPic = false;        //默认不拍照
    this->s = CGetSetInfo::Instance();                //调用设置信息变量单例
    this->control = CMyController::getInstence();           //调用控制器信息
    this->imgNum = 0;      //默认的数量为0
    this->decode = nullptr;

    //设置QSS
    QString qss = "";
    CFileTool::readQSS(":/QSS/mainWin.qss", qss);
    this->setStyleSheet(qss);

    //窗口的基本设置
    this->setWindowTitle(tr("基本信息设置"));         //设置窗体标题
    this->setWindowIcon(QIcon(":/images/icon.jpg"));//生成窗口图标
    this->setFixedSize(640, 600);                   //设置尺寸

    //字体大小的设置
    font.setPointSize(18);
    font1.setPointSize(12);

    //设置字体的类型
    font.setFamily(QString::fromUtf8("msyh"));
    font1.setFamily(QString::fromUtf8("msyh"));

    //标题按钮的设置
    titleLab = new QLabel("行车记录仪", this);
    titleLab->setObjectName(QString::fromUtf8("titleLab"));
    titleLab->setGeometry(QRect(260, 30, 150, 40));
    titleLab->setFont(font);

    //日期编辑框的设置
    dateLab = new QLabel("yyyy年MM月dd日 hh:mm:ss",this);
    dateLab->setObjectName(QString::fromUtf8("dateEdit"));
    dateLab->setGeometry(QRect(40, 90, 230, 40));
    dateLab->setFont(font1);
    this->curDateTime = QDateTime::currentDateTime();
    dateLab->setText(curDateTime.toString("yyyy年MM月dd日 hh:mm:ss"));//设置时间

    //正在录制
    recordLab = new QLabel(this);
    recordLab->setGeometry(QRect(20, 130, 30, 30));
    recordLab->setObjectName(QString::fromUtf8("recordLab"));
    recordLab->setStyleSheet("border-image:url(:/icon/photography.png)");

    //拍照LOGO
    photoLab = new QLabel(this);
    photoLab->setGeometry(QRect(55, 130, 300, 30));
    photoLab->setObjectName(QString::fromUtf8("photoLab"));
    photoLab->hide();

    //视频播放主窗口设置
    videoBtn = new QPushButton(this);
    videoBtn->setObjectName(QString::fromUtf8("videoBtn"));
    videoBtn->setGeometry(QRect(0, 120, 640, 480));

    //设置遮罩窗口
    mpShadeWindow = new QWidget(this);
    QString str("QWidget{background-color:rgba(0,0,0,0.6);}");   //0.6代表透明度，根据需要自行调整
    mpShadeWindow->setStyleSheet(str);
    mpShadeWindow->setGeometry(QRect(0, 120, 640, 480));    //遮罩窗口位置
    mpShadeWindow->hide();     //隐藏

    //设置登录
    loginEdit = new QLineEdit(this);
    loginEdit->setGeometry(QRect(450, 80, 145, 50));
    loginEdit->setFont(font1);
    loginEdit->setReadOnly(true);   //设置只图不可编辑
    loginEdit->setStyleSheet("background:transparent;border-style:none");
    if(s.getUserName() == "")
    {
        loginEdit->setText("未登录...");
    }

    //点击登录按钮
    loginBtn = new QPushButton(this);
    loginBtn->setObjectName(QString::fromUtf8("loginBtn"));
    loginBtn->setGeometry(QRect(580, 90, 30, 30));
    loginBtn->setIcon(QIcon(QPixmap(":/icon/login.png")));
    loginBtn->setIconSize(QSize(30, 30));

    //工具按钮的设置
    toolBtn = new QPushButton(this);
    toolBtn->setObjectName(QString::fromUtf8("toolBtn"));
    toolBtn->setGeometry(QRect(610, 90, 30, 30));
    toolBtn->setIcon(QIcon(QPixmap(":/icon/doubleleft.png")));

    //下拉菜单的设置
    setlistWin = new QListWidget(this);
    setlistWin->setObjectName(QString::fromUtf8("setlistWin"));
    setlistWin->setGeometry(QRect(580, 120, 60, 480));
    setlistWin->setFont(font1);
    setlistWin->setViewMode(QListView::IconMode);   //设置为图标模式
    setlistWin->setAlternatingRowColors(true);
    addItem();
    setlistWin->hide();//默认隐藏

    //定时器更新时间
    timer = new QTimer(this);
    tshink = new QTimer(this);
    tHider = new QTimer(this);
    timer->start(1000); // 每次发射timeout信号时间间隔为1秒

    //播放摄像头
    this->decode = nullptr;
    playCamera();

    //槽函数
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
    connect(tHider,SIGNAL(timeout()),this,SLOT(hidePhotoWin()));
    connect(tshink,SIGNAL(timeout()),this,SLOT(hideMpShadeWin()));
    connect(toolBtn,SIGNAL(clicked()),this,SLOT(openSetList()));
    connect(videoBtn,SIGNAL(clicked()),this,SLOT(savePic()));
    connect(setlistWin, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(doOption(QListWidgetItem*)));
    connect(loginBtn, SIGNAL(clicked()), this, SLOT(judgeLogin()));
}

CMainWin::~CMainWin()
{
    //结束线程
    if(this->decode->isRunning())
    {
        //结束线程
        this->decode->setExitFlag(true);
        cerr << "end1" <<endl<<"endl1"<<endl;
        if(this->decode->isRunning())
        {
            cerr << "end2" << endl << "endl2" <<endl;
            this->decode->terminate();
            this->decode->wait();
        }
    }
}

void CMainWin::addItem()
{
    setlistWin->setResizeMode(QListView::Adjust);         //图标自动调整
    setlistWin->setWindowFlags(Qt::FramelessWindowHint);  //设置无边框
    setlistWin->setIconSize(QSize(50, 50));
    //添加设置清单列表的生成
    QStringList setListInfo;
    setListInfo << QStringLiteral("拍照") << QStringLiteral("回放") << QStringLiteral("照片")
                << QStringLiteral("转码") << QStringLiteral("设置") << QStringLiteral("退出");

    //存入Icon的图标地址
    QStringList iconPic;
    iconPic << QStringLiteral(":/icon/camera.png") << QStringLiteral(":/icon/history.png")
            << QStringLiteral(":/icon/photo_gallery.png") << QStringLiteral(":/icon/changecode.png")
            << QStringLiteral(":/icon/settings.png") << QStringLiteral(":/icon/exit.png");

    //遍历添加ITEM数据
    for(int i = 0;i < setListInfo.length(); i++)
    {
        //通过 QListWidgetItem添加文本以及Icon数据的
        QListWidgetItem * IconItem = new QListWidgetItem(QIcon(iconPic.at(i)), setListInfo.at(i));
        setlistWin->insertItem(i, IconItem);
    }
}


/*
    函数功能:更新当前系统的时间
*/
void CMainWin::updateTime()
{
    dateLab->clear();
    this->curDateTime=QDateTime::currentDateTime();
    dateLab->setText(curDateTime.toString("yyyy年MM月dd日 hh:mm:ss"));
}

void CMainWin::openSetList()
{
    if(this->openFlag == true)//如果设置界面处于打开的状态,则关闭
    {
        toolBtn->setIcon(QIcon(QPixmap(":/icon/doubleleft.png")));
        setlistWin->hide();
    }
    else//如果设置界面处于关闭的状态,则打开
    {
        toolBtn->setIcon(QIcon(QPixmap(":/icon/doubleright.png")));
        setlistWin->show();
    }
    //取反
    this->openFlag = !openFlag;
}

/*
    播放摄像头
*/
void CMainWin::playCamera()
{
    if(s.findInfo() == false)
    {
        QMessageBox::information(this, "warning","设置信息未设置, 请设置!", QMessageBox::Yes);
        this->hide();
        CManageWin::getInstence()->findWin(e_setWin)->show();
        return;
    }
    if(this->decode == nullptr)
    {
        this->decode = new CDecodeVideo(s.getVideoUrlInfo(), CTool::char2int(s.getTimeInfo()), s.getCamInfo());
    }
    //连接切分出来的RGB图片,并播放
    this->decode->setType(EplayAndRecord);
    //启动线程
    decode->start();
    //播放连接槽函数
    connect(decode, SIGNAL(sendImg(QImage)), this, SLOT(reciveSlot(QImage)));
}

void CMainWin::reciveSlot(QImage img)
{
    QString picUrl = s.getPhotoUrlInfo();
    QString saveType = "photo";
    QString picName;
    this->img = img;
    if(this->getPic == true)
    {
        //如果开始拍照,则保存照片到路径
        picName = curDateTime.toString("yyyyMMddhhmmss");
        //保存到数据库中
        QString uId = s.getUserName();    //获得用户ID
        this->control->writeTypeInfo(uId, picName, saveType, picUrl, "0");
        //保存到文件内
        picUrl += + '/' + picName + ".jpg";
        img.save(picUrl, "JPG", 100);
        //左上角图标显示与更新
        this->photoLab->setText("已保存照片:"+picName+ ".jpg");
        this->photoLab->show();
        this->tHider->start(1000);
        //产生一个一闪而过的黑色遮罩
        this->mpShadeWindow->show();
        //重置拍照标志位
        this->getPic = false;
    }
    this->imgNum++;
    if(imgNum >= 25)
    {
        recordLab->setStyleSheet("border-image:url(:/icon/photography.png)");
        imgNum = 0;
        return;
    }
    else if(imgNum == 12)
    {
        recordLab->setStyleSheet("border-image:url(:/icon/photography_red.png)");
    }
    if(s.getUserName().length() != 0)
    {
        this->loginEdit->setText("欢迎:" + s.getUserName());
        loginBtn->setIcon(QIcon(QPixmap(":/icon/turnoff.png")));
    }
    this->update();
}

/*
    函数说明:执行相关操作
*/
void CMainWin::doOption(QListWidgetItem*)
{
    int indexNum = setlistWin->currentRow();
    //判断是否登录, 没登陆则进行登录
    if(indexNum != 4 && indexNum != 5)
    {
        if(!judgeLogin2())
        {
            return;
        }
    }
    switch (indexNum)
    {
    case 0:
    {   //进行"拍照"
        savePic();
        break;
    }
    case 1:
    {
        //跳转到界面“回放”
        this->hide();
        CManageWin::getInstence()->findWin(e_hisChooseWin)->show();
        break;
    }
    case 2:
    {
        //跳转到界面“照片”
        this->hide();
        CManageWin::getInstence()->findWin(e_pictureWin)->show();
        break;
    }
    case 3:
    {
        //跳转到界面"转码"
        this->hide();
        CManageWin::getInstence()->findWin(e_exportWin)->show();
        break;

    }
    case 4:
    {
        //跳转到界面"设置"
        this->hide();
        CManageWin::getInstence()->findWin(e_setWin)->show();
        break;
    }
    case 5:
    {
        //跳转到界面"退出"
        exit(0);
        break;
    }
    }
}

/*
    函数说明:保存相应的图片信息
*/

void CMainWin::savePic()
{
    this->getPic = true;
    tshink->start(150);
}

/*
    函数说明:隐藏遮罩窗口
*/
void CMainWin::hideMpShadeWin()
{
    //时间到了隐藏窗口
    this->mpShadeWindow->hide();
}

void CMainWin::hidePhotoWin()
{
    this->photoLab->hide();
}

/*
    函数说明:绘制相关事件
*/
void CMainWin::paintEvent(QPaintEvent *)
{
    //按钮设置为透明
    videoBtn->setFlat(true);
    videoBtn->setStyleSheet("QPushButton{background: transparent;}");
    QPainter painter(this);
    if(!this->img.isNull())
    {
        //播放区域设置为videoBtn
        painter.drawImage(QRect(this->videoBtn->pos(), QSize(640, 480)), this->img);
    }
}


/*
    函数说明:判断登录,未登录需要登录,否则注销
*/
bool CMainWin::judgeLogin()
{
    if(s.getUserName() == "")
    {
        QMessageBox::information(this, "warning","未登录,请登录!", QMessageBox::Yes);
        this->hide();
        CManageWin::getInstence()->findWin(e_loginWin)->show();
        return false;
    }
    //登录后进行注销
    else if(loginEdit->text() != "未登录...")
    {
        QMessageBox:: StandardButton result = QMessageBox::warning(this, "注意: ","是否注销该账户?(注销后您将无法使用本软件)", QMessageBox::Yes|QMessageBox::No);
        if(result == QMessageBox::Yes)
        {
            s.setUserName("");
            loginBtn->setIcon(QIcon(QPixmap(":/icon/login.png")));
            this->loginEdit->setText("未登录...");
        }
    }
    return true;
}

/*
    函数说明:判断是否登录
*/
bool CMainWin::judgeLogin2()
{
    if(s.getUserName() == "")
    {
        QMessageBox::information(this, "warning","未登录,请登录!", QMessageBox::Yes);
        this->hide();
        CManageWin::getInstence()->findWin(e_loginWin)->show();
        return false;
    }
    return true;
}
