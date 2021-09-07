#ifndef CPAGEWIDGET_H
#define CPAGEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QList>
#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>

class CPageWidget : public QWidget
{
    Q_OBJECT
public:
    //导出窗口
    explicit CPageWidget(int blockSize, QWidget *parent);
    //得到块大小
    int getBlockSize() const;
    //得到最多页面
    int getMaxPage() const;
    //得到当前页面
    int getCurrentPage() const;

    // 其他组件只需要调用这两个函数即可
    void setMaxPage(int maxPage); // 当总页数改变时调用
    void setCurrentPage(int currentPage, bool signalEmitted = false); // 修改当前页时调用

protected:
    virtual bool eventFilter(QObject *watched, QEvent *e);

signals:
    //当当前页面被改变时发射信号
    void currentPageChanged(int page);

private:
    int blockSize;
    int maxPage;
    int currentPage;
    //设置块尺寸
    void setBlockSize(int blockSize);
    //更新标签页
    void updatePageLabels();
    //初始化
    void initialize();
    QList<QLabel*> *pageLabels;

private:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;

    QWidget *leftPagesWidget;
    QWidget *centerPagesWidget;
    QWidget *rightPagesWidget;

    QLabel *previousPageLabel;
    QLabel *leftSeparateLabel;
    QLabel *rightSeparateLabel;
    QLabel *nextPageLabel;
    QLabel *label;
    QLabel *label_2;

    QLineEdit *pageLineEdit;

    QSpacerItem *horizontalSpacer;
};

#endif // CPAGEWIDGET_H
