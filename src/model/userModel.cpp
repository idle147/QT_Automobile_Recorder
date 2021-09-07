#include "userModel.h"
#include <QDebug>
CUserModel * CUserModel::userModel = nullptr;   //单例类指针初始化

CUserModel::CUserModel()
{
    this->DB = CDataOpt::getInstence("../dataBase/recordDB"); //初始化数据库单例
}

CUserModel *CUserModel::getInstence()
{
    if(userModel == nullptr)
    {
        CUserModel::userModel = new CUserModel;
    }
    return userModel;
}

//查询用户名和账户是否存在
int CUserModel::selectUserByNameAndPwd(QString &userName, QString &userPwd)
{
    QString sql = "SELECT * FROM usr WHERE uId = \"" + userName + "\" AND pwd = \"" + userPwd +"\";"; //输入数据库语句
    deque<string> user;
    if(DB->queryUsr(sql, user))
    {
        //如果能够执行
        if(user.empty())
        {
            user.deque<string>::~deque(); //调用析构函数,结束容器
            return NoFind; //为空表示未找到
        }
        user.deque<string>::~deque(); //调用析构函数, 结束容器
        return IsFind; //不为空表示找到

    }
    else
    {
        //如果不能够执行
        cerr << "sql语句出错" << endl;
        return SqlError;
    }
}

//查询uId是否存在
int CUserModel::queryUid(QString &uId)
{
    //查询数据库内是否有重复名字的
    QString sql =  "SELECT * FROM usr WHERE uId = \"" + uId + "\";";
    deque<string> user;
    if(DB->queryUsr(sql, user))
    {
        //如果能够执行
        if(user.empty())
        {
            user.deque<string>::~deque(); //调用析构函数,结束容器
            return NoFind; //为空表示未找到
        }
        user.deque<string>::~deque(); //调用析构函数, 结束容器
        return IsFind; //不为空表示找到

    }
    else
    {
        //如果不能够执行
        cerr << "sql语句出错" << endl;
        return SqlError;
    }
}

//进行注册
int CUserModel::reg(QString& uId, QString &userName, QString &userPwd)
{
    //开辟sql语句空间
    QString sql = QString("INSERT INTO usr (uId, uName, pwd, state) VALUES(\"%1\", \"%2\", \"%3\", 1);").arg(uId).arg(userName).arg(userPwd);
    string stringSql = sql.toStdString();
    //往注册表内插入相关信息
    return this->DB->opearate(stringSql, false);
}

//函数说明：设置信息写入数据库
int CUserModel::setInfo(QString &videoUrl, QString &photoUrl, QString &timeSet, QString &camSet)
{
    deque<string> dSetInfo;
    QString sql;
    if(querySetTable(dSetInfo) == IsFind)
    {
        //找到则调用更新数据库语句
        sql = QString("UPDATE setTable SET videoPath = \'%1\', picPath = \'%2\', time = \'%3\', camSet = \'%4\' WHERE sType = 1;").arg(videoUrl).arg(photoUrl).arg(timeSet).arg(camSet);

    }
    else
    {
        //没有找到则调用插入数据库语句
        sql = QString("INSERT INTO setTable VALUES (1, \'%1\',\'%2\',\'%3\',\'%4\');").arg(videoUrl).arg(photoUrl).arg(timeSet).arg(camSet);
    }
    querySetTable(dSetInfo);
    string s = sql.toStdString();
    int temp = this->DB->opearate(s, false);

    //往注册表内插入相关信息
    return temp;
}

//查询设置表的信息
int CUserModel::querySetTable(deque<string>& dSetInfo)
{
    //查询数据库内是否有重复名字的
    string sql =  "SELECT * FROM setTable WHERE sType = 1;";
    if(DB->querySetTable(sql, dSetInfo))
    {
        //如果能够执行
        if(dSetInfo.empty())
        {
            dSetInfo.deque<string>::~deque(); //调用析构函数,结束容器
            return NoFind; //为空表示未找到
        }
        return IsFind; //不为空表示找到
    }
    else
    {
        //如果不能够执行
        cerr << "sql语句出错" << endl;
        return SqlError;
    }
}

/*
    函数说明：查询所有文件
*/
int CUserModel::queryAllFile(QString &uId, QString &fileType, QList<QString> &fileInfo)
{
    //清空链表
    fileInfo.clear();
    QString sql;
    if(fileType == "photo")
    {
         sql = QString("SELECT * FROM fileTable WHERE uId = \'%1\' AND (type = 'photo' OR type = 'screenShoot');").arg(uId);
    }
    else
    {
       sql = QString("SELECT * FROM fileTable WHERE uId = \'%1\' AND type = \'%2\';").arg(uId).arg(fileType);
    }
    if(DB->querySourceTable(sql, fileInfo))
    {
        //如果能够执行
        if(fileInfo.empty())
        {
            fileInfo.clear();       //清空指针列表
            return NoFind;          //为空表示未找到
        }
        return IsFind; //不为空表示找到
    }
    else
    {
        //如果不能够执行
        cerr << "sql语句出错" << endl;
        return SqlError;
    }
}

/*
    函数功能: 查询所选时间,特定用户拥有的特定类型的文件
*/
int CUserModel::queryTimeFile(QString &uId, QString &time, QString &fileType, QList<QString> &fileInfo)
{
    QString sql =  QString("SELECT * FROM fileTable WHERE uId = \'%1\' AND data LIKE \'%2\' AND type = \'%3\';").arg(uId).arg(time).arg(fileType);
    //清空链表
    fileInfo.clear();
    if(DB->querySourceTable(sql, fileInfo))
    {
        //如果能够执行
        if(fileInfo.empty())
        {
            fileInfo.clear();       //清空指针列表
            return NoFind;          //为空表示未找到
        }
        return IsFind; //不为空表示找到
    }
    else
    {
        //如果不能够执行
        cerr << "sql语句出错" << endl;
        return SqlError;
    }
}

/*
    函数说明：查询所有视频帧数
*/
int CUserModel::queryVideoFrameNum(QString& time)
{
    QString sql =  QString("SELECT frameNum FROM fileTable WHERE data = \'%1\' AND type = 'video';").arg(time);
    return DB->queryFileNumTable(sql);
}

/*
    函数说明：写下文件信息
*/
int CUserModel::writeTypeInfo(QString &uId, QString &date, QString &type, QString path, QString frameNum)
{
    if(uId.length() == 0)
    {
        uId = "admin";
    }
    QString sql = QString("INSERT INTO fileTable VALUES (NULL,\'%1\',\'%2\',\'%3\',\'%4\', %5);")
            .arg(uId).arg(type).arg(date).arg(path).arg(frameNum);

    string s = sql.toStdString();
    //往注册表内插入相关信息
    return this->DB->opearate(s, false);
}

