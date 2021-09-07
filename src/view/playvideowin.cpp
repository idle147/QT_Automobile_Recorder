#include "playvideowin.h"
#include <QPainter>
#include <QMessageBox>
#include <QCompleter>
#include "exportwidget.h"

CPlayVideo::CPlayVideo(QStringList vlist, int countNum)
{   
    //基础变量的设置
    this->videoList = vlist;
    //判断需要播放的视频是在videoList上哪个位置
    this->num = countNum;
    this->stop = false;
    this->listWidgetFlag = false;
    this->fileNameCount = this->videoList.count();
    this->getPic = false;                                   //保存图片标志位
    this->control = CMyController::getInstence();           //调用控制器信息
    this->s = CGetSetInfo::Instance();                      //调用设置信息变量单例
    this->currentTime = 0;                                  //设置当前播放时长

    //窗口的基本设置
    this->setFixedSize(640, 530);                     //设置尺寸

    //视频播放窗口
    videoBtn = new QPushButton(this);
    videoBtn->setObjectName(QString::fromUtf8("videoButton"));
    videoBtn->setGeometry(QRect(0, 0, 640, 480));

    //设置遮罩窗口
    mpShadeWindow = new QWidget(this);
    QString str("QWidget{background-color:rgba(0,0,0,0.6);}");   //0.6代表透明度，根据需要自行调整
    mpShadeWindow->setStyleSheet(str);
    mpShadeWindow->setGeometry(QRect(0, 0, 640, 480));    //遮罩窗口位置
    mpShadeWindow->hide();     //隐藏

    //上一个播放按钮
    lastBtn = new QPushButton(this);
    lastBtn->setObjectName(QString::fromUtf8("lastBtn"));
    lastBtn->setGeometry(QRect(238, 485, 46, 46));
    lastBtn->setStyleSheet("border-image: url(:/icon/previous.png)");

    //本播放按钮
    playBtn = new QPushButton(this);
    playBtn->setObjectName(QString::fromUtf8("playBtn"));
    playBtn->setGeometry(QRect(285, 485, 46, 46));
    playBtn->setStyleSheet("border-image: url(:/icon/play.png)");

    //拍照提示信息
    photoLab = new QLabel(this);
    photoLab->setGeometry(QRect(30, 30, 300, 30));
    photoLab->setObjectName(QString::fromUtf8("photoLab"));
    photoLab->hide();

    //下一个播放按钮
    nextBtn = new QPushButton(this);
    nextBtn->setObjectName(QString::fromUtf8("nextBtn"));
    nextBtn->setGeometry(QRect(327, 485, 46, 46));
    nextBtn->setStyleSheet("border-image: url(:/icon/next.png)");

    //文件清单按钮
    videoPlayFileBtn = new QPushButton(this);
    videoPlayFileBtn->setObjectName(QString::fromUtf8("exportBtn"));
    videoPlayFileBtn->setGeometry(QRect(30, 489, 41, 41));
    videoPlayFileBtn->setStyleSheet("border-image: url(:/icon/folder.png)");

    //保存按钮的设置
    saveBtn = new QPushButton(this);
    saveBtn->setObjectName(QString::fromUtf8("exportBtn"));
    saveBtn->setGeometry(QRect(83, 494, 32, 32));
    saveBtn->setStyleSheet("border-image: url(:/icon/save.png)");

    //截图按钮
    photoBtn = new QPushButton(this);
    photoBtn->setObjectName(QString::fromUtf8("photoBtn"));
    photoBtn->setGeometry(QRect(480, 489, 41, 41));
    photoBtn->setStyleSheet("border-image: url(:/icon/screenshot.png)");

    //速度调整按钮
    changeSpeedBtn = new QPushButton("1X",this);
    changeSpeedBtn->setObjectName(QString::fromUtf8("changeSpeedBtn"));
    changeSpeedBtn->setGeometry(QRect(529, 490, 38, 38));
    changeSpeedBtn->setStyleSheet("border-image: url(:/icon/coin.png)");

    //退出按钮的设置
    exitBtn = new QPushButton(this);
    exitBtn->setObjectName(QString::fromUtf8("exportBtn"));
    exitBtn->setGeometry(QRect(580, 494, 32, 32));
    exitBtn->setStyleSheet("border-image: url(:/icon/return.png)");

    //文件下拉框
    this->fileListWidget = new QListWidget(this);
    this->fileListWidget->setObjectName(QString::fromUtf8("listWidget"));
    this->fileListWidget->setGeometry(QRect(30, 241, 115, 240));
    this->fileListWidget->setSortingEnabled(true);            //设置自动排序
    this->fileListWidget->setCurrentRow(0);                   //设置当前选择行为第0行
    this->fileListWidget->setViewMode(QListView::ListMode);   //设置为列表模式
    this->fileListWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//设置垂直滚动条常开
    this->fileListWidget->setIconSize(QSize(15, 15));
    listWinAddItem();   //加入Item控件
    this->fileListWidget->hide();

    //播放进度条
    this->playProgress = new QProgressBar(this);
    playProgress->setValue(0); //设置当前的运行值
    playProgress->setOrientation(Qt::Horizontal); //水平方向
    playProgress->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    playProgress->setFixedSize(640,10); //进度条固定大小
    playProgress->move(0,480);

    //设置进度条最大值
    url = videoList.at(num);
    AllTime = this->control->queryVideoFrameNum(url.mid(url.length()-19).mid(0, 14)) / 25;
    playProgress->setRange(0, AllTime);

    //定时器更新时间
    tShink = new QTimer(this);
    tHider = new QTimer(this);

    //创建解码器对象
    this->playDecode = new CDecodeVideo(url);
    this->playDecode->setType(EPlay);
    this->playDecode->start();

    //连接槽函数
    connect(playDecode,  SIGNAL(sendImg(QImage)), this, SLOT(reciveSlot(QImage)));
    connect(playDecode,  SIGNAL(videoIsEnd()), this, SLOT(stopPlay()));
    connect(photoBtn,SIGNAL(clicked()),this, SLOT(saveScreenShoot()));  //保存截图
    connect(saveBtn, SIGNAL(clicked()),this, SLOT(saveVideo()));        //保存视频
    connect(videoBtn,SIGNAL(clicked()),this, SLOT(isPlay()));           //暂停播放
    connect(playBtn, SIGNAL(clicked()),this, SLOT(isPlay()));           //暂停播放
    connect(lastBtn, SIGNAL(clicked()),this, SLOT(prePlay()));        //上一段视频播放
    connect(nextBtn, SIGNAL(clicked()),this, SLOT(nextPlay()));       //下一段视频播放
    connect(changeSpeedBtn,SIGNAL(clicked()),this, SLOT(changeSpeed()));   //视频速度改变播放
    connect(videoPlayFileBtn, SIGNAL(clicked()),this, SLOT(showListWidget()));//加入文件控件
    connect(exitBtn, SIGNAL(clicked()),this, SLOT(exitWin()));       //退出窗口
    connect(fileListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(chooseFile(QListWidgetItem*)));
    connect(playDecode,  SIGNAL(frameNumFindChange(int)), this, SLOT(flashFrame(int)));    //刷新进度条
    connect(tShink,  SIGNAL(timeout()),this, SLOT(hideMpShadeWin()));  //隐藏遮罩窗口
    connect(tHider,  SIGNAL(timeout()),this, SLOT(hidePhotoWin()));    //隐藏遮罩窗口
}

