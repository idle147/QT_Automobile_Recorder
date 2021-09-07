#include <QTime>
#include <QMovie>
#include <QMessageBox>
#include "loginwin.h"
#include "registwin.h"
#include "mainwin.h"

/*
    函数说明: 构造函数私有
*/
CLoginWin::CLoginWin()
{
    this->control = CMyController::getInstence();
    this->eyesFlag = false; //默认眼睛为关闭状态

    this->setWindowTitle(tr("登录"));    //设置窗体标题
    this->setWindowIcon(QIcon(":/images/icon.jpg"));    //生成窗口图标
    this->setFixedSize(470,470);  //设置窗口大小

    //设置QSS
    QString qss = "";
    CFileTool::readQSS(":/QSS/logAndReg.qss", qss);
    this->setStyleSheet(qss);

    //设置遮罩背景
    GifMovie = new QMovie(":/images/login2.gif");
    ground = new QLabel(this);
    ground->setMovie(GifMovie);
    GifMovie->start();

    //用户名Lab
    userNameLab = new QLabel(this);
    userNameLab->setGeometry(QRect(95,90, 60, 25));
    userNameLab->setText("账 号：");

    //用户名输入框
    userNameEdit = new QLineEdit(this);
    userNameEdit->setGeometry(QRect(160, 90, 220, 25));
    userNameEdit->setPlaceholderText(tr(" 请输入用户名!")); //占位符编辑框
    userNameEdit->setEchoMode(QLineEdit::Normal);//输入的用户名正常显示
    userNameEdit->setMaxLength(12);//最大长度是12位
    userNameEdit->setClearButtonEnabled(true);

    //密码Label
    pwdLab = new QLabel(this);
    pwdLab->setGeometry(QRect(95, 140, 60, 25));
    pwdLab->setText("密 码：");

    //密码输入框
    pwdEdit = new QLineEdit(this);
    pwdEdit->setGeometry(QRect(160, 140, 220, 25));
    pwdEdit->setPlaceholderText(" 请输入密码!");
    pwdEdit->setEchoMode(QLineEdit::Password);//输入的密码以圆点显示
    pwdEdit->setMaxLength(8);//最大长度是8位
    pwdEdit->setClearButtonEnabled(true);

    // 添加开启的action
    this->eyes = new QAction(this);
    eyes->setIcon(QIcon(":icon/view_off.png"));//设定图标
    pwdEdit->addAction(eyes, QLineEdit::TrailingPosition);


    //登录按钮
    loginBtn = new QPushButton(this);
    loginBtn->move(95,225);
    loginBtn->setText("登录");

    //退出按钮
    exitBtn = new QPushButton(this);
    exitBtn->move(200,225);
    exitBtn->setText("退出");

    //注册按钮
    regBtn = new QPushButton(this);
    regBtn->move(305,225);
    regBtn->setText("注册");

    //单击登录按钮时 执行 登录判定 槽函数；
    connect(loginBtn,&QPushButton::clicked,this,&CLoginWin::login);
    //单击退出按钮时 执行 关闭窗口 槽函数;
    connect(exitBtn,&QPushButton::clicked,this,&CLoginWin::close);
    //单击注册按钮时 执行 注册 槽函数;
    connect(regBtn,&QPushButton::clicked,this,&CLoginWin::regFun);
    //单机眼睛按钮时,切换明密文状态;
    connect(eyes, SIGNAL(triggered(bool)), this, SLOT(showKey()));
}

CLoginWin::~CLoginWin()
{
}


/*
    函数功能: 点击登录按钮时, 进行登录验证
*/
void CLoginWin::login()
{
    QString userName = this->userNameEdit->text();
    QString userKey = this->pwdEdit->text();

    //tr()函数，防止设置中文时乱码
    if(this->userNameEdit->text() == tr("") || this->pwdEdit->text() == tr(""))
    {//如果用户名为空
        QMessageBox::warning(NULL, "warning", "账号或密码不能为空", QMessageBox::Yes, QMessageBox::Yes);
    }
    else
    {
        int res = control->getUserByNameAndPwd(userName, userKey);
        if(res == NoFind)
        {   //提示登录失败
            QMessageBox::warning(NULL, "warning", "账号或密码不正确", QMessageBox::Yes, QMessageBox::Yes);
        }
        else if(res == IsFind)
        {
            //输入正确,接受
            QMessageBox::warning(NULL, "warning", "登录成功", QMessageBox::Yes, QMessageBox::Yes);
            CGetSetInfo::setUserName(userName);
            emit successLogin(userName);
            //重置表单
            this->userNameEdit->clear();// 清空输入框内容
            this->pwdEdit->clear();     // 清空密码框内容
            //跳转到主界面
            this->hide();
            CManageWin::getInstence()->findWin(e_mainWin)->show();
        }
    }
}

/*
    函数功能: 进行注册
*/
void CLoginWin::regFun()
{
    this->hide();
    CManageWin::getInstence()->findWin(e_regWin)->show();
}

/*
    函数功能: 进行明密文的转换
*/
void CLoginWin::showKey()
{
    this->eyesFlag = !eyesFlag;
    if(this->eyesFlag == true)
    {
        eyes->setIcon(QIcon(":icon/view.png"));//设定图标
        pwdEdit->setEchoMode(QLineEdit::Normal);//输入的密码正常显示
    }
    else
    {
        eyes->setIcon(QIcon(":icon/view_off.png"));//设定图标
        pwdEdit->setEchoMode(QLineEdit::Password);//输入的密码正常显示
    }
}

/*
    函数功能: 按键响应
*/
void CLoginWin::keyPressEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return )  //判断是否是回车键按下
    {
        login();   //回车执行注册
    }
}
