#ifndef CDATEEDIT_H
#define CDATEEDIT_H
#include <QtCore>
#include <QWidget>
#include <QDateEdit>
#include <QStyle>
#include <QPushButton>
#include <QLineEdit>
#include <QStyleOptionSpinBox>
#include <QKeyEvent>
#include <QCalendarWidget>
#include <QPainter>


//类说明: 继承QDateEdit,实现了相应时间编辑框可以为NULL
class CDateEdit : public QDateEdit
{

    Q_OBJECT

public:

    //相关变量
    QDateTime dateTime() const;
    QDate date() const;
    QTime time() const;
    QSize sizeHint() const;
    QSize minimumSizeHint() const;

    //相关函数
    explicit CDateEdit(QWidget *parent = 0);    //构造函数
    bool isNullable() const;                    //是否为空
    void setNullable(bool enable);              //设置为NULL
    void toSetNUll(bool n);                     //设置为NULL


protected:
    void showEvent(QShowEvent *event);          //虚函数:显示事件功能
    void resizeEvent(QResizeEvent *event);      //虚函数:重设事件功能
    void paintEvent(QPaintEvent *event);        //虚函数:绘制事件功能
    void keyPressEvent(QKeyEvent *event);       //虚函数:按键操作
    void mousePressEvent(QMouseEvent *event);   //虚函数:鼠标操作
    bool focusNextPrevChild(bool next);
    QValidator::State validate(QString &input, int &pos) const;

public slots:
    void setDateTime(const QDateTime &dateTime);//槽函数:设置时间与日期
    void setDate(const QDate &date);            //槽函数:设置日期
    void setTime(const QTime &time);            //槽函数:设置时间

private:
    Q_DISABLE_COPY(CDateEdit)
    class Private;
    friend class Private;
    Private* d;
};

#endif // CDATEEDIT_H
