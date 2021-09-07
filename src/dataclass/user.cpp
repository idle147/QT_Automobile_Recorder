#include "user.h"

CUser * CUser::user = nullptr;

CUser *CUser::getInstence()
{
    if(user == nullptr)
    {
        CUser::user = new CUser;
    }
    return user;
}

CUser::CUser()
{

}

