#ifndef STUDYPOWER_H
#define STUDYPOWER_H

#include <QDialog>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QJsonArray>
#include "communicate.h"
#include <QTimer>
namespace Ui {
class StudyPower;
}

class StudyPower : public QDialog
{
    Q_OBJECT

public:
    explicit StudyPower(QJsonObject json,Communicate *,QJsonObject,QWidget *parent = nullptr);
    void train_SetQuestion();//更新问题
    void show_train_rightAnswer(); //展示正确答案
    void rank_SetQuestion();
    ~StudyPower();

private slots:
    void rival_list_cb(QJsonObject);

    void rankscore_cb(QJsonObject);

    void rank_runningTimeout();

    void rank_timeout();

    void getquestion_cb(QJsonObject);

    void rank_cb(QJsonObject);

    void train_timeout();               //训练计时器timeout信号

    void on_train_back_clicked();

    void on_main_train_clicked();

    void on_train_suiji_clicked();

    void on_train_lishi_clicked();

    void on_train_changshi_clicked();

    void on_train_gushi_clicked();

    void on_train_result_back_clicked();

    void on_train_A_clicked();

    void on_train_B_clicked();

    void on_train_C_clicked();

    void on_train_D_clicked();

    void on_main_rank_clicked();

    void on_rank_A_clicked();

    void on_rank_B_clicked();

    void on_rank_C_clicked();

    void on_rank_D_clicked();

    void on_pushButton_clicked();

    void on_main_ranking_list_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::StudyPower *ui;
    Communicate *m_com;
    QJsonObject m_json;
    int m_rank;

    int m_train_current_question;     //训练赛的当前题号
    int m_train_score;                //训练赛的得分
    int m_trainSec;                   //训练赛的读秒
    int m_trainRightAnswer;           //训练赛正确答案
    int m_trainAnswer;                //用户的答案
    QJsonObject m_trainJson;          //训练赛的问题和答案
    QTimer m_trainTimer;              //训练计时器
    int m_train_answer_condition;     //答题状态标志位(按键了答错 1 ，没按键 0)

/*****************************rank*************************************************/
    QString m_rank_rivalName;           //获取对手名称
    int m_rank_current_question;
    int m_rank_score;
    int m_rankSec;
    int m_rankRightAnswer;
    int m_rankAnswer;
    QJsonObject m_rankJson;
    QTimer m_rankTimer;
    QTimer m_rankRuningTimer;           //答题计时器
    int m_rank_score_condition;        //已经给服务器发送我方分数的状态（已发送 1，未发送 0）
};

#endif // STUDYPOWER_H
