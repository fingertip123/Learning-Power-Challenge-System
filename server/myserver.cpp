#include "myserver.h"


Myserver::Myserver()
{
    //在文件中输出，每次都需要cat打印文件内容查看，很不方便，定义一个DEBUG，如果是DEBUG就控制台输出
#ifdef DEBUG
    m_log = spd::stdout_color_mt("Study_power");    //在控制台输出
    m_log->info("Welcome to spdlog!");
#else
    //循环输出
    m_log = spd::rotating_logger_mt("Study_power", "Study_power", 1024 * 1024 * 5, 3);  //在文件中输出 
    //当等级大于等于info时，立刻输出
    m_log->flush_on(spd::level::info);
#endif
    m_db = new Database(NULL,"root","123456","Study_power");
}
Myserver::~Myserver()
{}

//重写
void Myserver::readEvent(Tcpsocket *s)   //可读信号处理函数
{
    //从客户端发来的注册信息，服务器端在这里接收
    //先接收数据长度，在接收数据
    int len;
    s->readData(&len,sizeof(int));
    if(0 == len)
    {
        return;
    }
    char buf[1024];
    s->readData(buf,len);
    printf("客户端 IP : %s  发送消息 : \n",s->getIp());
    printf("%s\n",buf);

    Json::Value value;
    Json::Reader reader;  //解析器

    if(!reader.parse(buf,value))//通过解析器函数直接将buf中的json文件解析到value中，是bool类型
    {
        m_log->error("json数据解析失败!");
        return;
    }
    switch(value["cmd"].asInt())
    {
    case REGISTER:
        Register(s,value);
        break;
    case LOGIN:
        Login(s,value);
        break;
    case GETQUESTION:
        Getquestion(s,value);
        break;
    case RANK:
        Rank(s,value);
        break;
    case RANKSCORE:
        Rankscore(s,value);
        break;
    case RANKRESULT:
        Rankresult(s,value);
        break;
    case RIVALLIST:
        RivalList(s,value);
        break;
    default:
        break;

    }
    
}
void Myserver::writeEvent(Tcpsocket *)   //可写信号处理函数
{}
void Myserver::closeEvent(Tcpsocket *s,short)   //关闭信号处理函数
{
    printf("客户端 IP : %s  Port : %d 断开连接\n",s->getIp(),s->getPort());
    
    //当用户在排位中途推出排位，将他从rank_list中删除
    std::unique_lock<std::mutex> Rank_lock(rank_lock);
    std::map<int,Tcpsocket *>::iterator it = rank_list.begin();
    while(it != rank_list.end())
    {
        if(s == it->second)   //在列表中找到了对应的在线用户
        {
            m_log->info("User {} Log out!",it->second->get_username().c_str());
            delete it->second;
            rank_list.erase(it);
            return;
        }
        it++;
    }

    //退出后，要将在线的用户都删除
    std::unique_lock<std::mutex> lock(user_lock);
    std::map<std::string,User *>::iterator us = online_user_list.begin();
    while(us != online_user_list.end())
    {
        if(s == us->second->get_socket())   //在列表中找到了对应的在线用户
        {
            m_log->info("User {} Log out!",us->first.c_str());
            delete us->second;
            online_user_list.erase(us);
            return;
        }
        us++;
    }

}
void Myserver::connectEvent(Tcpsocket *s)   //连接信号处理函数
{
    printf("客户端 IP : %s  Port : %d 请求连接\n",s->getIp(),s->getPort());
}

void Myserver::WriteData(Tcpsocket *s,const Json::Value Injson)
{
    std::string buf = Injson.toStyledString();//将json格式转化为标准string格式
    s->writeData(buf.c_str(),buf.length());//writeData()函数定义在tcpsocket中
}

void Myserver::Register(Tcpsocket *s,const Json::Value Injson)
{
    int result;
    //获取客户端的信息
    std::string username = Injson["username"].asString();
    std::string password = Injson["password"].asString();

    //在数据库中检查用户是否存在
    char sql[1024] = {0};//初始化协调语句
    memset(sql,0,sizeof(sql));
    sprintf(sql,"select * from user where name = '%s';",username.c_str());
    Json::Value outjson;
    int ret = m_db->database_select(sql,outjson);//查找到的内容放到outjson中，类型为bool型
    if(0 == ret)
    {
        result = ERROR;
        m_log->error("数据库查找失败！");
    }
    else if(outjson.isMember("name"))//查询有结果，表示该用户已经存在
    {
        result = USEREXIT;
        m_log->error("用户已存在！");
    }
    else//用户不存在，添加用户
    {
        //数据库添加数据
        memset(sql,0,sizeof(sql));
        sprintf(sql,"insert into user values('%s','%s',100);",username.c_str(),password.c_str());

        ret = m_db->database_exec(sql);
        if(0 == ret)
        {
            result = ERROR;
            m_log->error("{} 注册失败！",username.c_str());
        }
        else
        {
            result = OK;
            m_log->info("{} 注册成功！",username.c_str());
        }
    }



    //写给客户端的json数据
    Json::Value json;
    json["cmd"] = REGISTER;
    json["result"] = result;

    //发送json数据到客户端
    WriteData(s,json);

}

