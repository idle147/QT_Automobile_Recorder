#ifndef DATAOPT_H
#define DATAOPT_H
#include <iostream>
#include <string>
#include <deque>
#include "sqlite3.h"
#include "../controller/ctool.h"
using namespace std;


#define optFailure -99
#define optSuccess 1
#define optOther 2
class CDataOpt
{
public:
    //定义静态单例函数(直接设为内联函数)
    static CDataOpt *getInstence(string dbPath)
    {
        //creat a unique object
        if(CDataOpt::db == nullptr)
        {
            CDataOpt::db = new CDataOpt(dbPath);
        }
        return CDataOpt::db;
    }
private:
    CDataOpt(string address); //构造函数,打开数据库
    static CDataOpt *db;      //定义单例类指针

public:
    ~CDataOpt();             //析构函数,关系数据库
    void openDB();           //打开数据库
    void closeDB();          //关闭数据库

    //设置回调函数
    static int callback(void *pdata, int col, char **value, char **name);

    //sqlit3_exec操作数据库
    int opearate(string &sql, bool open);

    //查询用户信息表内全部结果,并存储到向量容器内
    bool queryUsr(QString &sql, deque<string>& user);

    //查询用户信息表内全部结果,并存储到向量容器内
    bool querySetTable(string &sql, deque<string>& dSetInfo);

    //查询fileTable文件保存表内的全部结果,并存储到容器类
    bool querySourceTable(QString &sql, QList<QString> &fileInfo);

    //查询frameNum
    int queryFileNumTable(QString &sql);

    //错误的结果展示
    static void resEcho(int res, sqlite3 *sqlDB);

    //回声错误判单
    static int execEcho(int res, char *errMsg);

    sqlite3_stmt* getStmt();  //返回状态标识
    sqlite3* getDB();       //获得数据库指针

private:
    sqlite3 *sqlDB;     //数据库指针
    string address;     //数据库地址
    char *errMsg;       //错误标识
    sqlite3_stmt* pStmt; //状态标识
};

#endif // DATAOPT_H
