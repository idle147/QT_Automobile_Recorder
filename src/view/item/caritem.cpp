#include "caritem.h"

CCarItem::CCarItem(QString imgPath, int x, int y)
{
    this->img.load(imgPath);
    img = img.scaled(x, y, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->state = false; //没有发生爆炸
}

QRectF CCarItem::boundingRect() const
{
    return QRectF(-img.width()/2, -img.height()/2, img.width(), img.height());
}

void CCarItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(boundingRect().topLeft(), img);
    option = Q_NULLPTR;
    widget = Q_NULLPTR;
}

void CCarItem::advance(int)
{
    if(state == false)
    {
        Xmove = 8;
        Ymove = 0;
    }
    else
    {
        return;
    }
    //改变图元的位置
    this->setPos(mapToParent(Xmove, Ymove));
}

void CCarItem::changeState()
{
    //发生了爆炸
    this->state = true;
}
