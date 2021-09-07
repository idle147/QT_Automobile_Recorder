#ifndef DECODEVIDEO_H
#define DECODEVIDEO_H
#include <iostream>
#include <string>
#include <QThread>
#include <QImage>
#include "encodevideo.h"
#include "model/userModel.h"
#include "controller/getsetinfo.h"
using namespace std;

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavdevice/avdevice.h"
#include "libavformat/avformat.h"
#include "libavutil/avutil.h"
#include "libswresample/swresample.h"
#include "libswscale/swscale.h"
#undef main
}

enum type {EPlay, EplayAndRecord};
/*////////////////////////////////////////////////////////

     注册->打开视频文件->查找对应流媒体信息->提取出视频流->
     找到解码器->打开解码器->读出1帧压缩的数据

///////////////////////////////////////////////////////*/

class CDecodeVideo: public QThread
{
    Q_OBJECT
public:
    CDecodeVideo(QString& url);          //初始化
    CDecodeVideo(const char* H264Path, int timeNum, const char* camName);  //初始化

    //重设相关参数
    void resetParameter(const char* H264Path, int timeNum, const char* camName);

    //有关视频的操作
    bool openVideo();                    //打开视频

    //有关摄像头的操作
    bool openCamera();                   //打开摄像头

    //共同函数操作
    bool getStreamInfo();                //得到视频流信息
    bool getVideoStreamIndex();          //得到视频流索引信息
    bool findVideoDecoder();             //找到编码器

    void openVideoDecoder();             //YUV+RGB解码方式
    void openVideoDecoderRGB();          //使用RGB解码方式

    void changeSpeed(float i);           //倍速调节
    void changeH264();                   //选择保存的路径

    //设置的相关函数
    void setType(int type);              //设置打开的类型
    void setStop(bool flag);             //设置是否暂停符号
    void setURL(QString url);            //设置H264地址
    void setExitFlag(bool flag);         //设置退出的旗帜
    void run();          //重写虚函数运行函数

protected:
    void saveNewFile();                 //设置是否录制标志位

private:
    AVFormatContext* formatContent;          //封装格式结构体
    AVFormatContext* videoFormatContent;     //封装播放器视频格式结构体
    AVFormatContext* camFormatContent;     //封装播放器视频格式结构体

    AVCodecContext* codec;              //编码器上下文结构体
    AVCodec* decoder;                   //解码器上下文结构体
    AVPacket* pkt;                      //Get Frame Data
    AVFrame* picture, * pictureYUV, *pictureRGB;
    QString URL;                        //定义播放视频文件的地址
    QString h264Path;                   //转存的H264地址--前缀路径
    QString fileName;                   //文件名称
    QString newH264Path;                //转存的H264地址--绝对路径
    QString uId;                        //设置ID的String

    string camName;                     //摄像头的名字

    int video_index;                    //Video-Stream Index
    int size;                           //Save picture-size;
    int type;                           //设置是打开摄像头还是打开视频
    int judge;                          //判断是否需要保存标识符
    int frameNum;                       //设定帧数
    int VideoframeNum;                  //设定视频帧数
    qint64 curtime;                     //当前播放时间
    float speed;                        //播放速度调节;

    CEncodevideo* encodeObj;            //生成一个编码对象
    CUserModel* userModel;              //生成用户模型
    bool stopPlay;                      //是否暂停播放
    bool exitFlag;                      //退出视频

signals:
    void sendImg(QImage img);           //发送图片
    void videoIsEnd();                  //视频播放完毕
    void frameNumFindChange(int);       //发送当前帧数
};



#endif // DECODEVIDEO_H
