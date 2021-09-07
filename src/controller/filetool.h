#ifndef CFILETOOL_H
#define CFILETOOL_H

#include <QStringList>
#include <QDir>
#include <QDirIterator>
#include <QListWidget>
#include <iostream>
#include <QDate>

using namespace std;
class CFileTool
{
public:
    static CFileTool* getInstence();

    static bool isDirExist(QString fullPath);  //判断文件是否存在

    //加入listwin--照片
    static void listWinAddItem(QList<QString>& fileInfo, QListWidget* listWidget, QStringList& photoList);
    //加入listwin--照片和封面
    static void listWinAddItem(QList<QString>& fileInfo, QListWidget* listWidget, QStringList& videoList, QStringList& coverList);
    //得到所有文件
    static int fGetAllFile(QString uId, QString fileType, QList<QString>& fileInfo);
    //得到时间文件
    static int fGetTimeFile(QString uId, QDate curTime, QString fileType, QList<QString>& fileInfo);
    //搜素图片
    static void searchPic();
    //读取QSS文件
    static bool readQSS(const char* url, QString& qss);     //读取QSS文件
    //判断文件存不存在,不存在则创建
    static bool judgeExit(QString url);

private:
    CFileTool();               //构造函数私有
    QStringList imageType;     //图像类型清单
    QStringList videoType;     //视频类型清单
    int imageCout;             //图片文件夹数量
    int videoCout;             //视频文件夹数量

};

#endif // CFILETOOL_H
