#include "decodevideo.h"
#include "ctool.h"
#include <QDateTime>

/*
    函数说明:(构造函数)用以初始化播放视频,用以初始化视频播放的地址
    函数输入:视频播放的地址
*/
CDecodeVideo::CDecodeVideo(QString& url)
{
    /*
        解码流程:打开视频并获取视频文件信息-->获取视频流的索引(video_index)-->
                根据上下文结构体的编码id查找解码器并打开解码器
    */
//    //数值初始化
    this->video_index = -1;                 //视频流索引设置未-1
    this->codec = nullptr;                  //防止野指针,指针指向空
    this->decoder = nullptr;                //防止野指针,指针指向空
    this->pkt = nullptr;                    //防止野指针,指针指向空
    this->changeSpeed(1.0);                 //设置默认速度为1.0
    this->fileName = "";                    //无文件需要保存
    this->userModel = CUserModel::getInstence();//模型单例
    this->type = EPlay;                     //设置模式为视频模式
    this->stopPlay = false;                 //默认不暂停播放
    this->exitFlag = false;                 //设置退出旗帜
    this->VideoframeNum = 0;                //设置视频帧数
    av_register_all();                      //注册库register
    //视频数值初始化
    this->changeSpeed(40);      //设置播放速度延迟为0
    this->URL = url;            //视频播放的地址
    this->judge = 0;            //判断是否需要保存标识符,默认无需保存
}

/*
    函数说明: 用以初始化摄像机(构造函数)
    函数输入: 视频存储的位置, 存储的时间间隔, 存储的相机名称
    函数输出: 无
*/
CDecodeVideo::CDecodeVideo(const char *H264Path, int timeNum, const char *camName)
{
    //基础数值初始化
    this->video_index = -1;                         //Video-Stream Index
    this->codec = nullptr;                          //防止野指针,指针指向空
    this->decoder = nullptr;                        //防止野指针,指针指向空
    this->pkt = nullptr;                            //得到视频帧数据
    this->changeSpeed(1.0);                         //设置默认速度为1.0
    this->type = EplayAndRecord;                    //设置模式为同时播放和存储
    this->userModel = CUserModel::getInstence();    //模型单例
    this->frameNum = timeNum * 60 * 25;             //设置视频帧数
    this->encodeObj = new CEncodevideo(frameNum);   //初始化编码对象
    this->stopPlay = false;                         //默认不暂停播放
    this->exitFlag = false;                         //设置退出旗帜
    this->h264Path = H264Path;                      //转存的H264文件
    this->camName  = "video=";                      //前缀设置
    this->camName  += camName;
    //摄像头名称设置
    avdevice_register_all();

}

/*****************************************************************
    函数说明:重设参数(在需要更改参数的时候调用)
    函数输入:视频存储的位置char*, 存储的时间间隔int, 存储的相机名称char*
    函数输出:无
******************************************************************/
void CDecodeVideo::resetParameter(const char *H264Path, int timeNum, const char *camName)
{
    this->h264Path = H264Path;                       //转存的H264文件
    this->camName  = "video=";
    this->camName  += camName;                       //摄像头名称设置
    this->frameNum = timeNum * 60 * 25;              //设置视频帧数
    delete this->encodeObj;
    this->encodeObj = nullptr;
    this->encodeObj = new CEncodevideo(frameNum);   //初始化编码对象
}


/*
    函数说明:打开视频
    函数输入:无
    函数输出:（打开成功返回true，打开失败返回false）
*/
bool CDecodeVideo::openVideo()
{
    this->videoFormatContent = avformat_alloc_context(); //上下文解码器动态开空间
    int res = avformat_open_input(&this->videoFormatContent, this->URL.toStdString().c_str(), nullptr, nullptr);
    if(res != 0)
    {
        cout << "Open video Error: " << res << endl;
        avformat_free_context(videoFormatContent);
        return false;
    }
    else
    {
        cout << "Open Video Suceess" << endl;
        return true;
    }
}

/*
    函数说明: 打开摄像头并进行解码
    函数输入:无
    函数输出:（打开成功返回true，打开失败返回false）
*/
bool CDecodeVideo::openCamera()
{
    this->camFormatContent = avformat_alloc_context(); //上下文解码器动态开空间
    //打开摄像头，读取视频流
    AVInputFormat *fmt = av_find_input_format("dshow");
    int res = avformat_open_input(&camFormatContent, this->camName.c_str(), fmt, nullptr);
    if(res != 0)
    {
        cout << "Open Camera Error: " << res << endl;
        avformat_free_context(camFormatContent);
        return false;
    }
    else
    {
        cout << "Open Camera Success" << endl;
        return true;
    }

}


