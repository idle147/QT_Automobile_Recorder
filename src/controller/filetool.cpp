#include "filetool.h"
#include "myController.h"
#include <QMessageBox>

/*
    函数说明: 构造函数初始化数值
*/
CFileTool::CFileTool()
{
    //相关变量初始化
    this->imageCout = 0;
    this->videoCout = 0;
    //向字符串列表添加图片类型
    this->imageType << "*.bmp" << "*.jpg" << "*.png" << "*.gif" << "*.tiff" << "*.jpeg";
    this->imageType << "*.BMP" << "*.JPG" << "*.PNG" << "*.GIF" << "*.TIFF" << "*.JPEG";
    //向字符串列表添加视频类型
    this->videoType << "*.mpeg" << "*.avi" << "*.mov" << "*.wmv" << "*.flv" << "*.mp4" << "*.rmvb" << "*.rm";
    this->videoType << "*.MPEG" << "*.AVI" << "*.MOV" << "*.WMV" << "*.FLV" << "*.MP4" << "*.RMVB" << "*.RM";
}

/*
    函数说明: 获取文件单例指针
    函数输出: 文件的单例指针CFileTool*
*/
CFileTool *CFileTool::getInstence()
{
    static CFileTool instance; //单例指针
    return &instance;
}

/*
    函数说明: 判断文件是否存在
    函数输入: QString文件路径
    函数输出: bool类型值
*/
bool CFileTool::isDirExist(QString fullPath)
{
    QFileInfo file(fullPath);
    if(file.isFile())
    {
        return true;
    }
    return false;
}

/*
    函数说明: 列表窗口加入图标
    函数输入: QList<QString> &fileInfo, QListWidget *listWidget, QStringList &photoList
             文件信息列表引用, listWidget引用, 照片清单信息
    函数输出: 无
*/
void CFileTool::listWinAddItem(QList<QString> &fileInfo, QListWidget *listWidget, QStringList &photoList)
{
    //禁止元素拖拽
    listWidget->setMovement(QListView::Static);
    if(fileInfo.empty())
    {
        return;
    }
    //清空listWidget内所有的Item
    listWidget->clear();
    //将文件名和文件路径读取并存入stringList链表内
    photoList.clear();
    int listSize = fileInfo.size();
    int iNum = 0;
    while(iNum < listSize)
    {
        //判断图片文件是否存在
        QString url = fileInfo.at(iNum+4) + '/' + fileInfo.at(iNum+3) + ".jpg";
        if(CFileTool::isDirExist(url))
        {
            photoList << url;
        }
        iNum = iNum + 5;
    }
    //定义stringList内视频的数量
    int fileNameCount = photoList.length();

    //遍历添加ITEM数据
    for(int i = 0; i < fileNameCount; i++)
    {
        //通过 QListWidgetItem添加文本以及Icon数据
        QListWidgetItem * IconItem = new QListWidgetItem(QIcon(photoList.at(i)), photoList.at(i).right(18));
        //加入QListWidget
        listWidget->insertItem(i, IconItem);
    }
}

/*
    函数说明: 列表窗口加入图标
    函数输入: QList<QString> &fileInfo, QStringList &videoList, QStringList &coverList
             文件信息列表引用, listWidget引用, 视频清单信息, 封面清单信息
    函数输出: 无
*/
void CFileTool::listWinAddItem(QList<QString> &fileInfo, QListWidget *listWidget, QStringList &videoList, QStringList &coverList)
{
    //禁止元素拖拽
    listWidget->setMovement(QListView::Static);
    //将文件名和文件路径读取并存入stringList链表内
    videoList.clear();
    coverList.clear();
    int fileSize = fileInfo.size();
    int iNum = 0;
    while(iNum < fileSize)
    {
        //判断视频文件是否存在
        QString url = fileInfo.at(iNum + 4) + '/' + fileInfo.at(iNum + 3) + ".h264";
        if(CFileTool::isDirExist(url))
        {
            videoList << url;
        }

        //判断Icon的图片文件是否存在
        url = fileInfo.at(iNum + 4) + '/' + fileInfo.at(iNum + 3) + ".png";
        if(CFileTool::isDirExist(url))//如果图片文件存在,则加入
        {
            coverList << url;
        }
        //不存在则加入没有发现的Icon图标
        else
        {
            coverList << ":/icon/block.png";
        }
        iNum = iNum + 5;
    }

    //清空listWidget内所有的Item
    listWidget->clear();

    //定义stringList内视频的数量
    int fileNameCount = videoList.length();

    //遍历添加ITEM数据
    for(int i = 0; i < fileNameCount; i++)
    {
        //通过 QListWidgetItem添加文本以及Icon数据
        //H264长度为19位
        QListWidgetItem * IconItem = new QListWidgetItem(QIcon(coverList.at(i)), videoList.at(i).right(19));
        //加入QListWidget
        listWidget->insertItem(i, IconItem);
    }
}

/*
    函数说明: 得到所有的文件
    函数输入: QString uId, QString fileType, QList<QString> &fileInfo
    函数输出: 无
*/
int CFileTool::fGetAllFile(QString uId, QString fileType, QList<QString> &fileInfo)
{
    CMyController* control = CMyController::getInstence();//调用控制器信息
    if(uId.length() == 0)
    {
        return 0;
    }
    //遍历数据库内的所有文件，并存储到容器内
    control->queryAllFile(uId, fileType, fileInfo);
    return fileInfo.length();
}

/*
    函数说明:在选定时间下,得到所有的文件
*/
int CFileTool::fGetTimeFile(QString uId, QDate curTime, QString fileType, QList<QString> &fileInfo)
{
    fileInfo.clear();
    CMyController* control = CMyController::getInstence();//调用控制器信息
    QString timeStr = curTime.toString("yyyyMMdd");
    if(timeStr.length() == 0)
    {
        QMessageBox::warning(nullptr, "注意:", "所选日期为空!", QMessageBox::Yes);
        return 0;
    }
    control->queryTimeFile(uId, timeStr, fileType, fileInfo);
    return fileInfo.length() / 5;
}

/*
    函数说明: 读取QSS文件,并存储在输入的QString内
 */
bool CFileTool::readQSS(const char *url, QString &qss)
{
    QFile file(url);
    if(file.open(QFile::ReadOnly))
    {
        qss += file.readAll();
        file.close();
    }
    else
    {
        std::cerr << "打开QSS文件失败" << endl;
        return false;
    }
    return true;
}

bool CFileTool::judgeExit(QString url)
{
    QDir *fileDir = new QDir;
    bool exist = fileDir->exists(url);
    return exist;
}
