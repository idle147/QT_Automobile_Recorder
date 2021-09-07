#ifndef CTOOL_H
#define CTOOL_H
#include <QTextCodec>
#include <QString>
#include <iostream>

using namespace std;


class CTool
{
public:
    CTool();
    static char* utfTogbk(string& str); //utf-8转GBK
    static char* gbkToutf(string& str); //GBK转utf-8
    static bool judgeCNorEN(string str); //判断是否只包含中文和英文
    static bool judgeNumOrEN(string str);//判断是否只包含英文和数字(正则表达式)
    static int char2int(const char* str); //char*转int
};

template <class T>
//获取字符串数组的长度
int getArrayLen(T& array)
{
    return (sizeof(array) / sizeof(array[0] - 1 )); // 存储字符串的字符数组末尾有一个'\0'字符，需要去掉它
}


#endif // CTOOL_H