/*
    函数说明: 绘制事件
*/
void CPlayVideo::paintEvent(QPaintEvent *)
{
    //按钮设置为透明
    videoBtn->setFlat( true );
    videoBtn->setStyleSheet("QPushButton{background: transparent;}");
    QPainter painter(this);
    if(!this->img.isNull())
    {
        //播放区域设置为videoBtn
        painter.drawImage(QRect(this->videoBtn->pos(), QSize(640, 480)), this->img);
    }
}

/*
    函数说明:判断是否在绘制
*/
void CPlayVideo::isPlay()
{
    if(this->stop == true)
    {
        //如果目前的状态是暂停播放, 点击后开始播放
        playDecode->setStop(false);
        //更改图标为开始播放
        playBtn->setStyleSheet("border-image: url(:/icon/play.png)");

    }
    else
    {
        //如果目前的状态是开始播放, 点击后暂停播放
        playDecode->setStop(true);
        //更改图标为暂停播放
        playBtn->setStyleSheet("border-image: url(:/icon/pause.png)");
    }
    //标志位取反
    this->stop = !this->stop;
}

/*
    函数说明:停止播放
*/
void CPlayVideo::stopPlay()
{
    //暂停视频
    playDecode->setStop(true);
    //更改图标为暂停播放
    playBtn->setStyleSheet("border-image: url(:/icon/pause.png)");
    //状态设置暂停
    this->stop = true;
}

/*
    函数说明:退出窗口
*/
void CPlayVideo::exitWin()
{
    this->playDecode->requestInterruption();
    this->playDecode->setExitFlag(true);
    this->close();
}

/*
    函数说明:改变播放的视频
*/
void CPlayVideo::changeVideo()
{
    url = videoList.at(num);
    playDecode->setURL(url);//设置播放地址
    //退出视频
    playDecode->setExitFlag(true);
    //如果是暂停状态,则进行播放
    if(stop == true)
    {
        isPlay();
    }
    //更新进度条
    this->currentTime = 0;
    playProgress->setValue(0); //设置当前的运行值
    AllTime = this->control->queryVideoFrameNum(url.mid(url.length()-19).mid(0, 14)) / 25;
    playProgress->setRange(0, AllTime);
    //刷新屏幕
    this->update();
}


