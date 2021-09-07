#include <QMovie>
#include <QMessageBox>
#include <QKeyEvent>
#include "registwin.h"
#include "managewin.h"

/*
    函数说明:构造函数
*/
CRegistWin::CRegistWin()
{
    this->control = CMyController::getInstence();

    //默认眼睛为关闭状态
    this->pwdEyesFlag = false;
    this->rpwdEyesFlag = false;

    this->setFixedSize(470,470);  //设置窗口大小
    this->setWindowTitle(tr("登录")); //设置窗体标题
    this->setWindowIcon(QIcon(":/images/icon.jpg"));//生成窗口图标

    //设置QSS
    QString qss = "";
    CFileTool::readQSS(":/QSS/logAndReg.qss", qss);
    this->setStyleSheet(qss);

    //设置遮罩背景
    GifMovie = new QMovie(":/images/login2.gif");
    ground = new QLabel(this);
    ground->setMovie(GifMovie);
    GifMovie->start();

    //确定注册按钮
    resBtn = new QPushButton(this);
    resBtn->setGeometry(QRect(130 , 260, 75, 25));
    resBtn->setText("注册");

    //退出按钮
    exitBtn = new QPushButton(this);
    exitBtn->setGeometry(QRect(270, 260, 75, 25));
    exitBtn->setText("退出");

    //账号标签
    IdNumLab = new QLabel(this);
    IdNumLab->setGeometry(QRect(70, 40, 85, 25));
    IdNumLab->setText("账    号:");
    IdNumLab->setStyleSheet("color:white;");//设置字体颜色为白色

    //"账号"编辑框
    IdNumEdit = new QLineEdit(this);
    IdNumEdit->setGeometry(QRect(180, 40, 220, 25));
    IdNumEdit->setMaxLength(20);
    IdNumEdit->setClearButtonEnabled(true);

    //用户名标签
    userNameLab = new QLabel(this);
    userNameLab->setGeometry(QRect(70, 90, 85, 25));
    userNameLab->setText("用 户 名:");
    userNameLab->setStyleSheet("color:white;");//设置字体颜色为白色

    //"输入用户名"编辑框
    userNameEdit = new QLineEdit(this);
    userNameEdit->setGeometry(QRect(180, 90, 220, 25));
    userNameEdit->setMaxLength(12);//最大长度设置为16位
    userNameEdit->setClearButtonEnabled(true);

    //"密码"标签
    pwdLab = new QLabel(this);
    pwdLab->setObjectName(QString::fromUtf8("pwdLab"));
    pwdLab->setGeometry(QRect(70, 140, 85, 25));
    pwdLab->setText("密    码:");
    pwdLab->setStyleSheet("color:white;");//设置字体颜色为白色
    //"输入密码"小眼睛
    pwdEyes = new QAction(this);
    pwdEyes->setIcon(QIcon(":icon/view_off.png"));//设定图标
    //"输入密码"编辑框
    pwdEdit = new QLineEdit(this);
    pwdEdit->setGeometry(QRect(180, 140, 220, 25));
    pwdEdit->setEchoMode(QLineEdit::Password);//输入的密码以圆点显示
    pwdEdit->setMaxLength(16);//最大长度设置为16位
    pwdEdit->addAction(pwdEyes, QLineEdit::TrailingPosition);
    pwdEdit->setClearButtonEnabled(true);

    //"确认密码"标签
    rpwdLab = new QLabel(this);
    rpwdLab->setGeometry(QRect(70, 190, 85, 25));
    rpwdLab->setText("确认密码:");
    rpwdLab->setStyleSheet("color:white;");//设置字体颜色为白色
    //"确认密码"小眼睛
    rpwdEyes = new QAction(this);
    rpwdEyes->setIcon(QIcon(":icon/view_off.png"));//设定图标
    //"重新输入密码"编辑框
    rpwdEdit = new QLineEdit(this);
    rpwdEdit->setGeometry(QRect(180, 190, 220, 25));
    rpwdEdit->setEchoMode(QLineEdit::Password);//输入的密码以圆点显示
    rpwdEdit->setMaxLength(16);//最大长度设置为16位
    rpwdEdit->addAction(rpwdEyes, QLineEdit::TrailingPosition);
    rpwdEdit->setClearButtonEnabled(true);

    //槽函数连接
    connect(resBtn,  SIGNAL(clicked()),       this, SLOT(doRegFun()));  //点击注册按钮的槽函数
    connect(exitBtn, SIGNAL(clicked()),       this, SLOT(exitFun()));  //点击重置按钮的槽函数
    connect(pwdEyes, SIGNAL(triggered(bool)), this, SLOT(pwdShowKey())); //密码编辑框,单击眼睛按钮时,切换明密文状态;
    connect(rpwdEyes,SIGNAL(triggered(bool)), this, SLOT(rpwdShowKey())); //确认密码编辑栏,单击眼睛按钮时,切换明密文状态;
}

/*
    函数说明:析构删除函数
*/
CRegistWin::~CRegistWin()
{
    exitFun();
}

