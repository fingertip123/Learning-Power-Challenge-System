#include "communicate.h"

Communicate::Communicate(QObject *parent) : QObject(parent)
{
    s = new QTcpSocket;
    s->connectToHost(QHostAddress("192.168.1.164"),8000);
    connect(s,SIGNAL(readyRead()),this,SLOT(readData()));
}

void Communicate::readData()
{
     QByteArray data;
    //把数据全部读完
    while(s->bytesAvailable())//bytesAvailable()还有数据可读
    {
        data += s->readAll();
    }
    //数据解析
    QJsonDocument dt = QJsonDocument::fromJson(data);
    if(dt.isNull())return;
    QJsonObject obj = dt.object();
    //逻辑处理

    switch(obj["cmd"].toInt())
    {
    case REGISTER:
        emit register_cb(obj["result"].toInt());//这里发出注册信号给register，由register接收
        break;
    case LOGIN:
        emit login_cb(obj);
        break;
    case GETQUESTION:
        emit getquestion_cb(obj);
        break;
    case RANK:
        emit rank_cb(obj);
        break;
    case RANKSCORE:
        emit rankscore_cb(obj);
        break;
    case RIVALLIST:
        emit rival_list_cb(obj);
        break;
    default:
        break;
    }
}

void Communicate::writeData(const QJsonObject &json)
{
    QJsonDocument d(json);
    QByteArray sendData = d.toJson();
    int len = sendData.size();
    //先发送数据长度，在发送数据本身
    s->flush();  //保证数据立马发送
    s->write((char *)&len,sizeof(int));
    s->write(sendData);
}
