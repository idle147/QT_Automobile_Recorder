#include "dateedit.h"

/************************************
    函数说明:私有定义
    函数输入:无
    函数输出:无
*************************************/
class CDateEdit::Private {
public:
    Private(CDateEdit* qq) : q(qq), null(false), nullable(false) {}

    CDateEdit* const q;

    bool null;
    bool nullable;

    void setNull(bool n) {
        null = n;
        if (null) {
            QLineEdit *edit = q->findChild<QLineEdit*>("qt_spinbox_lineedit");
            if (!edit->text().isEmpty()) {
                edit->clear();
            }
        }
    }
};

/************************************
    函数说明:继承控件的窗口
    函数输入:父类窗口
    函数输出:无
*************************************/
CDateEdit::CDateEdit(QWidget *parent) :
    QDateEdit(parent), d(new Private(this))
{

}


/************************************
    函数说明:获取日期+时间
    函数输入:无
    函数输出:日期+时间
*************************************/
QDateTime CDateEdit::dateTime() const
{
    if (d->nullable && d->null)
    {
        return QDateTime();
    }
    else
    {
        return QDateEdit::dateTime();
    }
}

/************************************
    函数说明:获取日期
    函数输入:无
    函数输出:日期
*************************************/
QDate CDateEdit::date() const
{
    if (d->nullable && d->null)
    {
        return QDate();
    }
    else
    {
        return QDateEdit::date();
    }
}

/************************************
    函数说明:获取时间
    函数输入:无
    函数输出:时间
*************************************/
QTime CDateEdit::time() const
{
    if (d->nullable && d->null)
    {
        return QTime();
    }
    else
    {
        return QDateEdit::time();
    }
}

/************************************
    函数说明:设置日期
    函数输入:时间+日期
    函数输出:无
*************************************/
void CDateEdit::setDateTime(const QDateTime &dateTime)
{
    if (d->nullable && !dateTime.isValid()) {
        d->setNull(true);
    }
    else {
        d->setNull(false);
        QDateEdit::setDateTime(dateTime);
    }
}

/************************************
    函数说明:设置日期
    函数输入:无
    函数输出:日期
*************************************/
void CDateEdit::setDate(const QDate &date)
{
    if (d->nullable && !date.isValid()) {
        d->setNull(true);
    }
    else {
        d->setNull(false);
        QDateEdit::setDate(date);
    }
}

/************************************
    函数说明:设置时间
    函数输入:无
    函数输出:时间
*************************************/
void CDateEdit::setTime(const QTime &time)
{
    if (d->nullable && !time.isValid()) {
        d->setNull(true);
    }
    else {
        d->setNull(false);
        QDateEdit::setTime(time);
    }
}

/************************************
    函数说明:判断是否为NULL
    函数输入:无
    函数输出:bool类型值
*************************************/
bool CDateEdit::isNullable() const
{
    return d->nullable;
}

/************************************
    函数说明:设置是否为NULL
    函数输入:所需设置的bool值
    函数输出:无
*************************************/
void CDateEdit::setNullable(bool enable)
{
    d->nullable = enable;
    update();
}

/************************************
    函数说明:调用私有的设置为空函数
    函数输入:所需设置的bool值
    函数输出:无
*************************************/
void CDateEdit::toSetNUll(bool n)
{
    d->setNull(n);
}

/************************************
    函数说明:获取编辑框大小
    函数输入:无
    函数输出:编辑框大小
*************************************/
QSize CDateEdit::sizeHint() const
{
    const QSize sz = QDateEdit::sizeHint();
    return QSize(sz.width() + 3, sz.height());
}

/************************************
    函数说明:获取编辑框最小尺寸
    函数输入:无
    函数输出:编辑框大小
*************************************/
QSize CDateEdit::minimumSizeHint() const
{
    const QSize sz = QDateEdit::minimumSizeHint();
    return QSize(sz.width() + 3, sz.height());
}

/************************************
    函数说明:绘制窗体
    函数输入:QShowEvent *event
    函数输出:无
*************************************/
void CDateEdit::showEvent(QShowEvent *event)
{
    QDateEdit::showEvent(event);
    d->setNull(d->null);
}

/************************************
    函数说明:重设事件
    函数输入:QResizeEvent *event
    函数输出:无
*************************************/
void CDateEdit::resizeEvent(QResizeEvent *event)
{
    QDateEdit::resizeEvent(event);
}

/************************************
    函数说明:绘制
    函数输入:QPaintEvent *event
    函数输出:无
*************************************/
void CDateEdit::paintEvent(QPaintEvent *event)
{
    d->setNull(d->null);
    QDateEdit::paintEvent(event);
}

/************************************
    函数说明:按键事件
    函数输入:QKeyEvent *event
    函数输出:无
*************************************/
void CDateEdit::keyPressEvent(QKeyEvent *event)
{
    if (d->nullable &&
            (event->key() >= Qt::Key_0) &&
            (event->key() <= Qt::Key_9) &&
            d->null) {
        setDateTime(QDateTime::currentDateTime());
    }
    if (event->key() == Qt::Key_Tab && d->nullable && d->null) {
        QAbstractSpinBox::keyPressEvent(event);
        return;
    }
    if (event->key() == Qt::Key_Backspace && d->nullable){
        QLineEdit *edit = this->findChild<QLineEdit *>("qt_spinbox_lineedit");
        if (edit->selectedText() == edit->text()) {
            setDateTime(QDateTime());
            event->accept();
            return;
        }
    }

    QDateEdit::keyPressEvent(event);
}

/************************************
    函数说明:鼠标点击事件
    函数输入:QMouseEvent *event
    函数输出:无
*************************************/
void CDateEdit::mousePressEvent(QMouseEvent *event)
{
    bool saveNull = d->null;
    QDateEdit::mousePressEvent(event);
    if (d->nullable && saveNull && calendarWidget()->isVisible()) {
        setDateTime(QDateTime::currentDateTime());
    }
}

/************************************
    函数说明:是否点击下个
    函数输入:QMouseEvent *event
    函数输出:无
*************************************/
bool CDateEdit::focusNextPrevChild(bool next)
{
    if (d->nullable && d->null){
        return QAbstractSpinBox::focusNextPrevChild(next);
    }
    else {
        return QDateEdit::focusNextPrevChild(next);
    }
}

/************************************
    函数说明:过滤器
    函数输入:输入QString 和位置int
    函数输出:QValidator::State
*************************************/
QValidator::State CDateEdit::validate(QString &input, int &pos) const
{
    if (d->nullable && d->null){
        return QValidator::Acceptable;
    }
    return QDateEdit::validate(input, pos);
}
