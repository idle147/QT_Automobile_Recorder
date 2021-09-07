#include "menulistwidget.h"
#include "controller/filetool.h"
#include "managewin.h"

CMenuListWidget::CMenuListWidget(QWidget *parent)
    : QWidget(parent)
{
    //设置QSS
    QString qss = "";
    CFileTool::readQSS(":/QSS/setMenu.qss", qss);
    this->setStyleSheet(qss);

    //界面设置
    this->setWindowFlags(Qt::FramelessWindowHint);    //无边框设置
    this->hLayout = new QHBoxLayout;

    //字体设置
    font.setPointSize(18);
    font.setFamily(QString::fromUtf8("msyh"));

    //下拉菜单的设置
    setlistWin = new QListWidget(this);
    setlistWin->setObjectName(QString::fromUtf8("setlistWin"));
    setlistWin->setFont(font);
    setlistWin->setViewMode(QListView::IconMode);   //设置为图标模式
    setlistWin->setAlternatingRowColors(true);
    setlistWin->setResizeMode(QListView::Adjust);         //图标自动调整
    addItem();

    //加入布局管理器
    this->hLayout->addWidget(setlistWin);

    //设置布局管理器
    this->setLayout(hLayout);

    //信号与槽连接
    connect(setlistWin, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(doOption(QListWidgetItem*)));
}

void CMenuListWidget::addItem()
{
    setlistWin->setIconSize(QSize(50, 50));
    //添加设置清单列表的生成
    QStringList setListInfo;
    setListInfo << QStringLiteral("返回") << QStringLiteral("回放") << QStringLiteral("照片")
                << QStringLiteral("转码") << QStringLiteral("设置") << QStringLiteral("退出");

    //存入Icon的图标地址
    QStringList iconPic;
    iconPic << QStringLiteral(":/icon/mainwindow.png") << QStringLiteral(":/icon/history.png")
            << QStringLiteral(":/icon/photo_gallery.png") << QStringLiteral(":/icon/changecode.png")
            << QStringLiteral(":/icon/settings.png") << QStringLiteral(":/icon/exit.png");

    //遍历添加ITEM数据
    for(int i = 0;i < setListInfo.length(); i++)
    {
        //通过 QListWidgetItem添加文本以及Icon数据的
        QListWidgetItem * IconItem = new QListWidgetItem(QIcon(iconPic.at(i)), setListInfo.at(i));
        setlistWin->insertItem(i, IconItem);
    }
}


void CMenuListWidget::doOption(QListWidgetItem * widgetItemSignals)
{
    emit itemClicked(widgetItemSignals);
    int indexNum = setlistWin->currentRow();
    switch (indexNum)
    {
    case 0:
    {   //跳转到主界面
        CManageWin::getInstence()->findWin(e_mainWin)->show();
        break;
    }
    case 1:
    {
        //跳转到界面“回放”
        CManageWin::getInstence()->findWin(e_hisChooseWin)->show();
        break;
    }
    case 2:
    {
        //跳转到界面“照片”
        CManageWin::getInstence()->findWin(e_pictureWin)->show();
        break;
    }
    case 3:
    {
        //跳转到界面"转码"
        CManageWin::getInstence()->findWin(e_exportWin)->show();
        break;

    }
    case 4:
    {
        //跳转到界面"设置"
        CManageWin::getInstence()->findWin(e_setWin)->show();
        break;
    }
    case 5:
    {
        //跳转到界面"退出"
        exit(0);
        break;
    }
    }
}
