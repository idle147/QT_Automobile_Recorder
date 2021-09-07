#ifndef CODEVIDEO_H
#define CODEVIDEO_H
#include <iostream>
#include <string>
#include <QThread>
#include <QImage>
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

class CEncodevideo: public QThread
{
    Q_OBJECT
public:
    CEncodevideo(int setFrameNum);      //构造函数用以注册
    void initEncode(const char* H264Path, int width, int height);   //编码器初始化
    int encodeVideo(AVFrame *frame);    //编码视频
    void writeTailer();                 //封装上尾帧
    void resetParameter(int setFrameNum);//重设参数
    void endWrite();                 //设置帧数
private:
    int frameNum;                       //定义帧数
    int fframeNum;                      //定义动态变化的帧数

    AVOutputFormat* outformat;          //输出的视频格式
    AVFormatContext* formatContext;     //封装格式结构体
    AVCodec* codec;                     //编码器
    AVCodecContext *codecContext;       //编码器上下文结构体——用以存储编码视频的相关参数
    AVCodec* decoder;                   //解码器上下文结构体
    AVPacket* pkt;                      //Get Frame Data
    AVStream* newStream;                //新增视频流
    int pkt_index;                      //创建pkt的索引，防止乱码

};

#endif // CODEVIDEO_H
