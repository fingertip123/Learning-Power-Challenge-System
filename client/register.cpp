#include "register.h"
#include "ui_register.h"

Register::Register(Communicate *com,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    m_com = com;

    connect(m_com,SIGNAL(register_cb(int)),this,SLOT(register_cb(int)));//注册信号的接收
}

Register::~Register()
{
    delete ui;
}

void Register::on_register__clicked()
{
    QString R_username = ui->register_username->text();
    QString R_password = ui->register_password->text();

    //将里面的数据发送给服务器
    QJsonObject json;
    json["cmd"] = REGISTER;
    json["username"] = R_username;
    json["password"] = R_password;

    m_com->writeData(json);
}

void Register::on_register_back_clicked()
{
    this->close();
}

void Register::register_cb(int result)
{
    switch (result) {
    case OK:
        QMessageBox::information(this,"注册","注册成功！");
        break;
    case ERROR:
        QMessageBox::information(this,"注册","注册失败，未知错误！");
        break;
    case USEREXIT:
        QMessageBox::information(this,"注册","用户已存在！");
        break;
    default:
        break;
    }
}
