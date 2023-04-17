#ifndef MYSERVER_H
#define MYSERVER_H

#include "tcpserver.h"
#include <spdlog/spdlog.h>
#include "database.h"
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>//json解析器的头文件
#include "common.h"
#include "user.h"
#include <map>  //用表格记录用户信息
#include <mutex>

namespace spd = spdlog;

#define DEBUG

class Myserver : public Tcpserver
{
private:
    std::shared_ptr<spdlog::logger> m_log;   //定义日志的句柄
    Database *m_db;                     //数据库
    std::map<std::string,User *>online_user_list;   //在线用户表
    std::mutex user_lock;               //用户在线列表的锁
    std::map<int,Tcpsocket *> rank_list; //排位等待列表 一个Tcpsocket *代表一个用户
    std::mutex rank_lock;               //排位等待列表的锁
public:
    Myserver();
    ~Myserver();
    void readEvent(Tcpsocket *);   //可读信号处理函数
    void writeEvent(Tcpsocket *);   //可写信号处理函数
    void closeEvent(Tcpsocket *,short);   //关闭信号处理函数
    void connectEvent(Tcpsocket *);   //连接信号处理函数

    void Register(Tcpsocket *,const Json::Value);        //注册函数
    void WriteData(Tcpsocket *,const Json::Value);          //将json格式数据写到客户端函数
    void Login(Tcpsocket *,const Json::Value);                 //登录函数
    void Getquestion(Tcpsocket *,const Json::Value);          //获取问题函数
    void Rank(Tcpsocket *,const Json::Value);               //排位赛
    void Rankscore(Tcpsocket *,const Json::Value);          //排位赛获取对方得分
    void Rankresult(Tcpsocket *,const Json::Value);         //排位赛结果
    void RivalList(Tcpsocket *,const Json::Value);          //排行榜获取
protected:

};



#endif