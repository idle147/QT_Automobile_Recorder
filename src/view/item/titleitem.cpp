#include "titleitem.h"

CTitleItem::CTitleItem(QString imgPath, int x, int y)
{
    this->img.load(imgPath);
    img = img.scaled(x, y, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

QRectF CTitleItem::boundingRect() const
{
    return QRectF(-img.width()/2, -img.height()/2, img.width(), img.height());
}

void CTitleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(boundingRect().topLeft(), img);
    option = Q_NULLPTR;
    widget = Q_NULLPTR;
}

void CTitleItem::advance(int)
{
    if(state == false)
    {
        Xmove = 0;
        Ymove = 6;
    }
    else
    {
        return;
    }
    //改变图元的位置
    this->setPos(mapToParent(Xmove, Ymove));
}