void Myserver::Login(Tcpsocket *s,const Json::Value Injson)
{
    //与前面的注册函数相似
    int result;
    int rank;
    //获取客户端的信息
    std::string username = Injson["username"].asString();
    std::string password = Injson["password"].asString();

    //在数据库中检查用户是否存在
    char sql[1024] = {0};//初始化协调语句
    memset(sql,0,sizeof(sql));
    sprintf(sql,"select * from user where name = '%s' and password = '%s';",username.c_str(),password.c_str());
    Json::Value outjson;
    int ret = m_db->database_select(sql,outjson);//查找到的内容放到outjson中，类型为bool型
    if(0 == ret)
    {
        result = ERROR;
        m_log->error("数据库查找失败！");
    }
    else if(outjson.isMember("name"))//查询有结果，表示该用户已经存在
    {
        //这里重新定义一个user类来判断用户信息
        //判断用户是否在线
        std::unique_lock<std::mutex> lock(user_lock);
        if(online_user_list.find(username) != online_user_list.end())   //查找在线用户名，找到了
        {
            result = USERLOGIN;
            m_log->error("用户{}已登录！",username.c_str());
        }
        else
        {
            //先获取rank分
            int i = 0;
            rank =atoi(outjson["rank_num"][i].asString().c_str());//json中值存储的类型都是char 因此要用atoi转int
            User *u = new User(username,s,rank);
            online_user_list.insert(std::make_pair(username,u));    //把用户插入在线列表
            result = OK;
            m_log->info("用户{}登录成功！",username.c_str());
            s->set_username(username);      //将socket用户名和客户端用户名绑定
            s->set_rank(rank);
        }
    }
    else//查询没有数据
    {
        //数据库添加数据
        result = NAMEORPASSWD;
        m_log->error("用户名或密码错误！");
        
    }



    //写给客户端的json数据
    Json::Value json;
    json["cmd"] = LOGIN;
    json["result"] = result;
    json["rank_num"] = rank;
    json["username"] = username;
    //发送json数据到客户端
    WriteData(s,json);
}

void Myserver::Getquestion(Tcpsocket *s,const Json::Value Injson)
{
    int result;
    char sql[1024] = {0};//初始化协调语句
    memset(sql,0,sizeof(sql));
    
    switch(Injson["type"].asInt())
    {
    case GUSHI:
        sprintf(sql,"select * from gushi order by rand() limit 5;");//随机获取五条数据
        break;
    case CHANGSHI:
        sprintf(sql,"select * from changshi order by rand() limit 5;");//随机获取五条数据
        break;
    case LISHI:
        sprintf(sql,"select * from lishi order by rand() limit 5;");//随机获取五条数据
        break;
    case SUIJI:
        sprintf(sql,"select * from suiji order by rand() limit 5;");//随机获取五条数据
        break;
    }

    Json::Value outjson;  //接收查询结果
    int ret = m_db->database_select(sql,outjson);
    if(0 == ret)
    {
        result = ERROR;
        m_log->error("数据库查找失败!");
    }
    else
    {
        result = OK;
        m_log->info("Question select success!");
        m_log->info("User {} get question {}",s->get_username().c_str(),outjson.toStyledString().c_str());
    }

    //写给客户端的json数据
    Json::Value json;
    json["cmd"] = GETQUESTION;
    json["result"] = result;
    json["question"] = outjson;
    //发送json数据到客户端
    WriteData(s,json);
}

