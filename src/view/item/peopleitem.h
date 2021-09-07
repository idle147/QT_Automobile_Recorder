#ifndef PEOPLEITEM_H
#define PEOPLEITEM_H

#include <QObject>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QSize>
#include <QTimer>

class CPeopleItem: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit CPeopleItem();
    QRectF boundingRect() const;     //定义人的大致范围

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR); //设置重绘函数

private:
    int frame;                              //标志跑动的帧数
    QPixmap pix1, pix2, pix3, pix4, pix5;   //展示人跑步的动画
    QPixmap pix6, pix7, pix8, pix9, pix10;  //展示人跑步的动画
    int boom;                              //标志爆炸
    qreal Xmove, Ymove, angle;              //设置移动的方向
    QTimer *timer;                          //爆炸后人物翻滚的定时器

signals:
    void getBoom();     //发生爆炸


public slots:
    void advance(int);               //定义人的移动规则
    void stopMove();    //停止图元翻滚
};

#endif // PEOPLEITEM_H
