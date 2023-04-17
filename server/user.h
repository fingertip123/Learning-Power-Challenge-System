#ifndef USER_H
#define USER_H

#include <string>
#include "tcpsocket.h"


class User
{
private:
    std::string userName;
    Tcpsocket *m_s;
    int rank_num;
public:
    User(std::string str, Tcpsocket *s, int num);
    ~User();

    Tcpsocket * get_socket(); 
    void set_rank(int);                     //用户rank要更改
    void set_socket_rank(int);              //同样 socket中的rank也要更改

};

#endif