#ifndef CRECODEVIDEO_H
#define CRECODEVIDEO_H
#include <iostream>
#include <string>
#include <QThread>
#include <QImage>
#include <QProgressBar>
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


class CRecodeVideo: public QThread
{
    Q_OBJECT

public:
    CRecodeVideo();        //构造函数类
    int& getFrameNum();    //获取文件的总帧数
    bool openH264File(QString inputFile);   //打开码流数据
    void tranceToFormat(QString outputFile);//转码到对应的封装格式

private:
    AVFormatContext *formatContext;    //定义输入上下文结构体
    AVFormatContext *outFormatContext; //定义输出上下文结构体
    AVOutputFormat *outFormat;         //定义视频输出格式
    AVPacket *pkt;                     //定义视频的pkt指针
    int video_index;                   //视频索引下标
    int frameNum;                      //计算文件的帧数

signals:
    void frameNumFindChange(int frameNum);    //帧数发生改变

};

#endif // CRECODEVIDEO_H