/*
    函数说明: 列表加入清单
*/
void CPlayVideo::listWinAddItem()
{
    this->fileListWidget->clear();    //清空listWidget内所有的Item
    //遍历添加ITEM数据
    for(int i = 0;i < fileNameCount; i++)
    {
        //通过 QListWidgetItem添加文本以及Icon数据
        QListWidgetItem * IconItem = new QListWidgetItem(QIcon(":/icon/video.png"), videoList.at(i).right(19));
        //加入QListWidget
        this->fileListWidget->insertItem(i, IconItem);
    }
}

/*
    函数说明:收到信号
*/
void CPlayVideo::reciveSlot(QImage img)
{
    this->img = img;
    if(this->getPic == true)
    {
        //如果开始拍照,则保存照片到路径
        QString picUrlScreenshpoot = s.getPhotoUrlInfo();
        curDateTime = QDateTime::currentDateTime();
        QString picName = curDateTime.toString("yyyyMMddhhmmss");
        QString saveType = "screenShoot";
        //保存到数据库中
        this->uId = s.getUserName();    //获得用户ID
        this->control->writeTypeInfo(uId, picName, saveType, picUrlScreenshpoot, "0");
        //保存到文件内
        picUrlScreenshpoot = picUrlScreenshpoot + '/' + picName + ".jpg";
        img.save(picUrlScreenshpoot, "JPG", 100);
        //左上角图标显示与更新
        this->photoLab->setText("已保存照片:"+picName+ ".jpg");
        this->photoLab->show();
        tHider->start(1000);
        //产生一个一闪而过的黑色遮罩
        this->mpShadeWindow->show();
        //重置拍照标志位
        this->getPic = false;
    }
    this->update();
}

/*
    函数说明: 保存屏幕截图
*/
void CPlayVideo::saveScreenShoot()
{
    this->getPic = true;
    tShink->start(150);

}

/*
    函数说明:保存视频
*/
void CPlayVideo::saveVideo()
{
    QMessageBox:: StandardButton result = QMessageBox::warning(this, "注意: ","是否导出该视频?(确认则会关闭本窗口)", QMessageBox::Yes|QMessageBox::No);
    if(result == QMessageBox::Yes)
    {
        QString videoName = videoList.at(num).mid(videoList.at(num).length()-19);
        CExportWidget* exportSmallWin = new CExportWidget(videoName, videoList, num);
        exitWin();
        exportSmallWin->show();
    }
}

/*
    函数说明: 上一个视频
*/
void CPlayVideo::prePlay()
{
    if(this->num - 1 < 0)
    {
        QMessageBox::warning(NULL, "warning: ", "没有上一段视频!", QMessageBox::Yes);
        return;
    }
    this->num--;
    changeVideo();
}

/*
    函数说明: 下一个视频
*/
void CPlayVideo::nextPlay()
{
    if(this->num + 1 >= this->videoList.length())
    {
        QMessageBox::warning(NULL, "warning", "没有下一段视频", QMessageBox::Yes);
        return;
    }
    this->num++;
    changeVideo();
}

/*
    函数说明: 改变速度按钮
*/
void CPlayVideo::changeSpeed()
{
    if(changeSpeedBtn->text() == "1X")
    {
        changeSpeedBtn->setText("1.5X");
        this->playDecode->changeSpeed(16.7);
    }
    else if(changeSpeedBtn->text() == "1.5X")
    {
        changeSpeedBtn->setText("2X");
        this->playDecode->changeSpeed(20);
    }
    else if(changeSpeedBtn->text() == "2X")
    {
        changeSpeedBtn->setText("0.5X");
        this->playDecode->changeSpeed(80);
    }
    else if(changeSpeedBtn->text() == "0.5X")
    {
        changeSpeedBtn->setText("1X");
        this->playDecode->changeSpeed(40);
    }
}

/*
    函数说明: 显示列表清单窗口
*/
void CPlayVideo::showListWidget()
{
    if(this->listWidgetFlag == true)
    {
        //若原来的窗口是开的, 则隐藏
        this->fileListWidget->hide();
    }
    else
    {
        this->fileListWidget->show();
    }
    this->listWidgetFlag = !this->listWidgetFlag;
}


/*
    函数说明:更改播放的文件
*/
void CPlayVideo::chooseFile(QListWidgetItem *)
{
    QString res;
    QString match = fileListWidget->currentItem()->text();
    //遍历QStringList查找是否含该字符串
    for(int i = 0; i < this->fileNameCount; i++)
    {
        res = videoList.at(i).right(19);
        if(match == res)
        {
            this->num = i;  //修改播放的视频为选中的视频
            changeVideo();
            break;
        }
    }
}


/*
    函数说明:时间到了隐藏遮罩窗口
*/
void CPlayVideo::hideMpShadeWin()
{
    //时间到了隐藏窗口
    this->mpShadeWindow->hide();
}

/*
    函数说明:隐藏拍照控件
*/
void CPlayVideo::hidePhotoWin()
{
    this->photoLab->hide();
    this->tHider->stop();
}

/*
    函数说明:刷新帧数
*/
void CPlayVideo::flashFrame(int)
{
    this->currentTime++;
    this->playProgress->setValue(currentTime);
}
