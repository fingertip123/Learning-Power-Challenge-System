#include "tcpsocket.h"

Tcpsocket::Tcpsocket(Tcpserver *server,struct bufferevent *bev,const char*ip,uint16_t port)
{
    //初始化
    m_server = server;
    m_bev = bev;
    m_ip = ip;
    m_port = port;
}

Tcpsocket::~Tcpsocket()
{

}
void Tcpsocket::readEventCb(struct bufferevent *bev, void *user_data)  //可读事件回调函数
{
    Tcpsocket *s = (Tcpsocket *)user_data;
    s->readEvent(bev);
}
void Tcpsocket::writeEventCb(struct bufferevent *bev, void *user_data)  //可写事件回调函数
{
    Tcpsocket *s = (Tcpsocket *)user_data;
    s->writeEvent(bev);
}
void Tcpsocket::closeEventCb(struct bufferevent *bev, short events, void *user_data)  //关闭事件回调函数
{
    Tcpsocket *s = (Tcpsocket *)user_data;
    s->closeEvent(bev,events);
    delete s;
}
void Tcpsocket::connectEventcb(struct bufferevent *bev, void *user_data)
{
    Tcpsocket *s = (Tcpsocket *)user_data;
    s->connectEvent(bev);
}
//回调函数的具体实现  因为想将这个服务器写成一个基类，其他都可以继承使用，因此都写成虚函数，都放在主线程tcpserver上
void Tcpsocket::readEvent(struct bufferevent *bev)  //可读事件回调函数
{
    m_server->readEvent(this);
}
void Tcpsocket::writeEvent(struct bufferevent *bev)  //可写事件回调函数
{
    m_server->writeEvent(this);

}
void Tcpsocket::closeEvent(struct bufferevent *bev, short events)  //关闭事件回调函数
{
    m_server->closeEvent(this,events);

}
void Tcpsocket::connectEvent(struct bufferevent *bev)
{
    m_server->connectEvent(this);

}

const char *Tcpsocket::getIp()
{
    return m_ip;
}
uint16_t Tcpsocket::getPort()
{
    return m_port;
}

int Tcpsocket::readData(void * data,int size) //读数据
{
    return bufferevent_read(m_bev,data,size);
}
int Tcpsocket::writeData(const void * data,int size)//写数据
{
    return bufferevent_write(m_bev,data,size);
}

void Tcpsocket::set_username(std::string u)
{
    username_socket = u;
}

std::string Tcpsocket::get_username()
{
    return username_socket;
}

void Tcpsocket::set_rank(int rank)
{
    rank_socket = rank;
}
int Tcpsocket::get_rank()
{
    return rank_socket;
}