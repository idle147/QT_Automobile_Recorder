#ifndef CSTARTWIN_H
#define CSTARTWIN_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QLabel>
#include <QIcon>
#include <QTime>
#include "item/caritem.h"
#include "item/peopleitem.h"
#include "item/titleitem.h"
#include "controller/getsetinfo.h"


class CStartWin : public QGraphicsView
{
    Q_OBJECT
public:
    CStartWin();

private:
    QGraphicsScene *scene;      //开辟场景对象
    QGraphicsView *view;        //开辟视图对象
    QGraphicsPixmapItem *boom;  //爆炸图元

    CCarItem *car;              //创建小车的图元
    CPeopleItem *people;        //创建人的图元
    CTitleItem *title;          //生成标题控件
    CTitleItem *titleIcon;      //生成标题icon

    QTimer *timer1, *timer2;    //设置定时器,用以图元移动
    CGetSetInfo s;              //调用单例

public slots:
    void displayBoom();         //展示爆炸信号
    void jumpWin();             //停止图元
};

#endif // CSTARTWIN_H
