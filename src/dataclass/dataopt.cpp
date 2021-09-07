#include "dataopt.h"
#include <QDebug>

CDataOpt * CDataOpt::db = nullptr;//静态变量初始化

//数据库初始化
CDataOpt::CDataOpt(string address)
{
    this->sqlDB = NULL;
    this->address = address;
    this->errMsg = NULL;
    this->pStmt = NULL;
    string str = "open database: ";
    cout << CTool::utfTogbk(str);
    this->openDB();
}

CDataOpt::~CDataOpt()
{
    cout << "close database: ";
    closeDB();//关闭数据库
}

//打开数据库
void CDataOpt::openDB()
{
    int res = sqlite3_open(this->address.c_str(), &this->sqlDB);
    resEcho(res, this->sqlDB);
}

//关闭数据库
void CDataOpt::closeDB()
{
    int res = sqlite3_close(this->sqlDB);
    resEcho(res, this->sqlDB);
}

//提示信息展示
void CDataOpt::resEcho(int res, sqlite3 *DB)
{
    if(res == SQLITE_OK)
    {
        cout <<"opearate success" << endl;
    }
    else
    {
        cout <<"opearate error, error: " << sqlite3_errmsg(DB) << endl;
        cout <<"Error Code: " << sqlite3_errcode(DB) << endl;
    }
}

int CDataOpt::execEcho(int res, char *errMsg)
{
    if (res == SQLITE_OK)
    {
        printf("Operation Success");
        return optSuccess;
    }
    else if (res == SQLITE_ABORT)
    {
        printf("Operation Abort: %s\n",errMsg);
        return optFailure;
    }
    else
    {
        printf("Operation Failure: %s\n",errMsg);
        return optOther;
    }
}

//回调函数
int CDataOpt::callback(void *pdata, int nCount, char** pValue, char** pName)
{
    /*****************************************************************************
      sqlite:每查到一条记录，就调用一次这个回调
      pdata: 是你在 sqlite3_exec 里传入的 void * 参数, 通过para参数，
             可以传入一些特殊的指针（比如类指  针、结构指针），
             然后在这里面强制转换成对应的类型（这里面是void*类型，必须强制转换成需要的类型才可用）。
      nCount: 是这一条(行)记录有多少个字段 (即这条记录有多少列)
      char ** pValue: 是个关键值，查出来的数据都保存在这里，它实际上是个1维数组
                      每一个元素都是一个 char* 值，是一个字段内容（用字符串来表示，以/0结尾）
      char ** pName: 跟pValue是对应的，表示这个字段的字段名称, 也是个1维数组
 *****************************************************************************/
    string s;
    if(getArrayLen(pValue) != 0)
    {
        for(int i = 0; i < nCount; i++)
        {
            s += pName[i];
            s += ":";
            s += pValue[i];
            s += "\n";
        }
        cout<<CTool::utfTogbk(s)<<endl;
        return 0; //继续执行sqlite3_exec()
    }
    else
    {
        s = "查无此数据";
        cout<<CTool::utfTogbk(s)<<endl;
        return 1; //中断执行sqlite3_exec()
    }
}
//执行exec操作
int CDataOpt::opearate(string& sql, bool open)
{
    int res;
    if(open == false)//不调用回调函数
    {
        res = sqlite3_exec(this->sqlDB, sql.c_str(), NULL, NULL, &this->errMsg);
        return execEcho(res, errMsg);
    }
    else//调用回调函数
    {
        //对每一条查询结果,均会调用一次回调函数
        res = sqlite3_exec(this->sqlDB, sql.c_str(), this->callback, NULL, &this->errMsg);
        return execEcho(res, errMsg);
    }
}

//查询用户信息表,并存到deque<string>容器内
bool CDataOpt::queryUsr(QString &sql, deque<string> &user)
{
    string temp = "";
    const char *zTail;
    //调用sqlite3_prepare()将SQL语句编译为sqlite内部一个结构体(sqlite3_stmt).
    //该结构体中包含了将要执行的的SQL语句的信息.
    if (sqlite3_prepare_v2(this->sqlDB, sql.toStdString().c_str(), -1, &this->pStmt, &zTail) == SQLITE_OK)
    {
        /*
         调用sqlite3_step(),这时候SQL语句才真正执行.
         注意该函数的返回值,SQLITE_DONE和SQLITE_ROW都是表示执行成功, SQLITE_DONE表示没有查询结果,
         UPDATE,INSERT这些SQL语句都是返回SQLITE_DONE
         SELECT查询语句在查询结果不为空的时候返回SQLITE_ROW,在查询结果为空的时候返回SQLITE_DONE.
       */
        //查询结果不为空,则存如数组内
        while(sqlite3_step(this->pStmt) == SQLITE_ROW)
        {
            temp = (char *)sqlite3_column_text(this->pStmt, 0);//const unsign char* 强制类型转换为char*
            user.push_back(temp); //添加用户账号
            temp = (char *)sqlite3_column_text(this->pStmt, 1);//const unsign char* 强制类型转换为char*
            user.push_back(temp); //添加用户名
            temp = (char *)sqlite3_column_text(this->pStmt, 2);//const unsign char* 强制类型转换为char*
            user.push_back(temp); //添加用户密码
            temp = to_string(sqlite3_column_int(this->pStmt, 3));//int类型强制类型转换为int类型
            user.push_back(temp); //添加用户状态
        }
        sqlite3_finalize(this->pStmt);//sqlite3_finalize()来释放stmt占用的内存
        return true; //表示sql语句执行成功
    }
    return false; //表示sql语句执行失败
}

