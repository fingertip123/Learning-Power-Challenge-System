#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "thread.h"
#include <event2/listener.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "tcpsocket.h"

class Tcpsocket;

class Tcpserver
{
private:
    Thread *m_threadPool;       //线程池
    int m_threadNum;              //线程池大小
    struct event_base *m_base;  //事件集合  监听客户端的连接请求
    struct evconnlistener *m_listener;  //监听事件
    int currentThread;              //标记当前的线程

public:
    Tcpserver(int threadNum = 8);//要获取线程池中的线程个数
    ~Tcpserver();

    int listen(int port,const char* ip = NULL);    //IP为NULL时，表示允许监听所有ip
    
    void start();               //服务器的运行函数
    //客户端连接的处理函数
    void listenEvent(evutil_socket_t fd,struct sockaddr_in *clientAddr);

/**************************************虚函数*********************************************/
    virtual void readEvent(Tcpsocket *){}   //可读信号处理函数
    virtual void writeEvent(Tcpsocket *){}   //可写信号处理函数
    virtual void closeEvent(Tcpsocket *,short){}   //关闭信号处理函数
    virtual void connectEvent(Tcpsocket *){}   //连接信号处理函数
//目前已经定义好了服务器基类的虚函数，需要再定义一个自己的服务器类myserver继承这个基类
protected:
    //static void listener_cb(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *sa, int socklen, void *user_data)
    //客户端连接的回调函数，一有客户端连接就会调用这个函数
    static void listener_cb(struct evconnlistener *, evutil_socket_t , struct sockaddr *, int , void *);
};


#endif