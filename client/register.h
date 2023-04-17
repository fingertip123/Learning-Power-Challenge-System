#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>//打印窗口使用的头文件
#include "common.h"
#include "communicate.h"
namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(Communicate *com,QWidget *parent = nullptr);
    ~Register();

private slots:
    void on_register__clicked();

    void on_register_back_clicked();

    void register_cb(int);//处理注册新号的槽函数

private:
    Ui::Register *ui;
    Communicate *m_com;
};

#endif // REGISTER_H
