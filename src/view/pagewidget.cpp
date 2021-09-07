#include "pagewidget.h"
#include <QtGlobal>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QIntValidator>

CPageWidget::CPageWidget(int blockSize, QWidget *parent)
    : QWidget(parent)
{
    //QSS
    QString qss = QString(".QLabel[page=\"true\"] { padding: 1px; }")
            + QString(".QLabel[currentPage=\"true\"] { color: rgb(190, 0, 0);}")
            + QString(".QLabel[page=\"true\"]:hover { color: white; border-radius: 4px; background-color: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(53, 121, 238, 255), stop:1 rgba(0, 202, 237, 255));}");

    //界面控件设置
    this->setWindowFlags(Qt::FramelessWindowHint);    //无边框设置
    this->setStyleSheet(qss);

    horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->setSpacing(0);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

    //距离填充
    horizontalSpacer   = new QSpacerItem(45, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    //向左标签
    previousPageLabel = new QLabel("<<",this);
    previousPageLabel->setObjectName(QString::fromUtf8("previousPageLabel"));

    //向右标签
    nextPageLabel = new QLabel(">>",this);
    nextPageLabel->setObjectName(QString::fromUtf8("nextPageLabel"));

    //左边填充布局管理器标签
    leftSeparateLabel = new QLabel(this);
    leftSeparateLabel->setObjectName(QString::fromUtf8("leftSeparateLabel"));

    //右边填充布局管理器标签
    rightSeparateLabel = new QLabel(this);
    rightSeparateLabel->setObjectName(QString::fromUtf8("rightSeparateLabel"));

    //左侧页面
    leftPagesWidget = new QWidget(this);
    leftPagesWidget->setObjectName(QString::fromUtf8("leftPagesWidget"));

    //中间页面
    centerPagesWidget = new QWidget(this);
    centerPagesWidget->setObjectName(QString::fromUtf8("centerPagesWidget"));

    //右边页面
    rightPagesWidget = new QWidget(this);
    rightPagesWidget->setObjectName(QString::fromUtf8("rightPagesWidget"));

    //初始化页面标签链表
    pageLabels = new QList<QLabel *>;

    //设置选择页面的布局管理器
    pageLineEdit = new QLineEdit(this);
    pageLineEdit->setObjectName(QString::fromUtf8("pageLineEdit"));
    pageLineEdit->setMinimumSize(QSize(25, 25));
    pageLineEdit->setMaximumSize(QSize(25, 500));
    pageLineEdit->setAlignment(Qt::AlignCenter);
    pageLineEdit->setStyleSheet("background:transparent;border:none;border-bottom:1px solid black;");

    //编辑框左右文字
    label = new QLabel("第", this);
    label->setObjectName(QString::fromUtf8("label"));
    label_2 = new QLabel("页", this);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    //加入布局管理器
    horizontalLayout->addItem(horizontalSpacer);    //左边距离填充
    horizontalLayout->addWidget(previousPageLabel);
    horizontalLayout->addWidget(leftPagesWidget);
    horizontalLayout->addWidget(centerPagesWidget);
    horizontalLayout->addWidget(rightPagesWidget);
    horizontalLayout->addWidget(leftSeparateLabel);
    horizontalLayout->addWidget(rightSeparateLabel);
    horizontalLayout->addWidget(nextPageLabel);
    horizontalLayout->addWidget(label);
    horizontalLayout->addWidget(pageLineEdit);
    horizontalLayout->addWidget(label_2);
    horizontalLayout->addItem(horizontalSpacer_2);  //右边距离填充

    setBlockSize(blockSize);
    initialize();
    maxPage = 0;
    setMaxPage(1);
}


bool CPageWidget::eventFilter(QObject *watched, QEvent *e)
{
    //鼠标点击页码值
    if (e->type() == QEvent::MouseButtonRelease)
    {
        int page = -1;
        if (watched == previousPageLabel)
        {
            page = getCurrentPage() - 1;
        }
        if (watched == nextPageLabel)
        {
            page = getCurrentPage() + 1;
        }
        for (int i = 0; i < pageLabels->count(); ++i)
        {
            if (watched == pageLabels->at(i))
            {
                page = pageLabels->at(i)->text().toInt();
                break;
            }
        }
        if (page != -1)
        {
            setCurrentPage(page, true);
            return true;
        }
    }

    //键盘输入页码值
    if (watched == pageLineEdit && e->type() == QEvent::KeyRelease)
    {
        QKeyEvent *ke = static_cast<QKeyEvent *>(e);
        if (ke->key() == Qt::Key_Enter || ke->key() == Qt::Key_Return)
        {
            setCurrentPage(pageLineEdit->text().toInt(), true);
            //setMaxPage(pageLineEdit->text().toInt()); // 测试生成多个页码
            return true;
        }
    }
    return QWidget::eventFilter(watched, e);
}

int CPageWidget::getBlockSize() const
{
    return blockSize;
}

int CPageWidget::getMaxPage() const
{
    return maxPage;
}

int CPageWidget::getCurrentPage() const
{
    return currentPage;
}

void CPageWidget::setMaxPage(int page)
{
    page = qMax(page, 1);
    if (maxPage != page)
    {
        this->maxPage = page;
        this->currentPage = 1;
        updatePageLabels();
    }
}

void CPageWidget::setCurrentPage(int page, bool signalEmitted)
{
    page = qMax(page, 1);
    page = qMin(page, maxPage);

    if (page != this->currentPage)
    {
        this->currentPage = page;
        updatePageLabels();
        if (signalEmitted)
        {
            emit currentPageChanged(page);
        }
    }
}

void CPageWidget::setBlockSize(int blockSize)
{
    // 为了便于计算, block size 必须是奇数, 且最小为3
    blockSize = qMax(blockSize, 3);
    if (blockSize % 2 == 0) {
        ++blockSize;
    }
    this->blockSize = blockSize;
}


// 初始化页码的labels
// 分成三个部分, 左...中...右
void CPageWidget::initialize()
{
    //设定页面编辑框最大输入长度
    pageLineEdit->installEventFilter(this);
    pageLineEdit->setValidator(new QIntValidator(1, 10, this));

    //设置object's的名字
    nextPageLabel->setProperty("page", "true");
    previousPageLabel->setProperty("page", "true");

    //安装一个事件过滤器
    nextPageLabel->installEventFilter(this);
    previousPageLabel->installEventFilter(this);

    QHBoxLayout *leftLayout = new QHBoxLayout();
    QHBoxLayout *centerLayout = new QHBoxLayout();
    QHBoxLayout *rightLayout = new QHBoxLayout();

    leftLayout->setContentsMargins(0, 0, 0, 0);
    leftLayout->setSpacing(0);
    centerLayout->setContentsMargins(0, 0, 0, 0);
    centerLayout->setSpacing(0);
    rightLayout->setContentsMargins(0, 0, 0, 0);
    rightLayout->setSpacing(0);

    for (int i = 0; i < blockSize * 3; ++i)
    {
        QLabel *label = new QLabel(QString::number(i + 1));
        label->setProperty("page", "true");
        label->installEventFilter(this);
        pageLabels->append(label);

        if (i < blockSize)
        {
            leftLayout->addWidget(label);
        }
        else if (i < blockSize * 2)
        {
            centerLayout->addWidget(label);
        }
        else
        {
            rightLayout->addWidget(label);
        }
    }

    //设置布局管理器
    leftPagesWidget->setLayout(leftLayout);
    centerPagesWidget->setLayout(centerLayout);
    rightPagesWidget->setLayout(rightLayout);
}


void CPageWidget::updatePageLabels()
{
    leftSeparateLabel->hide();
    rightSeparateLabel->hide();

    // 以下情况为maxPageNumber小于 blockSize * 3
    if (maxPage <= blockSize * 3)
    {
        for (int i = 0; i < pageLabels->count(); i += 1)
        {
            QLabel *label = pageLabels->at(i);
            if (i < maxPage)
            {
                label->setText(QString::number(i + 1));
                label->show();
            }
            else
            {
                label->hide();
            }
            if (currentPage - 1 == i)
            {
                label->setProperty("currentPage", "true");
            }
            else
            {
                label->setProperty("currentPage", "false");
            }
            label->setStyleSheet("/**/");
        }
        return;
    }

    // 以下情况为maxPageNumber大于blockSize * 3, 所有的页码label都要显示
    // c 为 currentPage
    // n 为 block size
    // m 为 maxPage

    // 1. c ∈ [1, n + n/2 + 1]: 显示前 n * 2 个, 后 n 个: 只显示右边的分隔符
    // 2. c ∈ [m - n - n/2, m]: 显示前 n 个, 后 n * 2 个: 只显示左边的分隔符
    // 3. 显示[1, n], [c - n/2, c + n/2], [m - 2*n + 1, m]: 两个分隔符都显示

    int c = currentPage;
    int n = blockSize;
    int m = maxPage;
    int centerStartPage = 0;

    if (c >= 1 && c <= n + n / 2 + 1)
    {
        // 1. c ∈ [1, n + n/2 + 1]: 显示前 n * 2 个, 后 n 个: 只显示右边的分隔符
        centerStartPage = n + 1;
        rightSeparateLabel->show();
    }
    else if (c >= m - n - n / 2 && c <= m)
    {
        // 2. c ∈ [m - n - n/2, m]: 显示前 n 个, 后 n * 2 个: 只显示左边的分隔符
        centerStartPage = m - n - n + 1;
        leftSeparateLabel->show();
    }
    else
    {
        // 3. 显示[1, n], [c - n/2, c + n/2], [m - n + 1, m]: 两个分隔符都显示
        centerStartPage = c - n / 2;
        rightSeparateLabel->show();
        leftSeparateLabel->show();
    }

    for (int i = 0; i < n; ++i)
    {
        pageLabels->at(i)->setText(QString::number(i + 1));                     // 前面 n 个
        pageLabels->at(n + i)->setText(QString::number(centerStartPage + i));   // 中间 n 个
        pageLabels->at(3 * n - i - 1)->setText(QString::number(m - i));         // 后面 n 个
    }

    for (int i = 0; i < pageLabels->count(); ++i)
    {
        QLabel *label = pageLabels->at(i);
        int page = label->text().toInt();
        if (page == currentPage)
        {
            label->setProperty("currentPage", "true");
        }
        else
        {
            label->setProperty("currentPage", "false");
        }
        label->setStyleSheet("/**/");
        label->show();
    }
}
