#ifndef CGETSETINFO_H
#define CGETSETINFO_H
#include "controller/myController.h"

//生成一个单例类模板
template<typename T>
class Singleton
{
public:
    static T& Instance()
    {
        if(s_Instance == 0)
        {
            s_Instance = new(T)();
            atexit(Destroy);//销毁单例指针
        }
        return *s_Instance;
    }

protected:
    Singleton() {}  //构造单例
    ~Singleton() {} //析构单例

private:
    //销毁单例类
    static void Destroy()
    {
        if(s_Instance != 0)
        {
            delete(s_Instance);
            s_Instance = 0;
        }
    }
    /*
            volatile: (易变性质)下一条语句不会直接使用上一条语句对应的volatile变量的寄存器内容，而是重新从内存中读取。
            volatile: (不可优化)告诉编译器，不要对我这个变量进行各种激进的优化，甚至将变量直接消除，保证程序员写在代码中的指令，一定会被执行。
            volatile: (顺序性)多线程编程，并发访问/修改的全局变量
        */
    static T* volatile s_Instance;  //定义静态模板指针
};

//创建一个全局唯一的对象
template<typename T>
T* volatile Singleton<T>::s_Instance = 0;

//设置信息
class CGetSetInfo: public Singleton<CGetSetInfo>
{
public:
    CGetSetInfo();                  //设置信息构造函数
    bool findInfo();                //是否发现信息
    const char* getVideoUrlInfo();  //得到视频播放地址信息
    const char* getPhotoUrlInfo();  //得到照片播放地址信息
    const char* getTimeInfo();      //得到时间间隔信息
    const char* getCamInfo();       //得到摄像头信息
    static QString& getUserName();  //得到用户信息
    static void setUserName(QString name);//设置用户信息

private:
    CMyController *control;         //控制器单例
    deque<string> dSetInfo;         //存储数据库当前的配置信息
    bool isFindInfo;                //是否有数据
    static QString LoginUserName;   //用户名全局遍历
};

#endif // CGETSETINFO_H
