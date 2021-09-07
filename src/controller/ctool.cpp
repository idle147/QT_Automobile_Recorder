#include "ctool.h"
#include <sys/stat.h>
#include <unistd.h>

/************************************
    函数说明:初始化构造函数,无需使用
    函数输入:无
    函数输出:无
*************************************/
CTool::CTool()
{

}


/************************************
    函数说明:将utf转化为gbk
    函数输入:string类型字符串(引用)
    函数输出:char*指针(可直接赋值)
*************************************/
char* CTool::utfTogbk(string& str)
{
    QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(utf8);
    QTextCodec* gbk = QTextCodec::codecForName("gbk");
    //1.utf8->unicode
    QString strUnicode= utf8->toUnicode(QString::fromStdString(str).toLocal8Bit().data());
    //2. unicode->gbk, 得到QByteArray
    QByteArray p= gbk->fromUnicode(strUnicode);
    return p.data(); //获取其char*
}


/************************************
    函数说明:gbk转UTF
    函数输入:string类型字符串(引用)
    函数输出:char*指针(可直接赋值)
*************************************/
char* CTool::gbkToutf(string &str)
{
    QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(utf8);
    QTextCodec* gbk = QTextCodec::codecForName("gbk");
    //1. gbk -> unicode
    QString gbk2utf = gbk->toUnicode(gbk->fromUnicode(QString::fromStdString(str)));
    //2. unicode -> utf-8
    QByteArray p = gbk2utf.toLatin1();
    return p.data(); //获取其char*
}


/**********************************************
    函数功能:判断所输入的字符串是否是中英文字符
    函数输入:字符串
    函数输出:bool, 是则输出true, 不是则输出为false
    函数名称:judgeCNorEN(string& str)
**********************************************/
bool CTool::judgeCNorEN(string str)
{
    //基本思想: 输入一串字符串,如果是中英文字符,则删除, 最后长度为0,则返回true
    //utf-8情况下一个中文字符占3位

    int len = str.length();//字符串长度
    int i = 0;             //遍历的变量
    int num = 0;           //记录删除的字符数
    char key , key2;       //记录字符的信息
    string word;           //判断一个字符

    //先匹配中文字符的个数
    while(i < len)
    {
        key = str.c_str()[i];
        key2 = str.c_str()[i+1];
        //判断是否是中文字符
        if ((unsigned char)key >= 0Xa1 && (unsigned char)key2 <= 0XFE)
        {
            if ((unsigned char)key >= 0Xa1 && (unsigned char)key2 <= 0XFE)
            {
                num += 3; //记录字符数为2
            }
        }
        i = i + 3;
    }

    //在查询所有的英文字符的个数
    i = 0;
    while(i < len)
    {
        if((str[i]>='a'&&str[i]<='z')||(str[i]>='A'&&str[i]<='Z'))
        {
            num++;
        }
        i++;
    }

    //相等则为true, 否则返回false
    return (len == num);
}


/********************************************
    函数功能:判断所输入的字符串是否是大小写英文字符和数字
    函数输入:字符串
    函数输出:bool, 是则输出true, 不是则输出为false
    函数名称:judgeNumOrEN(string& str)
**********************************************/
bool CTool::judgeNumOrEN(string str)
{
    QRegExp rx("^[A-Za-z0-9]+$"); //匹配数字和大小写字母,且必须匹配1次
    //indexIn的返回值: -1不匹配, >=0 表示匹配的位置
    if(rx.indexIn(str.c_str()) != -1)
    {
        return true; //匹配返回true
    }
    return false;//不匹配返回false
}


/********************************************
    函数说明:char类型转成int类型
    函数输入:const char*类型字符串(可直接赋值)
    函数输出:int类型
*********************************************/
int CTool::char2int(const char *str)
{
    const char* p = str;
    int res = 0;
    if (*str == '-' || *str == '+')
    {
        str++;
    }

    //循环转换
    while (*str != 0)
    {
        if (*str < '0' || *str > '9')
        {
            break;
        }
        res = res * 10 + *str - '0';
        str++;
    }

    if (*p == '-')
    {
        res = -res;
    }
    return res;
}



