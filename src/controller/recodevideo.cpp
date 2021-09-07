#include "recodevideo.h"

CRecodeVideo::CRecodeVideo()
{
    av_register_all();         //注册组件
    this->video_index =  -1;   //初始化视频下标
    this->frameNum = 0;
}

/*
    函数说明：得到所有帧数文件
*/
int &CRecodeVideo::getFrameNum()
{
    return this->frameNum;
}

/*
    函数说明：打开H264文件
*/
bool CRecodeVideo::openH264File(QString inputFile)
{
    //动态开辟相关空间
    this->formatContext = avformat_alloc_context();         //打开源视频信息上下文结构体
    this->outFormatContext = avformat_alloc_context();      //目标视频信息上下文结构体
    this->pkt = (AVPacket *)malloc(sizeof(AVPacket));       //保存压缩的码流数据

    //打开H264文件
    int res = avformat_open_input(&formatContext, inputFile.toStdString().c_str(), nullptr, nullptr);
    if(res != 0)
    {
        cerr << "avformat_open_input find Error :" << res << endl;
        return false;
    }
    cout << "avformat_open_input Success" << endl;

    //查找流媒体是否存在
    res = avformat_find_stream_info(formatContext, nullptr);
    if(res < 0)
    {
        cerr << "Find Stream Error: " << res << endl;
        return false;
    }
    cout << "Find Stream success" << endl;

    //视频流下标
    this->video_index = av_find_best_stream(formatContext, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
    if(video_index == -1)
    {
        cerr << "Find_videos stream Error" << endl;
        return false;
    }
    cout << "Find_video stream success" << endl;
    return true;
}

/*
    函数说明：转换输入格式
*/
void CRecodeVideo::tranceToFormat(QString outputFile)
{
    cout << "Coming in tranceToFormat" << endl;
    //猜测封装格式
    outFormat = av_guess_format(nullptr, outputFile.toStdString().c_str(), nullptr);
    if(outFormat == nullptr)
    {
        cerr << "find_video stream error" << endl;
        return ;
    }
    cout << "find_video stream success" << endl;

    //设置输出视频封装格式
    outFormatContext->oformat = outFormat;

    //打开输出的视频流
    int res = avio_open(&outFormatContext->pb, outputFile.toStdString().c_str(), AVIO_FLAG_WRITE);
    if(res < 0)
    {
        cerr << "avio_open Error: " << res << endl;
        return;
    }
    cout << "avio_open success" << endl;

    //新建输出流
    AVStream *outNewStream = avformat_new_stream(outFormatContext, nullptr);
    if(outNewStream == nullptr)
    {
        cerr << "new stream error" << endl;
        return;
    }
    cout << "new stream creats success" << endl;

    //参数设置(利用参数拷贝)
    //参数1:目标参数设置, 参数2:原来的参数设置
    res = avcodec_parameters_copy(outNewStream->codecpar, formatContext->streams[video_index]->codecpar);
    if (res < 0)
    {
        cerr << "parameters_copy find error: " << res << endl;
        return;
    }
    cout << "parameters_copy success" << endl;
    outNewStream->codecpar->codec_tag = 0;

    //写入头部信息
    res = avformat_write_header(outFormatContext, nullptr);
    if (res < 0)
    {
        cerr << "write_header find error: " << res << endl;
        return;
    }
    cout << "write_header success" << endl;

    //转码操作: 一帧一帧写入码流数据
    //此处H264已经剔除了坏数据,并且删除了B帧
    int size = outNewStream->codecpar->width * outNewStream ->codecpar ->height;
    //动态开辟空间大小
    res = av_new_packet(pkt, size);
    if (res != 0)
    {
        cerr << "new_packet find error: " << res << endl;
        return;
    }
    cout << "new_packet success" << endl;
    int frameCount = 0;

    while(av_read_frame(formatContext, pkt) == 0)
    {
        //判断是否是视频流
        if(video_index == pkt->stream_index)
        {
            //转码 表示第几帧
            frameCount++;
            //没有B帧的前提下: PTS:显示时间基 == DTS:解码时间基
            //视频没有设置显示时间基 指定解码顺序
            if(pkt->pts == AV_NOPTS_VALUE)
            {
                //时间基转换流程
                AVRational time_base1 = formatContext->streams[video_index]->time_base;
                //计算2帧之间的时长
                int64_t duration = (double)AV_TIME_BASE / (double)av_q2d(formatContext->streams[video_index]->r_frame_rate);
                //计算显示时间基: 总帧数*2帧之间的时长/输入实践基*AV_TIME_BASE
                pkt->pts = (double)(frameCount *duration) / (double)(av_q2d(time_base1) * AV_TIME_BASE);
                //PTS:显示时间基 == DTS:解码时间基
                pkt->dts = pkt->pts;
                pkt->duration = duration / (double)(av_q2d(time_base1) * AV_TIME_BASE);
            }
            else if(pkt->pts < pkt->dts)
            {
                cout << "frameCount: " << frameCount << endl;
            }
            //参数1:需要转换的值 参数2:原来的时间基 参数3:现在的时间基 参数4:换算规则
            //显示时间基转换
            pkt->pts = av_rescale_q_rnd(pkt->pts, formatContext->streams[video_index]->time_base,
                                        outNewStream->time_base, (AVRounding)(AV_ROUND_INF | AV_ROUND_PASS_MINMAX));

            //解码时间基的转换
            pkt->dts = av_rescale_q_rnd(pkt->dts, formatContext->streams[video_index]->time_base,
                                        outNewStream->time_base, (AVRounding)(AV_ROUND_INF | AV_ROUND_PASS_MINMAX));

            //两帧之间的时长，以所属媒体流的时间基准为单位，未知则默认值0
            pkt->duration = av_rescale_q(pkt->duration, formatContext->streams[video_index]->time_base, outNewStream->time_base);

            //数据在流媒体中的位置
            pkt->pos = -1;

            //标示 结合AV_PKT_FLAG 最低是1表示为关键帧
            pkt->flags |= AV_PKT_FLAG_KEY;

            //packet在stream中index的位置
            pkt->stream_index = 0;

            //写入数据到输出信息上文结构体
            av_interleaved_write_frame(outFormatContext, pkt);
            this->frameNum++;
            emit frameNumFindChange(this->frameNum);
        }
        av_packet_unref(pkt);
    }
    //写入尾帧
    av_write_trailer(outFormatContext);
    this->frameNum = 0;
    //关闭编码器
    avcodec_close(outFormatContext->streams[video_index]->codec);
    av_freep(&outFormatContext->streams[video_index]->codec);
    //关闭输出流
    avio_close(outFormatContext->pb);
    av_free(outFormatContext->pb);
    avformat_close_input(&formatContext);
    //av_packet_free(&pkt);
}
