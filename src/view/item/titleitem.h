#ifndef TITLEITEM_H
#define TITLEITEM_H
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>


class CTitleItem: public QObject, public QGraphicsItem
{
    //图元类
    Q_OBJECT
public:
    CTitleItem(QString imgPath, int x, int y);
    //const修饰一个方法表示:无法修改该类当中的属性
    QRectF boundingRect() const; //定义图元的大致范围
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //设置重绘函数

private:
    QPixmap img;
    bool state;
    int Xmove, Ymove;   //设置移动的方向

public slots:
    void advance(int); //定义控件的移动规则

};

#endif // TITLEITEM_H
