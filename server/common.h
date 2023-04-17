#ifndef COMMON_H
#define COMMON_H

//定义我们的通信接口文档
//命令
#define REGISTER     1000
#define LOGIN        1001
#define GETQUESTION  1002
#define RANK         1003
#define RANKSCORE    1004
#define RANKRESULT   1005
#define RIVALLIST    1006

//结果
#define OK           2000
#define ERROR        2001
#define USEREXIT     2002
#define NAMEORPASSWD 2003           //密码错误
#define USERLOGIN    2004           //用户已登录

//问题类型
#define SUIJI        3000
#define GUSHI        3001
#define LISHI        3002
#define CHANGSHI     3003
#endif // COMMON_H
