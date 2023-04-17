#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_com = new Communicate;

    connect(m_com,SIGNAL(login_cb(QJsonObject)),this,SLOT(login_cb(QJsonObject)));
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_log_in_button_clicked()
{
    QString username = ui->username->text();//获取lineedite输入的内容
    QString password = ui->password->text();

    //将里面的数据发送给服务器进行登陆操作
    QJsonObject json;
    json["cmd"] = LOGIN;
    json["username"] = username;
    json["password"] = password;

    m_com->writeData(json);
}

void Widget::on_register_button_clicked()
{
    this->hide();
    Register * r = new Register(m_com);
    r->show();
    r->exec();
    this->show();
}

void  Widget::login_cb(QJsonObject json)
{
    switch(json["result"].toInt())
    {
    case OK:
    {
        StudyPower * sp = new StudyPower(json,m_com,json);
        this->close();
        sp->show();
    }
        break;

    case ERROR:             //登陆失败
    {
        QMessageBox::warning(this,"登录","登陆失败!");
    }
        break;

    case NAMEORPASSWD:             //密码错误
    {
        QMessageBox::warning(this,"登录","登陆失败! 密码错误!");
    }
        break;

    case USERLOGIN:             //用户已登录
    {
        QMessageBox::warning(this,"登录","登陆失败! 用户已登录!");
    }
        break;

    default:
        break;
    }
}
