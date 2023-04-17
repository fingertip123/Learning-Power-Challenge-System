#ifndef DATABASE_H
#define DATABASE_H
#include<mysql/mysql.h>
#include<mutex>
#include <spdlog/spdlog.h>
#include <jsoncpp/json/json.h>

namespace spd = spdlog;

class Database
{
private:
    MYSQL *m_sql;    //操作数据库的句柄
    std::mutex m_mutex;
public:
    //host主机名  用户名 密码  数据库名
    Database(const char *host,const char *userName,const char *password,const char *DbName );
    ~Database();

    //对数据库的操作   增删改查
    bool database_exec(const char *sql);    //执行语句操作
    //[in]    const char *sql       输入一个查询语句
    //[out]   Json::Value &outjson  输出一个json格式的数据
    bool database_select(const char *sql,Json::Value &outjson);     //查询语句

protected:

};



#endif