#include "playerslider.h"

CPlayerSlider::CPlayerSlider(QWidget * parent)
    : QSlider(parent)
{
    m_bPressed = true;
}

void CPlayerSlider::mousePressEvent(QMouseEvent *e)
{
    m_bPressed = true;
    QSlider::mousePressEvent(e);//必须有这句，否则手动不能移动滑块
}

void CPlayerSlider::mouseMoveEvent(QMouseEvent *e)
{
    QSlider::mouseMoveEvent(e);//必须有这句，否则手动不能移动滑块
}

void CPlayerSlider::mouseReleaseEvent(QMouseEvent *e)
{
    m_bPressed = false;
    qint64 i64Pos = value();
    emit sigProgress(i64Pos);
    QSlider::mouseReleaseEvent(e);//必须有这句，否则手动不能移动滑块
}

void CPlayerSlider::setProgress(qint64 i64Progress)
{
    if(!m_bPressed)
    {
        setValue(i64Progress);
    }
}
