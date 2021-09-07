#include "startwin.h"
#include <QThread>
#include "QMessageBox"
#include "managewin.h"

/*
    函数说明:相关设置初始化
*/
CStartWin::CStartWin()
{
    //调用单例
    this->s = CGetSetInfo::Instance();//调用单例
    //设置窗口的大小
    this->setFixedSize(1071,714);
    //设置窗口透明(无边框)
    setWindowFlags(Qt::FramelessWindowHint);//无边框
    //设置背景图
    this->setBackgroundBrush(QBrush(QPixmap(":/images/road.png")));   //设置背景图

    //生成场景
    scene = new QGraphicsScene();                                       //开辟场景对象
    this->setScene(scene);                                              //给视图添加场景
    scene->setSceneRect(QRectF(0,0, this->width()-2,this->height()-2)); //设置场景的坐标

    //生成汽车
    this->car = new CCarItem(":/images/car.png", 350 , 250); //创建图元
    scene->addItem(car);                                  //添加图元
    car->setPos(200, this->height()/2 + 280);             //定义图元的位置

    //生成人
    this->people = new CPeopleItem();
    this->people->setPos(600, this->height()/2 - 100);           //定义图元的位置
    scene->addItem(this->people);                         //图元加入场景

    //生成爆炸图元并隐藏
    QPixmap boomPixmap = QPixmap(":/images/boom.png");
    boomPixmap = boomPixmap.scaled(200, 200, Qt::KeepAspectRatio);
    this->boom =scene->addPixmap(boomPixmap);
    this->boom->setPos(470, 550);
    this->boom->hide();

    //启动定时器
    timer1 = new QTimer();   //设置开始的定时器,用以图元移动;
    timer2 = new QTimer();   //设置人翻滚的时间

    timer1->start(100);      //定时间隔
    connect(timer1, SIGNAL(timeout()), scene, SLOT(advance()));       //图元移动
    connect(timer2, SIGNAL(timeout()), this, SLOT(jumpWin()));        //图元移动
    connect(people, SIGNAL(getBoom()), this,  SLOT(displayBoom()));   //发生碰撞
    connect(people, SIGNAL(getBoom()), car,   SLOT(changeState()));   //发生碰撞时车停下来

}

/*
    函数说明: 展示爆炸
*/
void CStartWin::displayBoom()
{
    //启动定时器
    timer2->start(1500);      //定时1.5秒后跳转主界面
    this->boom->show();

    //生成标题控件
    this->title = new CTitleItem(":/images/title.png", 700, 200);
    this->titleIcon = new CTitleItem(":/images/carRecord.png", 200, 200);
    scene->addItem(title);
    scene->addItem(titleIcon);
    titleIcon->setPos(250, 0);         //定义标题图片的位置
    title->setPos(700, 5);             //定义标题的位置
}

/*
    函数说明:跳出窗口
*/
void CStartWin::jumpWin()
{
    timer1->stop();
    timer2->stop();
    //添加设置界面信息
    CManageWin::getInstence()->addSet();
    //判断是否有进行设置
    if(s.findInfo() == false)
    {
        QMessageBox::information(this, "warning","设置信息未设置, 请设置!", QMessageBox::Yes);
        //调用设置界面
        CManageWin::getInstence()->findWin(e_setWin)->show();
        this->close();
    }
    else
    {
        //跳转主界面
        CManageWin::getInstence()->addWin();
        CManageWin::getInstence()->findWin(e_mainWin)->show();
        this->close();
    }
}

