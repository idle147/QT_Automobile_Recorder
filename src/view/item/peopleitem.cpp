#include "peopleitem.h"
#include <QPoint>
#include <math.h>

CPeopleItem::CPeopleItem()
{
    //设置初始帧数为1
    this->frame = 1;

    //初始设置不爆炸
    this->boom = 0;

    //定时器初始化
    timer = new QTimer();   //设置定时器,用以图元移动;

    //载入人跑动时候的图片
    this->pix1.load(":/images/people/1.png");
    pix1 = pix1.scaled(100, 150, Qt::KeepAspectRatio);

    this->pix2.load(":/images/people/2.png");
    pix2 = pix2.scaled(100, 150, Qt::KeepAspectRatio);

    this->pix3.load(":/images/people/3.png");
    pix3 = pix3.scaled(100, 150, Qt::KeepAspectRatio);

    this->pix4.load(":/images/people/4.png");
    pix4 = pix4.scaled(100, 150, Qt::KeepAspectRatio);

    this->pix5.load(":/images/people/5.png");
    pix5 = pix5.scaled(100, 150, Qt::KeepAspectRatio);

    this->pix6.load(":/images/people/6.png");
    pix6 = pix6.scaled(100, 150, Qt::KeepAspectRatio);

    this->pix7.load(":/images/people/7.png");
    pix7 = pix7.scaled(100, 150, Qt::KeepAspectRatio);

    this->pix8.load(":/images/people/8.png");
    pix8 = pix8.scaled(100, 150, Qt::KeepAspectRatio);

    this->pix9.load(":/images/people/9.png");
    pix9 = pix9.scaled(100, 150, Qt::KeepAspectRatio);

    this->pix10.load(":/images/people/10.png");
    pix10 = pix10.scaled(100, 150, Qt::KeepAspectRatio);

    connect(timer, SIGNAL(timeout()), this, SLOT(stopMove()));         //图元移动
}

QRectF CPeopleItem::boundingRect() const
{
    qreal adjust = 2;
    return QRectF(-pix1.width()/2-adjust, -pix1.height()/2-adjust,
                  pix1.width()+adjust*2,  pix1.height()+adjust*2);//确定人的大致范围
}

void CPeopleItem::advance(int)
{
    //如果没发生爆炸
    if(boom == 0)
    {
        this->Xmove = 0;
        this->Ymove = 10;
        //改变图元的位置
        this->setPos(mapToParent(Xmove, Ymove));
        //发生图元重叠, 发生爆炸
        if(collidingItems().count() > 0)
        {
            this->boom = 1;     //发生爆炸
            timer->start(1000);   //开始定时器
            emit getBoom();    //发射爆炸信号
        }
    }
    else if(boom == 1)
    {
        angle += (qrand()%10) / 20.0;
        this->Xmove = fabs(sin(angle*3.1416)*10.0) + 1;
        this->Ymove = (qrand()%20 - 10.0) + 5;
        this->setPos(mapToParent(Xmove, -Ymove));
    }
    else
    {
        this->setPos(mapToParent(0, 0));
    }
}

void CPeopleItem::stopMove()
{
    timer->stop();
    this->boom = -1; //停止翻滚
}

void CPeopleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(this->boom == 0)
    {
        if(frame > 10)
        {
            //超过10则重置为1
            this->frame = 1;
        }
        //未爆炸时在跑步
        switch (this->frame)
        {
        case 1:painter->drawPixmap(boundingRect().topLeft(),pix1);break;
        case 2:painter->drawPixmap(boundingRect().topLeft(),pix2);break;
        case 3:painter->drawPixmap(boundingRect().topLeft(),pix3);break;
        case 4:painter->drawPixmap(boundingRect().topLeft(),pix4);break;
        case 5:painter->drawPixmap(boundingRect().topLeft(),pix5);break;
        case 6:painter->drawPixmap(boundingRect().topLeft(),pix6);break;
        case 7:painter->drawPixmap(boundingRect().topLeft(),pix7);break;
        case 8:painter->drawPixmap(boundingRect().topLeft(),pix8);break;
        case 9:painter->drawPixmap(boundingRect().topLeft(),pix9);break;
        case 10:painter->drawPixmap(boundingRect().topLeft(),pix10);break;
        default:break;
        }
        frame++;
    }
    else
    {
        //翻滚的时候,绘制2帧
        painter->drawPixmap(boundingRect().topLeft(),pix1);
        painter->drawPixmap(boundingRect().topLeft(),pix2);
    }
}
