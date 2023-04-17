#include "tcpserver.h"

Tcpserver::Tcpserver(int threadNum)
{
    //初始化m_base
    m_base = event_base_new();
    if(!m_base)
    {
        printf("couldn't create an event_base:exiting\n");
        exit(1);
    }
    //判断传入的参数是否合理
    if(0 >= threadNum)
    {
        printf("threadNum err\n");
        exit(1);
    }

    //初始化线程池
    m_threadNum = threadNum;
    m_threadPool = new Thread[m_threadNum];
    currentThread = 0;
}

Tcpserver::~Tcpserver()
{
    
}


int Tcpserver::listen(int port,const char* ip)
{
	struct sockaddr_in sin = {0};

    memset(&sin,0,sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
    if(NULL != ip)
    {
        inet_aton(ip,&sin.sin_addr);
    }
    //listener会触发listerner_cb回调函数
	m_listener = evconnlistener_new_bind(m_base, listener_cb,this,
	    LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE, -1,
	    (struct sockaddr*)&sin,
	    sizeof(sin));

	if (!m_listener) {
		printf("Could not create a listener!\n");
		return 1;
	}

    //开启线程池
    for(int i=0;i < m_threadNum;i++)
    {
        m_threadPool[i].start();
        printf("线程 %d 开始运行\n",i + 1);
    }

	printf("done\n");
	return 0;
}
//回调函数参数：监听事件，socket套接字，客户端地址信息（ip port），标志位，给回调函数穿的参数
void Tcpserver::listener_cb(struct evconnlistener *, evutil_socket_t fd, struct sockaddr *clientAddr, int , void *data)
{
    printf("有客户端请求连接\n");
    Tcpserver *p = (Tcpserver *)data;
    p->listenEvent(fd,(struct sockaddr_in *)clientAddr);
}

void Tcpserver::start()
{
    //开始监听
    event_base_dispatch(m_base);

	evconnlistener_free(m_listener);

	event_base_free(m_base);
}

void Tcpserver::listenEvent(evutil_socket_t fd,struct sockaddr_in *clientAddr)
{
    char *ip = inet_ntoa(clientAddr->sin_addr);
    uint16_t port = ntohs(clientAddr->sin_port);
    //线程的轮询操作
    //此处要获得的是线程池里的m_base，不是主线程的m_base,但是线程池的m_base是私有变量，因此需要定义一个函数get_base获得私有变量里的事件集合m_base
    struct event_base *base = m_threadPool[currentThread].get_base();
    printf("线程: %d 开始监听客户端 %s \n",(int)m_threadPool[currentThread].get_threadId(),ip);
    currentThread = (currentThread + 1) % m_threadNum;//以轮询的方式调用线程，要做取余操作
	struct bufferevent *bev;//通信句柄

	bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
	if (!bev) {
		printf("Error constructing bufferevent!");
		event_base_loopbreak(base);
		return;
	}

    Tcpsocket *s = new Tcpsocket(this,bev,ip,port);

	bufferevent_setcb(bev, s->readEventCb, s->writeEventCb, s->closeEventCb, s);
	bufferevent_enable(bev, EV_WRITE);
	bufferevent_enable(bev, EV_READ);//记得将disable属性改为enable，打开可读操作
	bufferevent_enable(bev, EV_SIGNAL);
    
    //连接客户端事件
    connectEvent(s);
	
    
    // bufferevent_write(bev, MESSAGE, strlen(MESSAGE));
}