/*
    函数说明:获取视频流信息（打开成功返回true，打开失败返回false）
    函数输入:无
    函数输出:（打开成功返回true，打开失败返回false）
*/
bool CDecodeVideo::getStreamInfo()
{
    int res = -1;
    //判断采用哪个上下文结构体
    if(this->type == EPlay)
    {
        formatContent = this->videoFormatContent;
    }
    else
    {
        formatContent = this->camFormatContent;        
    }
    //得到视频流信息
    res = avformat_find_stream_info(this->formatContent, nullptr);
    //判断是否成功
    if(res < 0)
    {
        cerr << "Get Video-Stream information Error: " << res << endl;
        return false;
    }
    cout << "Get Video-Stream information Success" << endl;
    return true;
}

/*
    函数说明:查找视频流索引信息
    函数输入:无
    函数输出:（打开成功返回true，打开失败返回false）
*/
bool CDecodeVideo::getVideoStreamIndex()
{
    // This part is to look for Video-Stream Index
    this->video_index = av_find_best_stream(formatContent, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
    if (this->video_index == -1)
    {
        cerr << "Cann't Find Video-Stream:" << video_index << endl;
        return false;
    }
    cout << "Find Video-Stream :" << video_index << endl;
    return true;
}


/*
    函数说明:根据上下文结构体的编码id查找解码器（打开成功返回true，打开失败返回false）
    函数输入:无
    函数输出:（打开成功返回true，打开失败返回false）
*/
bool CDecodeVideo::findVideoDecoder()
{
    // This part is to find decoder for Video-Stream
    this->codec = formatContent->streams[video_index]->codec;
    this->decoder = avcodec_find_decoder(codec->codec_id);
    if(decoder == nullptr)
    {
        cerr << "Decoder was not Found" << endl;
        return false;
    }
    cout << "Find the Decoder" << endl;
    //Open Decoder
    //Return true if successfully opened, otherwise return false）
    int res = avcodec_open2(codec, decoder, nullptr);
    if(res != 0)
    {
        cerr << "Open Decoder Error: " << res << endl;
        return false;
    }
    this->pkt = (AVPacket*)malloc(sizeof(AVPacket));      //payload size;
    this->size = codec->width * codec->height;            //Save picture-size;
    res = av_new_packet(this->pkt, size);                 //Allocate the payload of a packet
    if (res == 0)//如果部署成功
    {
        cout << "Open Decoder Success" << endl;
        if(this->type == EPlay)
        {
            //只进行播放
            this->openVideoDecoderRGB();
        }
        else
        {
            //同时存和播
            this->openVideoDecoder();
        }
        cout << "write h264 file success to RGB";
        this->formatContent = nullptr;
        return true;
    }
    else
    {
        cerr << "Open Space Error: " << res  << endl;
        formatContent = nullptr;
        return false;
    }
}


/*
    函数说明:使用RGB播放,H264存储形式解码
    函数输入:无
    函数输出:（打开成功返回true，打开失败返回false）
*/
void CDecodeVideo::openVideoDecoder()
{

    //准备解压视频、提取图片像素数据
    //picture: It contains all the pic-information
    //pictureYUV: It eliminates bad data in pic-information
    picture = av_frame_alloc();

    //YUV相关内容开辟空间
    pictureYUV = av_frame_alloc();
    pictureYUV->width = codec->width;
    pictureYUV->height = codec->height;
    pictureYUV->format = codec->pix_fmt;

    //RGB相关内容开辟空间
    pictureRGB = av_frame_alloc();
    pictureRGB->width = codec->width;
    pictureRGB->height = codec->height;
    pictureRGB->format = codec->pix_fmt;

    //动态计算一张图片YUV420P控件的大小、RGB32控件的大小
    int imgBytesYUV = avpicture_get_size(AV_PIX_FMT_YUV420P, codec->width, codec->height);
    int imgBytesRGB = avpicture_get_size(AV_PIX_FMT_RGB32, codec->width, codec->height);

    //将像素数据存储到缓冲区内
    uint8_t* bufferYUV = (uint8_t*)av_malloc(imgBytesYUV * sizeof(uint8_t));    //YUV存储
    uint8_t* bufferRGB = (uint8_t*)av_malloc(imgBytesRGB * sizeof(uint8_t));    //RGB存储

    //Store data from buffer to pictureYUV
    avpicture_fill((AVPicture*)pictureYUV, bufferYUV, AV_PIX_FMT_YUV420P, codec->width, codec->height); //YUV存储
    avpicture_fill((AVPicture*)pictureRGB, bufferRGB, AV_PIX_FMT_RGB32, codec->width, codec->height);   //RGB存储

    //Making the rule to eliminates bad data
    SwsContext* swscontextYUV, *swscontextRGB;
    swscontextYUV = sws_getContext(codec->width, codec->height, codec->pix_fmt,
                                   codec->width, codec->height, AV_PIX_FMT_YUV420P,
                                   SWS_BICUBLIN, nullptr, nullptr, nullptr);   //YUV的swscontext开辟
    swscontextRGB = sws_getContext(codec->width, codec->height, codec->pix_fmt,
                                   codec->width, codec->height, AV_PIX_FMT_RGB32,
                                   SWS_BICUBLIN, nullptr, nullptr, nullptr);//rgb的swscontext开辟
    //初始化一个编码对象
    this->changeH264(); //设置保存的地址
    this->encodeObj->initEncode(newH264Path.toStdString().c_str(), pictureYUV->width, pictureYUV->height);
    this->judge = 1;

    //一帧帧读取并转存为H264,并发送给窗口
    while (av_read_frame(formatContent, pkt) == 0)
    {
        //Determine if it is a video stream
        if (pkt->stream_index == video_index)
        {
            //解压视频流数据
            int got_picture_ptr = -1;
            avcodec_decode_video2(codec, picture, &got_picture_ptr, pkt);
            if (got_picture_ptr != 0)
            {
                //删除坏数据--RGB
                sws_scale(swscontextRGB, picture->data, picture->linesize, 0,
                          picture->height, pictureRGB->data, pictureRGB->linesize); //剔除RGB内的坏数据

                //删除坏数据--YUV
                sws_scale(swscontextYUV, picture->data, picture->linesize, 0,
                          picture->height, pictureYUV->data, pictureYUV->linesize);//剔除YUV内的坏数据

                //发射图像
                QImage img((uchar*)bufferRGB, codec->width, codec->height, QImage::Format_RGB32);//发送给窗口
                //判断是否是第一帧,是则需要保存图片的封面
                if(this->judge == 1)
                {
                    this->uId = CGetSetInfo::getUserName();
                    this->h264Path = CGetSetInfo::Instance().getVideoUrlInfo();
                    this->newH264Path = this->h264Path + '/' + fileName + ".png";
                    img.save(newH264Path, "PNG", -1);
                    //将图片数据写入数据库
                    QString Savetype = "screencover";
                    userModel->writeTypeInfo(uId, this->fileName, Savetype, this->h264Path, "0");
                }
                emit sendImg(img);
                //存储成h264
                judge = this->encodeObj->encodeVideo(pictureYUV); //存储到编码文件
                if(judge == 1)
                {
                    //保存新文件
                    saveNewFile();
                    pictureYUV->pts = 0;
                }
                //如果需要切换设置信息,则需要跳出该循环
                if(this->exitFlag == true)
                {
                    cout << "exit Cam" << endl;
                    this->encodeObj->endWrite();
                    judge = 1;
                    this->exitFlag = false;     //设置退出视频标志位
                    break;
                }
            }
        }

        //ref data
        av_packet_unref(this->pkt);
    }
    av_frame_unref(picture);
    av_frame_unref(pictureYUV);
    av_frame_unref(pictureRGB);
}


/*
    函数说明:使用RGB32形式进行播放
    函数输入:无
    函数输出:无
*/
void CDecodeVideo::openVideoDecoderRGB()
{
    //preapre to unzip the data image
    //picture: It contains all the pic-information
    //pictureRGB: It eliminates bad data in pic-information
    VideoframeNum = 0;
    AVFrame* picture, * pictureRGB;
    picture = av_frame_alloc();//开辟空间
    pictureRGB = av_frame_alloc();//开辟空间
    pictureRGB->width = codec->width;
    pictureRGB->height = codec->height;
    pictureRGB->format = codec->pix_fmt;
    //Calculate the size of a frame of RGB32
    int imgBytes = avpicture_get_size(AV_PIX_FMT_RGB32, codec->width, codec->height);
    //Calculate the size of uint8_t buffer
    uint8_t* buffer = (uint8_t*)av_malloc(imgBytes * sizeof(uint8_t));
    //Store data from buffer to pictureRGB32
    avpicture_fill((AVPicture*)pictureRGB, buffer, AV_PIX_FMT_RGB32, codec->width, codec->height);
    //Making the rule to eliminates bad data
    SwsContext* swscontext;
    swscontext = sws_getContext(codec->width, codec->height, codec->pix_fmt, codec->width, codec->height, AV_PIX_FMT_RGB32,
                                SWS_BICUBLIN, nullptr, nullptr, nullptr);
    //读取帧数并播放
    while (av_read_frame(formatContent, pkt) == 0)
    {
        //Determine if it is a video stream
        if (pkt->stream_index == video_index)
        {
            int got_picture_ptr = -1;
            //解压缩数据流
            avcodec_decode_video2(codec, picture, &got_picture_ptr, pkt);
            if (got_picture_ptr != 0)
            {
                cout << "It's into got_picture_ptr" << endl;
                //删除坏数据
                sws_scale(swscontext, picture->data, picture->linesize, 0,
                          picture->height, pictureRGB->data, pictureRGB->linesize);
                QImage img((uchar*)buffer, codec->width, codec->height, QImage::Format_RGB32);
                //延迟发送,实现倍速控制
                msleep(this->speed);
                emit sendImg(img);
                this->VideoframeNum++;
                if(VideoframeNum % 25 == 0)
                {
                    emit frameNumFindChange(this->VideoframeNum);
                }
                //是否暂停播放,如果暂停则在此无限循环, 阻塞
                while(this->stopPlay)
                {

                }
                //如果需要切换视频,则需要跳出该窗口
                if(this->exitFlag == true)
                {
                    cout << "change Video" << endl;
                    this->exitFlag = false;     //设置退出视频标志位
                    break;
                }
            }
        }
        //ref data
        av_packet_unref(pkt);
    }
    av_frame_unref(picture);
    av_frame_unref(pictureRGB);
}


/*
    函数说明:改变播放速度
    函数输入:浮点素,用以控制倍速,40是1倍速, 20是2倍速, 26.667是1.5倍速, 80是0.5倍速
    函数输出:无
*/
void CDecodeVideo::changeSpeed(float i)
{
    this->speed = i;
}


/*
    函数说明:改变H264地址
    函数输入:无
    函数输出:无

*/
void CDecodeVideo::changeH264()
{
    //获取系统现在的时间,并格式化显示
    this->fileName = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");//设置显示格式
    this->newH264Path = this->h264Path + '/' + fileName + ".h264";
}


/*
    设置视频的类型
    函数输入:视频的类型.(枚举)Eplay EPlayAndRecord
    函数输出:无
*/
void CDecodeVideo::setType(int type)
{
    this->type = type;
}


/*
    函数说明: 进行解码
    函数输入: 无
    函数输出: 无
*/
void CDecodeVideo::run()
{
    //是否需要边录,边播
    if(this->type == EplayAndRecord)
    {
        if(openCamera() && getStreamInfo()&& getVideoStreamIndex()&& findVideoDecoder())
        {
            cout << endl << "EplayAndRecord is success run and over" << endl;
            return;
        }
    }
    else
    {
        while(!isInterruptionRequested())
        {
            //边播则进入循环
            if(openVideo()&& getStreamInfo()&& getVideoStreamIndex()&& findVideoDecoder())
            {
                cout << endl << "EplayAndRecord is success run and over" << endl;
                emit videoIsEnd(); //发射视频播放结束信号
            }
        }
    }
}


/*
    函数说明: 保存新的视频
    函数输入: 无
    函数输出: 无
*/
void CDecodeVideo::saveNewFile()
{
    //QString &uId, QString &date, QString &type, QString &path
    //将视频写入数据库
    QString Savetype = "video";
    userModel->writeTypeInfo(uId, this->fileName, Savetype, this->h264Path, QString::number(frameNum));
    //改变视频保存的地址
    this->changeH264();
    //重新初始化
    this->encodeObj->initEncode(newH264Path.toStdString().c_str(), pictureYUV->width, pictureYUV->height);
}

/*
    函数说明: 设置暂停
    函数输入: bool标识符
    函数输出: 无
*/
void CDecodeVideo::setStop(bool flag)
{
    this->stopPlay = flag;
}

/*
    函数说明: 设置URL的值
    函数输入: QString的URL值
    函数输出: 无
*/
void CDecodeVideo::setURL(QString url)
{
    this->URL = url;
}

/*
    函数说明: 设置退出的标识符
    函数输入: bool标识符
    函数输出: 无
*/
void CDecodeVideo::setExitFlag(bool flag)
{
    this->exitFlag = flag;
}
