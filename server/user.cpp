#include "user.h"

User::User(std::string str, Tcpsocket *s, int num)
{
    userName = str;
    m_s = s;
    rank_num = num;
}

User::~User()
{
}

Tcpsocket * User::get_socket()
{
    return m_s;
}
void User::set_rank(int i)
{
    rank_num = i;
}
void User::set_socket_rank(int i)
{
    m_s->set_rank(i);
}