/********************************************************************************
** Form generated from reading UI file 'studypower.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STUDYPOWER_H
#define UI_STUDYPOWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StudyPower
{
public:
    QStackedWidget *stackedWidget;
    QWidget *main_widget;
    QLabel *main_username;
    QLabel *main_rank_num;
    QPushButton *main_ranking_list;
    QPushButton *main_train;
    QPushButton *main_rank;
    QWidget *train_widget;
    QLabel *label;
    QPushButton *train_suiji;
    QPushButton *train_lishi;
    QPushButton *train_changshi;
    QPushButton *train_gushi;
    QPushButton *train_back;
    QWidget *train_run;
    QLabel *train_question;
    QLCDNumber *train_lcdNumber;
    QLabel *train_right_answer;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *train_A;
    QPushButton *train_B;
    QPushButton *train_C;
    QPushButton *train_D;
    QWidget *train_result;
    QLabel *label_2;
    QLabel *train_score;
    QPushButton *train_result_back;
    QWidget *rank_wait;
    QLabel *label_3;
    QWidget *rank_match_result;
    QLabel *label_4;
    QLabel *rival_name;
    QLabel *rival_rank;
    QWidget *rank_run;
    QLCDNumber *rank_lcdNumber;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QPushButton *rank_A;
    QPushButton *rank_B;
    QPushButton *rank_C;
    QPushButton *rank_D;
    QLabel *rank_question;
    QLabel *rank_current_score;
    QWidget *rank_result;
    QLabel *label_5;
    QLabel *rank_my_score;
    QLabel *rank_rival_score;
    QLabel *rank_my_result;
    QPushButton *pushButton;
    QWidget *rivallist;
    QLabel *label_6;
    QLabel *rival_first;
    QLabel *rival_second;
    QLabel *rival_third;
    QPushButton *pushButton_2;

    void setupUi(QDialog *StudyPower)
    {
        if (StudyPower->objectName().isEmpty())
            StudyPower->setObjectName(QString::fromUtf8("StudyPower"));
        StudyPower->resize(489, 705);
        stackedWidget = new QStackedWidget(StudyPower);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(9, 9, 471, 691));
        main_widget = new QWidget();
        main_widget->setObjectName(QString::fromUtf8("main_widget"));
        main_username = new QLabel(main_widget);
        main_username->setObjectName(QString::fromUtf8("main_username"));
        main_username->setGeometry(QRect(30, 20, 281, 61));
        QFont font;
        font.setFamily(QString::fromUtf8("Adobe \351\273\221\344\275\223 Std R"));
        font.setPointSize(18);
        main_username->setFont(font);
        main_rank_num = new QLabel(main_widget);
        main_rank_num->setObjectName(QString::fromUtf8("main_rank_num"));
        main_rank_num->setGeometry(QRect(30, 70, 271, 61));
        main_rank_num->setFont(font);
        main_ranking_list = new QPushButton(main_widget);
        main_ranking_list->setObjectName(QString::fromUtf8("main_ranking_list"));
        main_ranking_list->setGeometry(QRect(120, 360, 221, 51));
        main_train = new QPushButton(main_widget);
        main_train->setObjectName(QString::fromUtf8("main_train"));
        main_train->setGeometry(QRect(120, 430, 221, 51));
        main_rank = new QPushButton(main_widget);
        main_rank->setObjectName(QString::fromUtf8("main_rank"));
        main_rank->setGeometry(QRect(120, 500, 221, 51));
        stackedWidget->addWidget(main_widget);
        train_widget = new QWidget();
        train_widget->setObjectName(QString::fromUtf8("train_widget"));
        label = new QLabel(train_widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 130, 391, 71));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(20);
        label->setFont(font1);
        train_suiji = new QPushButton(train_widget);
        train_suiji->setObjectName(QString::fromUtf8("train_suiji"));
        train_suiji->setGeometry(QRect(130, 330, 181, 51));
        QFont font2;
        font2.setFamily(QString::fromUtf8("AcadEref"));
        font2.setPointSize(12);
        train_suiji->setFont(font2);
        train_lishi = new QPushButton(train_widget);
        train_lishi->setObjectName(QString::fromUtf8("train_lishi"));
        train_lishi->setGeometry(QRect(130, 390, 181, 51));
        train_lishi->setFont(font2);
        train_changshi = new QPushButton(train_widget);
        train_changshi->setObjectName(QString::fromUtf8("train_changshi"));
        train_changshi->setGeometry(QRect(130, 450, 181, 51));
        train_changshi->setFont(font2);
        train_gushi = new QPushButton(train_widget);
        train_gushi->setObjectName(QString::fromUtf8("train_gushi"));
        train_gushi->setGeometry(QRect(130, 510, 181, 51));
        train_gushi->setFont(font2);
        train_back = new QPushButton(train_widget);
        train_back->setObjectName(QString::fromUtf8("train_back"));
        train_back->setGeometry(QRect(330, 590, 111, 41));
        train_back->setFont(font2);
        stackedWidget->addWidget(train_widget);
        train_run = new QWidget();
        train_run->setObjectName(QString::fromUtf8("train_run"));
        train_question = new QLabel(train_run);
        train_question->setObjectName(QString::fromUtf8("train_question"));
        train_question->setGeometry(QRect(40, 90, 401, 261));
        QFont font3;
        font3.setFamily(QString::fromUtf8("AcadEref"));
        font3.setPointSize(14);
        train_question->setFont(font3);
        train_question->setWordWrap(true);
        train_lcdNumber = new QLCDNumber(train_run);
        train_lcdNumber->setObjectName(QString::fromUtf8("train_lcdNumber"));
        train_lcdNumber->setGeometry(QRect(313, 20, 121, 51));
        train_right_answer = new QLabel(train_run);
        train_right_answer->setObjectName(QString::fromUtf8("train_right_answer"));
        train_right_answer->setGeometry(QRect(30, 630, 391, 41));
        layoutWidget = new QWidget(train_run);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 430, 401, 191));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        train_A = new QPushButton(layoutWidget);
        train_A->setObjectName(QString::fromUtf8("train_A"));

        verticalLayout->addWidget(train_A);

        train_B = new QPushButton(layoutWidget);
        train_B->setObjectName(QString::fromUtf8("train_B"));

        verticalLayout->addWidget(train_B);

        train_C = new QPushButton(layoutWidget);
        train_C->setObjectName(QString::fromUtf8("train_C"));

        verticalLayout->addWidget(train_C);

        train_D = new QPushButton(layoutWidget);
        train_D->setObjectName(QString::fromUtf8("train_D"));

        verticalLayout->addWidget(train_D);

        stackedWidget->addWidget(train_run);
        train_result = new QWidget();
        train_result->setObjectName(QString::fromUtf8("train_result"));
        label_2 = new QLabel(train_result);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(110, 50, 241, 151));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Adobe \351\273\221\344\275\223 Std R"));
        font4.setPointSize(24);
        label_2->setFont(font4);
        train_score = new QLabel(train_result);
        train_score->setObjectName(QString::fromUtf8("train_score"));
        train_score->setGeometry(QRect(40, 290, 381, 51));
        QFont font5;
        font5.setFamily(QString::fromUtf8("AcadEref"));
        font5.setPointSize(16);
        train_score->setFont(font5);
        train_result_back = new QPushButton(train_result);
        train_result_back->setObjectName(QString::fromUtf8("train_result_back"));
        train_result_back->setGeometry(QRect(330, 600, 111, 41));
        train_result_back->setFont(font2);
        stackedWidget->addWidget(train_result);
        rank_wait = new QWidget();
        rank_wait->setObjectName(QString::fromUtf8("rank_wait"));
        label_3 = new QLabel(rank_wait);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(80, 140, 301, 151));
        label_3->setFont(font4);
        stackedWidget->addWidget(rank_wait);
        rank_match_result = new QWidget();
        rank_match_result->setObjectName(QString::fromUtf8("rank_match_result"));
        label_4 = new QLabel(rank_match_result);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(130, 50, 191, 71));
        QFont font6;
        font6.setFamily(QString::fromUtf8("AcadEref"));
        font6.setPointSize(24);
        label_4->setFont(font6);
        rival_name = new QLabel(rank_match_result);
        rival_name->setObjectName(QString::fromUtf8("rival_name"));
        rival_name->setGeometry(QRect(30, 230, 371, 51));
        QFont font7;
        font7.setFamily(QString::fromUtf8("Adobe \351\273\221\344\275\223 Std R"));
        font7.setPointSize(20);
        rival_name->setFont(font7);
        rival_rank = new QLabel(rank_match_result);
        rival_rank->setObjectName(QString::fromUtf8("rival_rank"));
        rival_rank->setGeometry(QRect(30, 340, 371, 51));
        rival_rank->setFont(font7);
        stackedWidget->addWidget(rank_match_result);
        rank_run = new QWidget();
        rank_run->setObjectName(QString::fromUtf8("rank_run"));
        rank_lcdNumber = new QLCDNumber(rank_run);
        rank_lcdNumber->setObjectName(QString::fromUtf8("rank_lcdNumber"));
        rank_lcdNumber->setGeometry(QRect(320, 30, 121, 51));
        layoutWidget1 = new QWidget(rank_run);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(30, 440, 401, 191));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        rank_A = new QPushButton(layoutWidget1);
        rank_A->setObjectName(QString::fromUtf8("rank_A"));

        verticalLayout_2->addWidget(rank_A);

        rank_B = new QPushButton(layoutWidget1);
        rank_B->setObjectName(QString::fromUtf8("rank_B"));

        verticalLayout_2->addWidget(rank_B);

        rank_C = new QPushButton(layoutWidget1);
        rank_C->setObjectName(QString::fromUtf8("rank_C"));

        verticalLayout_2->addWidget(rank_C);

        rank_D = new QPushButton(layoutWidget1);
        rank_D->setObjectName(QString::fromUtf8("rank_D"));

        verticalLayout_2->addWidget(rank_D);

        rank_question = new QLabel(rank_run);
        rank_question->setObjectName(QString::fromUtf8("rank_question"));
        rank_question->setGeometry(QRect(30, 100, 411, 261));
        rank_question->setFont(font3);
        rank_question->setWordWrap(true);
        rank_current_score = new QLabel(rank_run);
        rank_current_score->setObjectName(QString::fromUtf8("rank_current_score"));
        rank_current_score->setGeometry(QRect(10, 30, 231, 51));
        rank_current_score->setFont(font7);
        stackedWidget->addWidget(rank_run);
        rank_result = new QWidget();
        rank_result->setObjectName(QString::fromUtf8("rank_result"));
        label_5 = new QLabel(rank_result);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(140, 80, 201, 81));
        label_5->setFont(font6);
        rank_my_score = new QLabel(rank_result);
        rank_my_score->setObjectName(QString::fromUtf8("rank_my_score"));
        rank_my_score->setGeometry(QRect(60, 230, 331, 61));
        QFont font8;
        font8.setFamily(QString::fromUtf8("AcadEref"));
        font8.setPointSize(20);
        rank_my_score->setFont(font8);
        rank_rival_score = new QLabel(rank_result);
        rank_rival_score->setObjectName(QString::fromUtf8("rank_rival_score"));
        rank_rival_score->setGeometry(QRect(60, 310, 331, 61));
        rank_rival_score->setFont(font8);
        rank_my_result = new QLabel(rank_result);
        rank_my_result->setObjectName(QString::fromUtf8("rank_my_result"));
        rank_my_result->setGeometry(QRect(60, 390, 331, 61));
        rank_my_result->setFont(font8);
        pushButton = new QPushButton(rank_result);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(290, 590, 131, 51));
        QFont font9;
        font9.setFamily(QString::fromUtf8("Adobe \351\273\221\344\275\223 Std R"));
        font9.setPointSize(16);
        pushButton->setFont(font9);
        stackedWidget->addWidget(rank_result);
        rivallist = new QWidget();
        rivallist->setObjectName(QString::fromUtf8("rivallist"));
        label_6 = new QLabel(rivallist);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(150, 50, 151, 91));
        QFont font10;
        font10.setFamily(QString::fromUtf8("Adobe \351\273\221\344\275\223 Std R"));
        font10.setPointSize(28);
        label_6->setFont(font10);
        rival_first = new QLabel(rivallist);
        rival_first->setObjectName(QString::fromUtf8("rival_first"));
        rival_first->setGeometry(QRect(20, 230, 441, 71));
        rival_first->setFont(font4);
        rival_second = new QLabel(rivallist);
        rival_second->setObjectName(QString::fromUtf8("rival_second"));
        rival_second->setGeometry(QRect(10, 320, 461, 71));
        rival_second->setFont(font4);
        rival_third = new QLabel(rivallist);
        rival_third->setObjectName(QString::fromUtf8("rival_third"));
        rival_third->setGeometry(QRect(10, 420, 461, 71));
        rival_third->setFont(font4);
        pushButton_2 = new QPushButton(rivallist);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(270, 560, 151, 61));
        pushButton_2->setFont(font7);
        stackedWidget->addWidget(rivallist);

        retranslateUi(StudyPower);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(StudyPower);
    } // setupUi

    void retranslateUi(QDialog *StudyPower)
    {
        StudyPower->setWindowTitle(QCoreApplication::translate("StudyPower", "Dialog", nullptr));
        main_username->setText(QCoreApplication::translate("StudyPower", "user :", nullptr));
        main_rank_num->setText(QCoreApplication::translate("StudyPower", "rank :", nullptr));
        main_ranking_list->setText(QCoreApplication::translate("StudyPower", "\346\216\222\350\241\214\346\246\234", nullptr));
        main_train->setText(QCoreApplication::translate("StudyPower", "\344\270\252\344\272\272\350\256\255\347\273\203\350\265\233", nullptr));
        main_rank->setText(QCoreApplication::translate("StudyPower", "\346\216\222\344\275\215\350\265\233", nullptr));
        label->setText(QCoreApplication::translate("StudyPower", "\344\270\252\344\272\272\350\256\255\347\273\203\346\250\241\345\274\217,\345\205\261\346\234\211\344\272\224\351\201\223\351\242\230", nullptr));
        train_suiji->setText(QCoreApplication::translate("StudyPower", "\351\232\217\346\234\272\351\242\230\345\272\223", nullptr));
        train_lishi->setText(QCoreApplication::translate("StudyPower", "\345\216\206\345\217\262\351\242\230\345\272\223", nullptr));
        train_changshi->setText(QCoreApplication::translate("StudyPower", "\345\270\270\350\257\206\351\242\230\345\272\223", nullptr));
        train_gushi->setText(QCoreApplication::translate("StudyPower", "\345\217\244\350\257\227\351\242\230\345\272\223", nullptr));
        train_back->setText(QCoreApplication::translate("StudyPower", "\350\277\224\345\233\236", nullptr));
        train_question->setText(QCoreApplication::translate("StudyPower", "\351\242\230\347\233\256", nullptr));
        train_right_answer->setText(QString());
        train_A->setText(QCoreApplication::translate("StudyPower", "A", nullptr));
        train_B->setText(QCoreApplication::translate("StudyPower", "B", nullptr));
        train_C->setText(QCoreApplication::translate("StudyPower", "C", nullptr));
        train_D->setText(QCoreApplication::translate("StudyPower", "D", nullptr));
        label_2->setText(QCoreApplication::translate("StudyPower", "     \350\256\255\347\273\203\347\273\223\346\235\237", nullptr));
        train_score->setText(QCoreApplication::translate("StudyPower", "\350\256\255\347\273\203\347\273\223\346\236\234", nullptr));
        train_result_back->setText(QCoreApplication::translate("StudyPower", "\350\277\224\345\233\236", nullptr));
        label_3->setText(QCoreApplication::translate("StudyPower", "\347\255\211\345\276\205\345\214\271\351\205\215\344\270\255. . .", nullptr));
        label_4->setText(QCoreApplication::translate("StudyPower", "\345\214\271\351\205\215\346\210\220\345\212\237", nullptr));
        rival_name->setText(QCoreApplication::translate("StudyPower", "rival name:", nullptr));
        rival_rank->setText(QCoreApplication::translate("StudyPower", "rival rank:", nullptr));
        rank_A->setText(QCoreApplication::translate("StudyPower", "A", nullptr));
        rank_B->setText(QCoreApplication::translate("StudyPower", "B", nullptr));
        rank_C->setText(QCoreApplication::translate("StudyPower", "C", nullptr));
        rank_D->setText(QCoreApplication::translate("StudyPower", "D", nullptr));
        rank_question->setText(QCoreApplication::translate("StudyPower", "\351\242\230\347\233\256", nullptr));
        rank_current_score->setText(QCoreApplication::translate("StudyPower", "Score:", nullptr));
        label_5->setText(QCoreApplication::translate("StudyPower", "\346\216\222\344\275\215\347\273\223\346\235\237", nullptr));
        rank_my_score->setText(QCoreApplication::translate("StudyPower", "\346\210\221\346\226\271\345\276\227\345\210\206:", nullptr));
        rank_rival_score->setText(QCoreApplication::translate("StudyPower", "\345\257\271\346\226\271\345\276\227\345\210\206:", nullptr));
        rank_my_result->setText(QCoreApplication::translate("StudyPower", "\346\216\222\344\275\215\347\273\223\346\236\234:", nullptr));
        pushButton->setText(QCoreApplication::translate("StudyPower", "\350\277\224\345\233\236", nullptr));
        label_6->setText(QCoreApplication::translate("StudyPower", "\346\216\222\350\241\214\346\246\234", nullptr));
        rival_first->setText(QString());
        rival_second->setText(QString());
        rival_third->setText(QString());
        pushButton_2->setText(QCoreApplication::translate("StudyPower", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StudyPower: public Ui_StudyPower {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STUDYPOWER_H
