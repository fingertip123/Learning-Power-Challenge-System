#include"thread.h"
#include"tcpserver.h"
#include "myserver.h"
int main()
{
    Myserver *p = new Myserver;

    p->listen(8000);
    p->start();

    return 0;
}
//g++ *.cpp -o main -lpthread -lmysqlclient -levent -ljsoncpp -std=c++11