/********************************************************************************
** Form generated from reading UI file 'register.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTER_H
#define UI_REGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Register
{
public:
    QLabel *label;
    QLineEdit *register_username;
    QPushButton *register_;
    QLabel *label_2;
    QPushButton *register_back;
    QLineEdit *register_password;

    void setupUi(QDialog *Register)
    {
        if (Register->objectName().isEmpty())
            Register->setObjectName(QString::fromUtf8("Register"));
        Register->resize(730, 624);
        label = new QLabel(Register);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(140, 190, 111, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("AcadEref"));
        font.setPointSize(18);
        label->setFont(font);
        register_username = new QLineEdit(Register);
        register_username->setObjectName(QString::fromUtf8("register_username"));
        register_username->setGeometry(QRect(290, 200, 241, 51));
        register_ = new QPushButton(Register);
        register_->setObjectName(QString::fromUtf8("register_"));
        register_->setGeometry(QRect(160, 480, 121, 51));
        QFont font1;
        font1.setFamily(QString::fromUtf8("AcadEref"));
        font1.setPointSize(14);
        register_->setFont(font1);
        label_2 = new QLabel(Register);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(140, 280, 111, 51));
        label_2->setFont(font);
        register_back = new QPushButton(Register);
        register_back->setObjectName(QString::fromUtf8("register_back"));
        register_back->setGeometry(QRect(410, 480, 121, 51));
        register_back->setFont(font1);
        register_password = new QLineEdit(Register);
        register_password->setObjectName(QString::fromUtf8("register_password"));
        register_password->setGeometry(QRect(290, 290, 241, 51));

        retranslateUi(Register);

        QMetaObject::connectSlotsByName(Register);
    } // setupUi

    void retranslateUi(QDialog *Register)
    {
        Register->setWindowTitle(QCoreApplication::translate("Register", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Register", "\347\224\250\346\210\267\345\220\215", nullptr));
        register_->setText(QCoreApplication::translate("Register", "\346\263\250 \345\206\214", nullptr));
        label_2->setText(QCoreApplication::translate("Register", "\345\257\206  \347\240\201", nullptr));
        register_back->setText(QCoreApplication::translate("Register", "\350\277\224 \345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Register: public Ui_Register {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTER_H
