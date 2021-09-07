#ifndef REGISTWIN_H
#define REGISTWIN_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QAction>
#include <QButtonGroup>
#include <controller/myController.h>


class CRegistWin : public QWidget
{
    Q_OBJECT

public:
    CRegistWin();
    void keyPressEvent(QKeyEvent *event);
    ~CRegistWin();


private:
    CMyController * control;     //控制器单例

    QMovie *GifMovie;            //设置GIF动图背景

    QPushButton *resBtn;         //注册按钮
    QPushButton *exitBtn;        //退出按钮

    QLabel *IdNumLab;            //"用户编号"标签
    QLabel *userNameLab;         //"用户名"标签
    QLabel *pwdLab;              //"密码"标签
    QLabel *rpwdLab;             //"确认密码"标签
    QLabel *ground;              //背景窗口

    QLineEdit *IdNumEdit;        //"用户数量"编辑框
    QLineEdit *userNameEdit;     //"输入用户名"编辑框
    QLineEdit *pwdEdit;          //"输入密码"编辑框
    QAction *pwdEyes;            //"输入密码"编辑框小眼睛
    QLineEdit *rpwdEdit;         //"重新输入密码"编辑框
    QAction *rpwdEyes;           //"输入密码"编辑框小眼睛

    bool pwdEyesFlag;            //输入密码标识符
    bool rpwdEyesFlag;           //重新输入密码标识符

public slots:
    void resetFun();            //重设函数
    void exitFun();             //退出函数
    void doRegFun();            //注册函数
    void pwdShowKey();          //密钥显示函数
    void rpwdShowKey();         //密钥重显示函数

};
#endif // REGISTWIN_H