//查询设置信息表,并存到deque容器中
bool CDataOpt::querySetTable(string &sql, deque<string> &dSetInfo)
{
    string temp = "";
    const char *zTail;
    //调用sqlite3_prepare()将SQL语句编译为sqlite内部一个结构体(sqlite3_stmt).
    //该结构体中包含了将要执行的的SQL语句的信息.
    if (sqlite3_prepare_v2(this->sqlDB, sql.c_str(), -1, &this->pStmt, &zTail) == SQLITE_OK)
    {
        /*
          调用sqlite3_step(),这时候SQL语句才真正执行.
          注意该函数的返回值,SQLITE_DONE和SQLITE_ROW都是表示执行成功, SQLITE_DONE表示没有查询结果,
          UPDATE,INSERT这些SQL语句都是返回SQLITE_DONE
          SELECT查询语句在查询结果不为空的时候返回SQLITE_ROW,在查询结果为空的时候返回SQLITE_DONE.
        */
        //查询结果不为空,则存如数组内
        while(sqlite3_step(this->pStmt) == SQLITE_ROW)
        {
            temp = to_string(sqlite3_column_int(this->pStmt, 0));//int类型强制类型转换为int类型
            dSetInfo.push_back(temp); //添加主键的信息
            temp = (char *)sqlite3_column_text(this->pStmt, 1);//const unsign char* 强制类型转换为char*
            dSetInfo.push_back(temp); //视频存储位置的信息
            temp = (char *)sqlite3_column_text(this->pStmt, 2);//const unsign char* 强制类型转换为char*
            dSetInfo.push_back(temp); //添加图片存储位置的信息
            temp = (char *)sqlite3_column_text(this->pStmt, 3);//const unsign char* 强制类型转换为char*
            dSetInfo.push_back(temp); //添加采集时间间隔的信息
            temp = (char *)sqlite3_column_text(this->pStmt, 4);//const unsign char* 强制类型转换为char*
            dSetInfo.push_back(temp); //添加摄像头配置的信息
        }
        sqlite3_finalize(this->pStmt);//sqlite3_finalize()来释放stmt占用的内存
        return true; //表示sql语句执行成功
    }
    return false; //表示sql语句执行失败
}

//函数说明：查询类型表
bool CDataOpt::querySourceTable(QString &sql, QList<QString> &fileInfo)
{
    string temp = "";
    const char *zTail;
    //调用sqlite3_prepare()将SQL语句编译为sqlite内部一个结构体(sqlite3_stmt).
    //该结构体中包含了将要执行的的SQL语句的信息.
    if (sqlite3_prepare_v2(this->sqlDB, sql.toStdString().c_str(), -1, &this->pStmt, &zTail) == SQLITE_OK)
    {
        /*
          调用sqlite3_step(),这时候SQL语句才真正执行.
          注意该函数的返回值,SQLITE_DONE和SQLITE_ROW都是表示执行成功, SQLITE_DONE表示没有查询结果,
          UPDATE,INSERT这些SQL语句都是返回SQLITE_DONE
          SELECT查询语句在查询结果不为空的时候返回SQLITE_ROW,在查询结果为空的时候返回SQLITE_DONE.
        */
        //查询结果不为空,则存如数组内
        while(sqlite3_step(this->pStmt) == SQLITE_ROW)
        {
            temp = to_string(sqlite3_column_int(this->pStmt, 0));//int类型强制类型转换为int类型
            fileInfo.append(QString::fromStdString(temp)); //添加主键的信息
            temp = (char *)sqlite3_column_text(this->pStmt, 1);//const unsign char* 强制类型转换为char*
            fileInfo.append(QString::fromStdString(temp)); //视频存储位置的信息
            temp = (char *)sqlite3_column_text(this->pStmt, 2);//const unsign char* 强制类型转换为char*
            fileInfo.append(QString::fromStdString(temp)); //添加图片存储位置的信息
            temp = (char *)sqlite3_column_text(this->pStmt, 3);//const unsign char* 强制类型转换为char*
            fileInfo.append(QString::fromStdString(temp)); //添加采集时间间隔的信息
            temp = (char *)sqlite3_column_text(this->pStmt, 4);//const unsign char* 强制类型转换为char*
            fileInfo.append(QString::fromStdString(temp)); //添加摄像头配置的信息
        }
        sqlite3_finalize(this->pStmt);//sqlite3_finalize()来释放stmt占用的内存
        return true; //表示sql语句执行成功
    }
    return false; //表示sql语句执行失败
}

//函数说明：查询文件信息数量表
int CDataOpt::queryFileNumTable(QString &sql)
{
    /*
        sqlite3_get_table主要是用于非回调的方式进行select查询，参数如下；
        参数1：打开数据库得到的指针；
        参数2：一条sql语句，跟sqlite3_exec中一样；
        参数3：查询的数据结果，他是一个指针数组，内存分布为：字段名称，后面是紧接着是每个字段的值；
        参数4：查询到的数据条数，（行数）；
        参数5：查询到的字段数，（列数）；
        参数6：错误信息
    */
    int row, column;
    char **dbResult; //是 char ** 类型，两个*号
    QString index;

    int res = sqlite3_get_table(this->sqlDB, sql.toStdString().c_str(), &dbResult, &row, &column, &errMsg);

    if(res == SQLITE_OK && row > 0)
    {
        index = dbResult[1];
        return index.toInt();
    }
    return -1;
}

//获取数据库指针
sqlite3* CDataOpt::getDB()
{
    return this->sqlDB;
}
//获取状态标识
sqlite3_stmt* CDataOpt::getStmt()
{
    return this->pStmt;
}
