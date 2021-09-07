#include "myController.h"
CMyController * CMyController::control = nullptr;

/*
    函数说明: 得到单例指针
*/
CMyController *CMyController::getInstence()
{
    if(control == nullptr)
    {
        CMyController::control = new CMyController;
    }
    return control;
}

/*
    函数说明: 得到用户名和密码
*/
int CMyController::getUserByNameAndPwd(QString &userName, QString &userPwd)
{
    //model function
    return userModel->selectUserByNameAndPwd(userName, userPwd);
}

/*
    函数说明: 进行注册
*/
int CMyController::reg(QString &uId, QString &userName, QString &userPwd)
{
    //model function
    //return userModel->setUserByNameAndPwd(userName, userPwd);
    return this->userModel->reg(uId, userName, userPwd);
}

/*
    函数说明: 得到单例指针
*/
int CMyController::setInfo(QString videoUrl, QString photoUrl, QString timeSet, QString camSet)
{
    return this->userModel->setInfo(videoUrl, photoUrl, timeSet, camSet);
}

/*
    函数说明：写下文件类型信息
*/
int CMyController::writeTypeInfo(QString &uId, QString &date, QString &type, QString &path, QString frameNum)
{
    return this->userModel->writeTypeInfo(uId, date, type, path, frameNum);
}

/*
    函数说明：查询设置信息表
*/
int CMyController::querySetTable(deque<string> &dSetInfo)
{
    dSetInfo.clear();
    return this->userModel->querySetTable(dSetInfo);
}

/*
    函数说明：查询所有文件
*/
int CMyController::queryAllFile(QString uid, QString fileType, QList<QString> &fileInfo)
{
    return this->userModel->queryAllFile(uid, fileType, fileInfo);
}

/*
    函数说明：查询所有时间文件
*/
int CMyController::queryTimeFile(QString uid, QString time, QString fileType, QList<QString> &fileInfo)
{
    if(time.length() != 0)
    {
        time += "%";
    }
    return this->userModel->queryTimeFile(uid, time, fileType, fileInfo);
}

/*
    函数说明： 查询视频帧数文件
*/
int CMyController::queryVideoFrameNum(QString time)
{
    return this->userModel->queryVideoFrameNum(time);
}

/*
    函数说明：查询所有文件
*/
int CMyController::queryUid(QString &uId)
{
    //查询是否存在该uid
    return userModel->queryUid(uId);
}

/*
    函数说明：得到控制器单例
*/
CMyController::CMyController()
{
    userModel = CUserModel::getInstence();
}
