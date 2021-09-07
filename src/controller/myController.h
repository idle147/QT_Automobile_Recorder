#ifndef MYCONTROLLER_H
#define MYCONTROLLER_H
#include <string>
#include "../model/userModel.h"
using namespace std;

//控制器单例
class CMyController
{

public:
    //静态单例类
    static CMyController* getInstence();
    //得到用户ID和密码
    int getUserByNameAndPwd(QString &userName, QString &userPwd);
    //查询用户ID
    int queryUid(QString &uId);
    //执行注册操作
    int reg(QString &uId, QString &userName, QString &userPwd);
    //设置信息
    int setInfo(QString videoUrl, QString photoUrl, QString timeSet, QString camSet);
    //写下文件信息
    int writeTypeInfo(QString &uId, QString &date, QString &type, QString &path, QString frameNum);
    //查询设置信息
    int querySetTable(deque<string>& dSetInfo);
    //查询全部文件信息
    int queryAllFile(QString uid, QString fileType, QList<QString>& fileInfo);
    //查询时间信息
    int queryTimeFile(QString uid, QString time, QString fileType, QList<QString>& fileInfo);
    //查询视频的总帧数
    int queryVideoFrameNum(QString time);

private:
    CMyController();        //私有构造函数
    static CMyController* control;//单例指针
    CUserModel* userModel;  //使用模型
};

#endif // MYCONTROLLER_H
