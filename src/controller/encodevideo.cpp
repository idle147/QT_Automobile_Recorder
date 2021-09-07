#include "encodevideo.h"

/*
    函数说明: 构造函数,用以设置相关参数
    函数输入: 每秒保存的帧数
    函数输出: 无
*/
CEncodevideo::CEncodevideo(int setFrameNum)
{
    //定义摄像头的总帧数
    this->frameNum = setFrameNum; //设置帧数
    this->fframeNum = frameNum;
    //注册
    av_register_all();
}

/*
    函数说明: 数值初始化
    函数输入: const char* H264Path(保存视频的地址), int width, int height(宽和高)
    函数输出: 无
*/
void CEncodevideo::initEncode(const char* H264Path, int width, int height)
{
    //相关数值开辟空间
    formatContext = avformat_alloc_context();
    pkt = av_packet_alloc();
    this->pkt_index = 0;

    //猜测格式是否可转存
    outformat = av_guess_format(nullptr, H264Path, nullptr);
    if(outformat == nullptr)
    {
        cerr << "Guess video-type Error" << endl;
        return;
    }
    cout << "Guess video-type Success" << endl;

    //设置输出格式
    formatContext->oformat = outformat;

    //将输出文件中的数据读入到程序的buffer当中，方便之后的数据写入，也可以说缓存数据写入
    int res = avio_open(&formatContext->pb, H264Path, AVIO_FLAG_WRITE);
    if(res < 0)
    {
        cerr << "avio_open find Error" << endl;
        return;
    }
    cout << "avio_open is Success" << endl;

    //新建流媒体
    newStream = avformat_new_stream(formatContext, nullptr);
    if(newStream == nullptr)
    {
        cerr << "Creat New Stream find Error" << endl;
        return;
    }
    // 设置 25 帧每秒 ，也就是 fps 为 25
    newStream->time_base.num = 1;
    newStream->time_base.den = 25;
    cout << "Creat New Stream is Success" << endl;

    //从媒体流中获取到编码结构体，他们是一一对应的关系，一个 AVStream 对应一个AVCodecContext
    this->codecContext = newStream->codec;

    //设置视频的宽和高
    codecContext->width = width;
    codecContext->height = height;

    // 设置比特率，每秒传输多少比特数 bit，比特率越高，传送速度越快，也可以称作码率，
    // 视频中的比特是指由模拟信号转换为数字信号后，单位时间内的二进制数据量。
    codecContext->bit_rate = 400000;       //bit流尺寸
    codecContext->time_base = {1, 25};      //1秒几帧
    codecContext->framerate = {25, 1};      //帧率

    // 设置图像组层的大小。
    // 图像组层是在 MPEG 编码器中存在的概念
    // 图像组包 若干幅图像, 组头包 起始码、GOP 标志等,如视频磁带记录器时间、控制码、B 帧处理码等;
    codecContext->gop_size = 10;            //帧数分组
    codecContext->qmax = 51;                //清晰度最高
    codecContext->qmin = 10;                //清晰度最低
    codecContext->qcompress = 1;            //Q压缩率

    // 设置 B 帧最大的数量，B帧为视频图片空间的前后预测帧， B 帧相对于 I、P 帧来说，压缩率比较大，也就是说相同码率的情况下，
    // 越多 B 帧的视频，越清晰，现在很多打视频网站的高清视频，就是采用多编码 B 帧去提高清晰度，
    // 但同时对于编解码的复杂度比较高，比较消耗性能与时间
    codecContext->max_b_frames = 0;                 //设置 B 帧最大的数量

    // 设置像素格式为 yuv 格式
    codecContext->pix_fmt = AV_PIX_FMT_YUV420P;

    // 设置编码类型为 视频编码
    codecContext->codec_type = AVMEDIA_TYPE_VIDEO;  //视频流

    //设置编码器的 id，每一个编码器都对应着自己的 id，例如 h264 的编码 id 就是 AV_CODEC_ID_H264
    codecContext->codec_id = outformat->video_codec;//输出的视频codecID

    //查找编码器
    codec = avcodec_find_encoder(codecContext->codec_id);
    //open codec
    res = avcodec_open2(codecContext, codec, nullptr);
    if(res != 0)
    {
        cerr << "Open Codec find Error";
        return;
    }
    cout << "Open Codec Success" << endl;


    //写下头文件数据
    res = avformat_write_header(formatContext, nullptr);
    if(res < 0)
    {
        cerr << "Write head info Error" << endl;
        return;
    }
    cout << "Write head info success";
    cout << "init encoder success";
}

/*
    函数说明: 对视频进行编码
    函数输入: AVFrame*类型值
    函数输出: -1(帧写入错误), 0(不成功存储) , 1(成功存储完毕)
*/
int CEncodevideo::encodeVideo(AVFrame *frame)
{
    //设定帧数
    //发送一帧数据给编码器
    int res = avcodec_send_frame(this->codecContext, frame);
    if(res != 0)
    {
        cerr << "Send_Frame Error: " << res << endl;
        return -1;
    }
    cout << "Send_Frame Success";
    //loop res 帧的尺寸有可能大于pkt的尺寸
    while(res >= 0)
    {
        //指定编码过程的顺序
        frame->pts = this->pkt_index++;
        res = avcodec_receive_packet(this->codecContext, this->pkt);
        if(res == AVERROR(EAGAIN) || res == AVERROR_EOF)
        {
            cerr << "Packet find Error" << endl;
            return -1;
        }
        cout << endl << "Packet Success" << endl;
        //已经压缩好的pkt,写入封装格式上下文结构体里面
        res = av_interleaved_write_frame(this->formatContext, this->pkt);
        if(res != 0)
        {
            cerr << "Write_frame find Error" << endl;
            return -1;
        }
        fframeNum--;
        //存完
        if(fframeNum <= 0)
        {
            endWrite();
            return 1;
        }
    }
    //清空pkt
    this->pkt_index = 0;
    av_packet_unref(this->pkt);            //释放pkt内的数据
    cout << "Endecode is success" << endl;
    return 0;
}

/*
    函数说明:写入尾帧,以保证存储
    函数输出:无
    函数输入:无
*/
void CEncodevideo::writeTailer()
{

    av_write_trailer(this->formatContext); //写入尾帧
    cout << "wirte tail Success" << endl;
    avio_close(this->formatContext->pb);   //关闭IO流
    avformat_free_context(this->formatContext);//释放上下文结构体
}


/*
    函数说明:重设参数
    函数输出:重设需要保存的帧数int
    函数输入:无
*/
void CEncodevideo::resetParameter(int setFrameNum)
{
    //定义摄像头的总帧数
    this->frameNum = setFrameNum; //设置帧数
    this->fframeNum = frameNum;
}

/*
    函数说明:结束写入
*/
void CEncodevideo::endWrite()
{
    //写入尾帧
    writeTailer();
    //重置
    fframeNum = frameNum;
    //清空pkt
    this->pkt_index = 0;
    //释放pkt内的数据
    av_packet_unref(this->pkt);
}


