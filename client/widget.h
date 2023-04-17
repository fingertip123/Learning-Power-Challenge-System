#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include "register.h"
#include "communicate.h"
#include "studypower.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_log_in_button_clicked();

    void on_register_button_clicked();  //处理注册新号的槽函数
    void login_cb(QJsonObject);                 //处理登陆信号的槽函数

private:
    Ui::Widget *ui;
    Communicate *m_com;
};
#endif // WIDGET_H
