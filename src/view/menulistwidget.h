#ifndef CMENULISTWIDGET_H
#define CMENULISTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QListWidget>
#include <QFont>
#include <QMessageBox>
#include <QHBoxLayout>
class CMenuListWidget: public QWidget
{
    Q_OBJECT
public:
    explicit CMenuListWidget(QWidget *parent);

private:
    QListWidget *setlistWin;            //工具列表清单
    QFont font;                         //字体设置
    QHBoxLayout *hLayout;               //布局管理器
    void addItem();                     //下拉框添加相关控件

signals:
    void itemClicked(QListWidgetItem* widgetItemSignals);   //当Item被点击时发送该信号

public slots:
    void doOption(QListWidgetItem*);    //执行操作

};

#endif // CMENULISTWIDGET_H
