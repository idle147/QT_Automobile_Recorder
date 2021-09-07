#ifndef MANAGEWIN_H
#define MANAGEWIN_H
#include <QMap>
#include "startwin.h"   //启动窗口
#include "loginwin.h"   //登录窗口
#include "registwin.h"  //注册窗口
#include "mainwin.h"    //主窗口
#include "setwin.h"     //设置窗口
#include "hischoosewin.h"  //回放选择窗口
#include "picturewin.h" //照片选择窗口
#include "exportwin.h"  //导出界面

//定义窗口枚举类型
enum e_winfamily { e_regWin = 1, e_loginWin,
                   e_mainWin,      e_setWin, e_hisChooseWin,
                   e_pictureWin,   e_exportWin};


class CManageWin
{
public:
    static CManageWin* getInstence();
    QWidget* findWin(int key);       //得到相对应的窗口值
    map<int, QWidget*>& getWinMap(); //得到map容器的值
    void addSet();                   //加入设置窗口
    void addWin();                   //加入窗口
    static bool getFlag();           //获取标识符
    void rebootMainWin();            //重启主界面

private:
    bool flag;      //用以判断是否加入了窗口
    CManageWin();   //私有构造函数，不允许使用者自己生成对象
    static CManageWin* m_instance;//静态成员变量
    map<int, QWidget*> winMap;

    //相关窗口
    QWidget* setWin;
    QWidget* mainWin;
    QWidget* loginWin;
    QWidget* regWin;
    QWidget* hisChooseWin;
    QWidget* pictureWin;
    QWidget* exportWin;

};
#endif // MANAGEWIN_H
