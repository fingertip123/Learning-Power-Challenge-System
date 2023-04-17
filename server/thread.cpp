#include"thread.h"

Thread::Thread()
{
    //初始化event_base
    m_base = event_base_new();
    if(!m_base)
    {
        printf("couldn't create an event_base:exiting\n");
        exit(1);
    }
    //创建管道
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    m_pieReadFD = pipefd[0];
    m_pieWriteFD = pipefd[1];

    //把管道事件添加到m_base的事件集合中
    //首先要把管道变成一个事件  event_set(接收管道事件,监听的事件,EV_PERSIST让事件始终存在,回调函数,回调函数参数)
    event_set(&m_pipeEvent,m_pieReadFD,EV_READ | EV_PERSIST,pipeCb,this);
    //将管道事件添加到事件集合中
    event_base_set(m_base,&m_pipeEvent);
    event_add(&m_pipeEvent,0);
}

Thread::~Thread()
{}

  //线程的运行函数
void Thread::start()
{
    pthread_create(&m_threadId,NULL,worker, this);
    pthread_detach(m_threadId);

}

void * Thread::worker(void * arg)
{
    //printf("线程: %d 开始运行\n",mthreadId);
    Thread *t = (Thread *)arg;
    t->run();
    return NULL;
}

void Thread::run()
{
    printf("线程: %d 开始运行\n",(int)m_threadId);
    //event_base_dispatch是一个死循环，循环处理事件集合中的事件
    //当事件集合m_base为空时，event_base_dispatch会立马返回，无法一直监听事件集合了
    //因此在初始化时就另m_base这个事件集合不为空
    /*具体做法：
    在主线程和子线程中间建立一条管道，子线程一开始是用于监听事件集合的，
    为了防止事件集合空，函数直接返回了，我们令事件集合在初始化时就监听管道读端
    */
    event_base_dispatch(m_base);
    event_base_free(m_base);

    printf("线程 %d 结束运行\n",(int)m_threadId);
}

void Thread::pipeCb(int,short,void *)
{}

event_base *Thread::get_base()
{
    return m_base;
}

pthread_t Thread::get_threadId()
{
    return m_threadId;
}