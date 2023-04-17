#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include "tcpserver.h"
#include <string>
//两者头文件相互包含，需要互相声明一下对方的类
class Tcpserver;

//创建通信类
class Tcpsocket
{
private:
    Tcpserver * m_server;
    struct bufferevent *m_bev;
    const char * m_ip;
    uint16_t m_port;

    std::string username_socket;
    int rank_socket;
public:
    Tcpsocket(Tcpserver *,struct bufferevent *,const char*,uint16_t);
    ~Tcpsocket();

    //外部调用
    static void readEventCb(struct bufferevent *bev, void *user_data);  //可读事件回调函数
    static void writeEventCb(struct bufferevent *bev, void *user_data);  //可写事件回调函数
    static void closeEventCb(struct bufferevent *bev, short events, void *user_data);  //关闭事件回调函数
    static void connectEventcb(struct bufferevent *bev, void *user_data);

    void readEvent(struct bufferevent *bev);  //可读事件回调函数
    void writeEvent(struct bufferevent *bev);  //可写事件回调函数
    void closeEvent(struct bufferevent *bev, short events);  //关闭事件回调函数
    void connectEvent(struct bufferevent *bev);

    const char *getIp();
    uint16_t  getPort();

    int readData(void * data,int size); //读数据
    int writeData(const void * data,int size);//写数据

    void set_username(std::string);     //设置用户名称
    std::string get_username();         //获取用户名称
    void set_rank(int);                 //设置用户rank分数
    int get_rank();                     //获取用户rank分数
};



#endif