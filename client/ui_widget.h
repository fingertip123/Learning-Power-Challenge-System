/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *username;
    QLineEdit *password;
    QPushButton *log_in_button;
    QPushButton *register_button;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(800, 600);
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(150, 190, 111, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("AcadEref"));
        font.setPointSize(18);
        label->setFont(font);
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(150, 280, 111, 51));
        label_2->setFont(font);
        username = new QLineEdit(Widget);
        username->setObjectName(QString::fromUtf8("username"));
        username->setGeometry(QRect(300, 200, 241, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("AcadEref"));
        font1.setPointSize(12);
        username->setFont(font1);
        password = new QLineEdit(Widget);
        password->setObjectName(QString::fromUtf8("password"));
        password->setGeometry(QRect(300, 290, 241, 41));
        password->setFont(font1);
        log_in_button = new QPushButton(Widget);
        log_in_button->setObjectName(QString::fromUtf8("log_in_button"));
        log_in_button->setGeometry(QRect(170, 480, 121, 51));
        QFont font2;
        font2.setFamily(QString::fromUtf8("AcadEref"));
        font2.setPointSize(14);
        log_in_button->setFont(font2);
        register_button = new QPushButton(Widget);
        register_button->setObjectName(QString::fromUtf8("register_button"));
        register_button->setGeometry(QRect(420, 480, 121, 51));
        register_button->setFont(font2);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\345\257\206  \347\240\201", nullptr));
        log_in_button->setText(QCoreApplication::translate("Widget", "\347\231\273 \345\275\225", nullptr));
        register_button->setText(QCoreApplication::translate("Widget", "\346\263\250 \345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
