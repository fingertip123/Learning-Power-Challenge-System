#ifndef THREAD_H
#define THREAD_H

#include <event2/event.h>
#include <event.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include <unistd.h>


class Thread
{
private:
    struct event_base *m_base;
    pthread_t m_threadId;
    int m_pieWriteFD;            //管道写端    
    int m_pieReadFD;            //管道读端    
    
    struct event m_pipeEvent;
public:
    Thread();
    ~Thread();

    void start();  //线程的运行函数
    void run();     //线程的逻辑函数
    struct event_base *get_base();      //获取私有变量中的事件集合m_base
    pthread_t get_threadId();           //获取私有变量中的线程号
protected:
    static void*worker(void *);    //线程工作函数
    static void pipeCb(int,short,void *);      //event_set的回调函数
};



#endif