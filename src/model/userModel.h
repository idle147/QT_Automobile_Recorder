#ifndef MYMODEL_H
#define MYMODEL_H
#include <string>
#include "../dataclass/dataopt.h"
using namespace std;
#define IsFind 1
#define NoFind 0
#define SqlError -1

//单例类:用户模式
class CUserModel
{
public:
    //用户单例函数
    static CUserModel* getInstence();
    //选择用户名字和密钥
    int selectUserByNameAndPwd(QString &userName, QString &userPwd);
    //查询用户ID
    int queryUid(QString& uId);
    //执行注册语句
    int reg(QString&uId, QString& userName, QString& userPwd);
    //设置信息查询
    int setInfo(QString &videoUrl, QString &photoUrl, QString &timeSet, QString &camSet);
    //查询设置表
    int querySetTable(deque<string>& dSetInfo);
    //写下类型信息
    int writeTypeInfo(QString &uId, QString &date, QString &type, QString path, QString frameNum);
    //查询所有文件
    int queryAllFile(QString &uId, QString &fileType, QList<QString> &fileInfo);
    //查询时间文件
    int queryTimeFile(QString &uId,QString &time, QString &fileType, QList<QString> &fileInfo);
    //查询视频帧总数
    int queryVideoFrameNum(QString& time);

private:
    CUserModel();
    static CUserModel* userModel;
    CDataOpt *DB; //实例化数据库单例
};

#endif // MYMODEL_H
