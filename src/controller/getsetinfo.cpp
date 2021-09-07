#include "getsetinfo.h"
/*
    函数说明:全局的登录名
*/
QString CGetSetInfo::LoginUserName = "";

/*
    函数说明: 得到单例指针
*/
CGetSetInfo::CGetSetInfo()
{
    this->control = CMyController::getInstence();
}

/*
    函数说明: 判断是否有查到信息
*/
bool CGetSetInfo::findInfo()
{
    int res = this->control->querySetTable(this->dSetInfo);
    if(res == IsFind)
    {
        for(int i = 0; i < 5; i++)
        {
            if(dSetInfo.at(i).length()==0)
            {
                return false;
            }
        }
        this->isFindInfo = true;
    }
    else
    {
        this->isFindInfo = false;
    }
    return this->isFindInfo;
}

/*
    函数说明: 得到视频的URL信息
*/
const char *CGetSetInfo::getVideoUrlInfo()
{
    findInfo();
    return dSetInfo.at(1).c_str();
}

/*
    函数说明: 得到照片的URL信息
*/
const char * CGetSetInfo::getPhotoUrlInfo()
{
    findInfo();
    return dSetInfo.at(2).c_str();
}

/*
    函数说明: 得到视频间隔信息
*/
const char *CGetSetInfo::getTimeInfo()
{
    findInfo();
    return dSetInfo.at(3).c_str();
}

/*
    函数说明: 得到摄像机信息
*/
const char *CGetSetInfo::getCamInfo()
{
    findInfo();
    return dSetInfo.at(4).c_str();
}

/*
    函数说明: 得到用户名称
*/
QString& CGetSetInfo::getUserName()
{
    return LoginUserName;
}

/*
    函数说明:设置用户名称
*/
void CGetSetInfo::setUserName(QString name)
{
    LoginUserName = name;
}


