#include "managewin.h"

/*
    函数说明:获取单例单数
*/
CManageWin* CManageWin::getInstence()
{
    //static 修饰的静态局部变量只执行初始化一次
    /*************************************
    这种实现方式利用了static修改函数内部的变量，当第一次调用GetInstance函数时，系统将构造一个CManageWin对象，
    在后续再次调用这个函数时，系统不再执行这个语句，也就不会再构造CManageWin类对象了，而直接返回instance本身。
    另外，当CManageWin类对象生命周期结束时，对象会自动调用析构函数销毁，这里也就不存在申请资源之类的了，
    需要注意的是GetInstance()函数返回的是引用，这样就不会调用拷贝构造函数了，使用时也应该声明CManageWin的引用，如下：
    **************************************/
    static CManageWin instance;
    return &instance;
}


/*
    函数说明:管理窗口
*/
CManageWin::CManageWin()
{
    //标识符初始化
    this->flag = false;
}

/*
    函数功能: 加入窗口
*/
void CManageWin::addWin()
{
    //窗口新建对象
    this->mainWin = new CMainWin();
    this->loginWin = new CLoginWin();
    this->regWin = new CRegistWin();
    this->hisChooseWin = new CHisChoose();
    this->pictureWin = new CPictureWin();
    this->exportWin = new CExportWin();

    //窗口加入map
    this->winMap[e_mainWin] = mainWin;
    this->winMap[e_regWin] = regWin;
    this->winMap[e_loginWin] = loginWin;
    this->winMap[e_hisChooseWin] = hisChooseWin;
    this->winMap[e_pictureWin] = pictureWin;
    this->winMap[e_exportWin] = exportWin;

    //标识符设为true
    flag = true;
}

/*
    函数说明:得到相应的标识符
*/
bool CManageWin::getFlag()
{
    return CManageWin::getInstence()->flag;
}

/*
    函数说明:重启主窗口
*/
void CManageWin::rebootMainWin()
{
    delete mainWin;
    this->mainWin = new CMainWin();
    this->winMap[e_mainWin] = mainWin;
}

/*
    函数功能: 返回对应的窗口
*/
QWidget *CManageWin::findWin(int key)
{
    return winMap[key];
}

/*
    函数说明:得到单例指针
*/
map<int, QWidget *> &CManageWin::getWinMap()
{
    return this->winMap;
}

/*
    函数说明:加入设置
*/
void CManageWin::addSet()
{
    //窗口新建对象
    this->setWin = new CSetWin();
    //窗口加入map
    this->winMap[e_setWin] = setWin;
}