/*
    函数功能: 按键响应
*/
void CRegistWin::keyPressEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return )  //判断是否是回车键按下
    {
        doRegFun();   //回车执行注册
    }
    else if(event->key() == Qt::Key_End)
    {
        exitFun();   //执行退出功能
    }
}


/*
    函数功能:重置
    输入/输出:无
*/
void CRegistWin::resetFun()
{
    IdNumEdit->clear();       //"用户ID"编辑框清空
    userNameEdit->clear();    //"输入用户名"编辑框清空
    pwdEdit->clear();         //"输入密码"编辑框清空
    rpwdEdit->clear();        //"重新输入密码"编辑框清空
}


/*
    函数功能:退出窗口
*/
void CRegistWin::exitFun()
{
    resetFun();
    this->hide(); //隐藏本窗口
    //进入登录窗口
    CManageWin::getInstence()->findWin(e_loginWin)->show();
}


/*
    函数功能:注册函数
    输入/输出:无
*/
void CRegistWin::doRegFun()
{
    QString qUId = this->IdNumEdit->text();
    QString qUserName = this->userNameEdit->text();
    QString qUserKey = this->pwdEdit->text();

    string uId = qUId.toStdString();
    string userName = qUserName.toStdString();
    string userKey = qUserKey.toStdString();
    //账号长度不小于8位,且不大于20位
    if(uId.length() < 8 || uId.length() > 20)
    {
        QMessageBox::warning(NULL, "warning", "账号长度限制8-20位(1个汉字3位)", QMessageBox::Yes);
        this->IdNumEdit->clear();// 清空输入框内容
        return;
    }
    //账号不能重复
    else if(this->control->queryUid(qUId) != NoFind)
    {
        QMessageBox::information(NULL, "tips:","账号重复,请重新输入", QMessageBox::Yes);
        this->IdNumEdit->clear();// 清空输入框内容
    }
    //用户名必须为中文或者英文
    else if(CTool::judgeCNorEN(userName) == false)
    {
        QMessageBox::warning(NULL, "warning", "用户名必须为中文或者英文", QMessageBox::Yes);
        this->userNameEdit->clear();// 清空输入框内容
    }
    //用户名长度必须为6-12位
    else if(userName.length() < 5 || userName.length() > 13)
    {
        QMessageBox::warning(NULL, "warning", "用户名长度必须为6-12位(1个中文占3位)", QMessageBox::Yes);
        this->userNameEdit->clear();// 清空输入框内容
    }
    //密码必须为大小写英文字符或数字
    else if(CTool::judgeNumOrEN(userKey) == false)
    {
        QMessageBox::warning(NULL, "warning", "密码必须为大小写英文字符或数字", QMessageBox::Yes);
        this->pwdEdit->clear(); //清空密码操作
    }
    //密码长度必须位6-16位
    else if(userKey.length() < 6 || userKey.length() > 16)
    {
        QMessageBox::warning(NULL, "warning", "密码长度必须为6-16位", QMessageBox::Yes);
        this->pwdEdit->clear(); //清空密码操作
    }
    //确认密码需与注册密码相同
    else if(qUserKey != this->rpwdEdit->text())
    {
        QMessageBox::warning(NULL, "warning", "确认密码需与注册密码相同", QMessageBox::Yes);
        this->rpwdEdit->clear(); //清空密码操作
    }
    //注册成功
    else
    {
        if(this->control->reg(qUId, qUserName, qUserKey) == optSuccess)
        {
            QMessageBox::information(NULL, "tips:","注册成功", QMessageBox::Yes);
            //关闭注册窗口, 返回登录窗口
            this->hide();
            this->resetFun();
            CManageWin::getInstence()->findWin(e_loginWin)->show();
        }
        else
        {
            QMessageBox::information(NULL, "tips:","注册失败", QMessageBox::Yes);
        }
    }
}

/*
    函数说明:小眼睛的变化(密码)
*/
void CRegistWin::pwdShowKey()
{
    this->pwdEyesFlag = !pwdEyesFlag;
    if(pwdEyesFlag == true)
    {
        pwdEyes->setIcon(QIcon(":icon/view.png"));//设定图标
        pwdEdit->setEchoMode(QLineEdit::Normal);//输入的密码正常显示
    }
    else
    {
        pwdEyes->setIcon(QIcon(":icon/view_off.png"));//设定图标
        pwdEdit->setEchoMode(QLineEdit::Password);//输入的密码正常显示
    }
}
/*
    函数说明:小眼睛的变化(确认密码)
*/
void CRegistWin::rpwdShowKey()
{
    this->rpwdEyesFlag = !rpwdEyesFlag;
    if(rpwdEyesFlag == true)
    {
        rpwdEyes->setIcon(QIcon(":icon/view.png"));//设定图标
        rpwdEdit->setEchoMode(QLineEdit::Normal);//输入的密码正常显示
    }
    else
    {
        rpwdEyes->setIcon(QIcon(":icon/view_off.png"));//设定图标
        rpwdEdit->setEchoMode(QLineEdit::Password);//输入的密码正常显示
    }
}

