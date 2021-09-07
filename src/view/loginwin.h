#ifndef LOGINWIN_H
#define LOGINWIN_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QAction>
#include "../controller/myController.h"
#include "managewin.h"

class CLoginWin : public QWidget
{
    Q_OBJECT

public:
    CLoginWin();
    ~CLoginWin();
    void keyPressEvent(QKeyEvent *event);

protected:
    static int verNum;
    
private:
    CMyController * control;     //控制器单例

    QLabel *ground;              //背景窗口
    QLabel *userNameLab;         //"用户名"标签
    QLabel *pwdLab;              //"密码"标签

    QLineEdit *userNameEdit;     //用户名编辑行
    QLineEdit *pwdEdit;          //密码编辑行
    QAction *eyes;               //小眼睛控制明文密文显示

    QPushButton *loginBtn;       //登录按钮
    QPushButton *exitBtn;        //退出按钮
    QPushButton *regBtn;         //注册按钮

    QMovie *GifMovie;            //设置GIF动图背景

    bool eyesFlag;     //设定眼睛的棋子

signals:
    void successLogin(QString userId);

public slots:
    void login();       //登录验证槽函数
    void regFun();      //注册槽函数
    void showKey();     //切换明密文显示
};
#endif // LOGINWIN_H
