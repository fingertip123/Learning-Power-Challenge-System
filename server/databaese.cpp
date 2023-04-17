#include "database.h"

Database::Database(const char *host,const char *userName,const char *password,const char *DbName)
{
    //初始化数据库
    m_sql = mysql_init(NULL);
    if(NULL ==m_sql)
    {
        spd::get("Study_power")->error("mysql_init error : {}",mysql_error(m_sql));
        exit(1);
    }
    //连接数据库
    MYSQL *con = mysql_real_connect(m_sql,host,userName,password,DbName,0,NULL,0);
    if(NULL == con)
    {
        spd::get("Study_power")->error("mysql_real_connect error : {}",mysql_error(m_sql));
        exit(1);
    }
    //设置中文权限
    m_sql = con;
    int ret = mysql_query(m_sql,"set names utf8;");
    if(0 != ret)
    {
        spd::get("Study_power")->error("mysql_query error : {}",mysql_error(m_sql));
        exit(1);
    }
}
Database::~Database()
{

}

bool Database::database_exec(const char *sql)
{
    //在对数据库操作前，一定要先上锁
    std::unique_lock<std::mutex> lok(m_mutex);
    if(NULL == sql)
    {
        spd::get("Study_power")->error("database_exec error : sql == NULL");
        return false;
    }
    //执行语句
    int ret = mysql_query(m_sql,sql);
    if(0 != ret)
    {
        spd::get("Study_power")->error("mysql_query {} error : {}",sql,mysql_error(m_sql));
        return false;
    }
    return true;
}

bool Database::database_select(const char *sql,Json::Value &outjson)
{
    std::unique_lock<std::mutex> loc(m_mutex);

    if(NULL == sql)
    {
        spd::get("Study_power")->error("database_exec error : sql == NULL");
        return false;
    }
    int ret = mysql_query(m_sql,sql);
    if(0 != ret)
    {
        spd::get("Study_power")->error("mysql_query {} error : {}",sql,mysql_error(m_sql));
        return false;
    }

    //从服务器中将查询结果下载下来
    MYSQL_RES * res =  mysql_store_result(m_sql);
    if(NULL == res)
    {
        if(0 == mysql_error(m_sql))
        {
            return true;
        }
        else
        {
            spd::get("Study_power")->error("db_select error : {}",mysql_error(m_sql));
            return false;
        }
    }

    //查询结果不为空，一行一行获取数据
    MYSQL_ROW row;                                      //结果行数
    unsigned int num_field = mysql_num_fields(res);     //结果列数
    MYSQL_FIELD *fetch_field = mysql_fetch_field(res);  //结果表头

    while(row = mysql_fetch_row(res))
    {
        for(int i = 0; i < num_field; i++)
        {
            outjson[fetch_field[i].name].append(row[i]);
        }
    }

    //释放结果
    //mysql_free_result(res);

    return true;

}