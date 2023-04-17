#ifndef COMMUNICATE_H
#define COMMUNICATE_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QJsonDocument>//解析json格式文件的头文件
#include <QJsonObject>//解析json格式对象的头文件
#include <QByteArray>//字节数组
#include "common.h"


class Communicate : public QObject
{
    Q_OBJECT
public:
    explicit Communicate(QObject *parent = nullptr);

    //给服务器发送数据
    void writeData(const QJsonObject &json);
signals:
    //注册的信号
    void register_cb(int);
    //登录的信号
    void login_cb(QJsonObject);
    //获取问题的信号
    void getquestion_cb(QJsonObject);
    //排位的信号
    void rank_cb(QJsonObject);
    //排位得分的信号
    void rankscore_cb(QJsonObject);
    //排行榜信号
    void rival_list_cb(QJsonObject);
public slots:
    //定义槽函数接收数据
    void readData();
private:
    QTcpSocket *s;

};

#endif // COMMUNICATE_H