void Myserver::Rank(Tcpsocket *s,const Json::Value Injson)
{
    int result = OK;
    m_log->info("{} 正在匹配  rank : {}",s->get_username().c_str(),Injson["rank_num"].asInt());
    int rank = Injson["rank_num"].asInt();
    std::unique_lock<std::mutex> lock(rank_lock);
    std::map<int,Tcpsocket *>::iterator it = rank_list.begin();
    //开始查找分数相同的等待用户
    for(int i = 0;i<11;i++)
    {
        it = rank_list.find(rank + i);
        if(it != rank_list.end())
        {
            char sql[1024] = {0};//初始化协调语句
            memset(sql,0,sizeof(sql));
            sprintf(sql,"select * from suiji order by rand() limit 30;");
            Json::Value outjson;  //接收查询结果
            int ret = m_db->database_select(sql,outjson);
            if(0 == ret)
            {
                result = ERROR;
                m_log->error("数据库查找失败!");
            }       
            else
            {
                result = OK;
                m_log->info("Question select success!");
                m_log->info("User {} get question {}",s->get_username().c_str(),outjson.toStyledString().c_str());
            }
            Json::Value json;
            json["cmd"] = RANK;
            json["result"] = result;
            json["question"] = outjson;
            json["rivalName"] = it->second->get_username();//不能用s，这是自己给自己发送消息，要用it->second，把我的信息发送给对手消息
            json["rivalrank"] = it->second->get_rank();
            WriteData(s,json);//写给对手
            json["rivalName"] = s->get_username();
            json["rivalrank"] = s->get_rank();
            WriteData(it->second,json);//写给我
            
            //匹配成功，从队列中删除
            rank_list.erase(it);
            //输出剩余匹配数量
            m_log->info("当前匹配列表人数为 : {}",rank_list.size());

            return;
        }
        it = rank_list.find(rank - i);
        if(it != rank_list.end())
        {
            char sql[1024] = {0};//初始化协调语句
            memset(sql,0,sizeof(sql));
            sprintf(sql,"select * from suiji order by rand() limit 30;");
            Json::Value outjson;  //接收查询结果
            int ret = m_db->database_select(sql,outjson);
            if(0 == ret)
            {
                result = ERROR;
                m_log->error("数据库查找失败!");
            }       
            else
            {
                result = OK;
                m_log->info("Question select success!");
                m_log->info("User {} get question {}",s->get_username().c_str(),outjson.toStyledString().c_str());
            }
            Json::Value json;
            json["cmd"] = RANK;
            json["result"] = result;
            json["question"] = outjson;
            json["rivalName"] = it->second->get_username();//不能用s，这是自己给自己发送消息，要用it->second，把我的信息发送给对手消息
            json["rivalrank"] = it->second->get_rank();
            WriteData(s,json);//写给对手
            json["rivalName"] = s->get_username();
            json["rivalrank"] = s->get_rank();
            WriteData(it->second,json);//写给我
            
            //匹配成功，从队列中删除
            rank_list.erase(it);
            //输出剩余匹配数量
            m_log->info("当前匹配列表人数为 : {}",rank_list.size());

            return;
            
        }
    //一直没有找到对手，就把自己加入到匹配队列中
    rank_list.insert(std::make_pair(s->get_rank(),s));
    m_log->info("当前匹配列表人数为 : {}",rank_list.size());

    }
}

void Myserver::Rankscore(Tcpsocket *s,const Json::Value Injson)
{
    m_log->info("Recieve Score success from {} : {}",s->get_username().c_str(),Injson["score"].asInt());
    //取出对手名字
    std::string rivalName = Injson["rivalName"].asString();
    int score = Injson["score"].asInt();
    User * rival = online_user_list.find(rivalName)->second;
    //给对手发送消息
    Json::Value json;
    json["cmd"] = RANK;
    json["rivalScore"] = score;

    WriteData(rival->get_socket(),json);//给对手发送我方得分
}

void Myserver::Rankresult(Tcpsocket *s,const Json::Value Injson)
{
    int rank = Injson["rank_num"].asInt();
    m_log->info("Recieve Result success from {} : {}",s->get_username().c_str(),rank);
    //修改User *   s->setRank    数据库里面的rank update
    char sql[1024] = {0};//初始化协调语句
    memset(sql,0,sizeof(sql));
    sprintf(sql,"update user set rank_num = %d where name = '%s';",rank,s->get_username().c_str());
    int ret = m_db->database_exec(sql);//执行语句
    if(0 == ret)
    {
        m_log->info("Update {} rank info failure",s->get_username().c_str());
    }
    else
    {
        m_log->info("Update {} rank info success",s->get_username().c_str());
    }
    online_user_list.find(s->get_username())->second->set_rank(rank);
    online_user_list.find(s->get_username())->second->set_socket_rank(rank);

}
void Myserver::RivalList(Tcpsocket *s,const Json::Value)
{
    m_log->info("Recieve get rival list info success from {}",s->get_username().c_str());
    char sql[1024] = {0};//初始化协调语句
    memset(sql,0,sizeof(sql));
    sprintf(sql,"select * from user order by rank_num desc limit 3;");//dec倒序（从大到小）取前三名
    Json::Value outjson;
    int ret = m_db->database_select(sql,outjson);
    if(0 == ret)
    {
        m_log->error("Get rival list error");
    }
    else
    {
        m_log->info("Get rival list success");
    }

    Json::Value json;
    json["cmd"] = RIVALLIST;
    json["rivallist"] = outjson;

    WriteData(s,json);
}