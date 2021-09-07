#ifndef USER_H
#define USER_H

//用户单例
class CUser
{
public:
    static CUser* getInstence();
private:
    CUser();
    static CUser* user;
};

#endif // USER_H
