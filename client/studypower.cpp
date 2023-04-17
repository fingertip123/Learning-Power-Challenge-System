#include "studypower.h"
#include "ui_studypower.h"

StudyPower::StudyPower(QJsonObject json,Communicate *com,QJsonObject ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudyPower)
{
    ui->setupUi(this);
    m_com = com;
    m_json = json;
    //解析
    QString str = QString("user :   %1").arg(m_json["username"].toString());
    ui->main_username->setText(str);
    QString ptr = QString("rank :   %1").arg(m_json["rank_num"].toInt());
    ui->main_rank_num->setText(ptr);
    m_rank = m_json["rank_num"].toInt();

    connect(m_com,SIGNAL(getquestion_cb(QJsonObject)),this,SLOT(getquestion_cb(QJsonObject)));
    connect(&m_trainTimer,SIGNAL(timeout()),this,SLOT(train_timeout()));

    connect(m_com,SIGNAL(rank_cb(QJsonObject)),this,SLOT(rank_cb(QJsonObject)));
    connect(&m_rankTimer,SIGNAL(timeout()),this,SLOT(rank_timeout()));
    connect(&m_rankRuningTimer,SIGNAL(timeout()),this,SLOT(rank_runningTimeout()));

    connect(m_com,SIGNAL(rankscore_cb(QJsonObject)),this,SLOT(rankscore_cb(QJsonObject)));

    connect(m_com,SIGNAL(rival_list_cb(QJsonObject)),this,SLOT(rival_list_cb(QJsonObject)));
}

StudyPower::~StudyPower()
{
    delete ui;
}

void StudyPower::on_train_back_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->main_widget);
}

void StudyPower::on_main_train_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->train_widget);
}

void StudyPower::on_train_suiji_clicked()
{
    //向服务器索要随机题库
    QJsonObject json;
    json["cmd"] = GETQUESTION;
    json["type"] = SUIJI;

    m_com->writeData(json);
}

void StudyPower::on_train_lishi_clicked()
{
    QJsonObject json;
    json["cmd"] = GETQUESTION;
    json["type"] = LISHI;

    m_com->writeData(json);
}

void StudyPower::on_train_changshi_clicked()
{
    QJsonObject json;
    json["cmd"] = GETQUESTION;
    json["type"] = CHANGSHI;

    m_com->writeData(json);
}

void StudyPower::on_train_gushi_clicked()
{
    QJsonObject json;
    json["cmd"] = GETQUESTION;
    json["type"] = GUSHI;

    m_com->writeData(json);
}

void StudyPower::getquestion_cb(QJsonObject Injson)
{
    //初始化
    if(OK != Injson["result"].toInt())
    {
        QMessageBox::warning(this,"训练模式","题目获取失败！");
        return;
    }
    else
    {
        m_train_current_question = 0;
        m_train_score = 0;

        m_trainJson = Injson["question"].toObject();//获取question的json格式
        ui->stackedWidget->setCurrentWidget(ui->train_run);
        train_SetQuestion();
    }
}

void StudyPower::train_SetQuestion()
{
    QString str = QString("正确答案");
    ui->train_right_answer->setText(str);
    m_train_answer_condition = 0;//未作答
    m_trainSec = 10;
    //打开计时器
    m_trainTimer.start(1000);//每秒钟发出一次timeout信号
    ui->train_lcdNumber->display(m_trainSec);
    m_trainRightAnswer = m_trainJson["answer"].toArray().at(m_train_current_question).toString().toInt();
    ui->train_question->setText(m_trainJson["question"].toArray().at(m_train_current_question).toString());
    ui->train_A->setText(m_trainJson["selection1"].toArray().at(m_train_current_question).toString());
    ui->train_B->setText(m_trainJson["selection2"].toArray().at(m_train_current_question).toString());
    ui->train_C->setText(m_trainJson["selection3"].toArray().at(m_train_current_question).toString());
    ui->train_D->setText(m_trainJson["selection4"].toArray().at(m_train_current_question).toString());

    ui->train_A->setEnabled(1);//按键生效
    ui->train_B->setEnabled(1);
    ui->train_C->setEnabled(1);
    ui->train_D->setEnabled(1);
}


void StudyPower::train_timeout()
{
    m_trainSec--;//倒计时减1
    ui->train_lcdNumber->display(m_trainSec);//显示倒计时
    if(0 == m_trainSec)//答题失败
    {
        if(0 == m_train_answer_condition)//未作答，超时
        {
            m_trainSec = 3;
            show_train_rightAnswer();
            m_train_answer_condition = 1;  //标志位切换
        }
        else if(1 == m_train_answer_condition)//答错了  已经显示了3s正确答案
        {
            m_train_current_question++;
            if(5 == m_train_current_question)//已完成所有题目
            {
                m_trainTimer.stop();//关闭计时器
                ui->stackedWidget->setCurrentWidget(ui->train_result);
                QString str = QString("本次训练赛得分为 :   %1  ").arg(m_train_score);//显示分数
                ui->train_score->setText(str);
            }
            else
            {
                train_SetQuestion();//超时进入下一题
            }
        }

    }
}

void StudyPower::on_train_A_clicked()
{
    ui->train_A->setDisabled(1);//按键失效，避免抢答出正确答案
    ui->train_B->setDisabled(1);
    ui->train_C->setDisabled(1);
    ui->train_D->setDisabled(1);
    m_train_answer_condition = 1;//避免出现二次三秒倒计时
    m_trainAnswer = 1;
    if(m_trainAnswer == m_trainRightAnswer)//选择正确，加分，下一题
    {
        m_train_score += 20;
        m_train_current_question++;
        if(5 == m_train_current_question)//已完成所有题目
        {
            m_trainTimer.stop();//关闭计时器
            ui->stackedWidget->setCurrentWidget(ui->train_result);
            QString str = QString("本次训练赛得分为 :   %1  ").arg(m_train_score);//显示分数
            ui->train_score->setText(str);
        }
        else
        {
            train_SetQuestion();//超时进入下一题
        }
    }
    else    //回答错误  显示正确答案三秒钟 进入下一题
    {
        m_trainSec = 3;
        show_train_rightAnswer();

    }
}

void StudyPower::on_train_B_clicked()
{
    ui->train_A->setDisabled(1);//按键失效，避免抢答出正确答案
    ui->train_B->setDisabled(1);
    ui->train_C->setDisabled(1);
    ui->train_D->setDisabled(1);
    m_train_answer_condition = 1;
    m_trainAnswer = 2;
    if(m_trainAnswer == m_trainRightAnswer)//选择正确，加分，下一题
    {
        m_train_score += 20;
        m_train_current_question++;
        if(5 == m_train_current_question)//已完成所有题目
        {
            m_trainTimer.stop();//关闭计时器
            ui->stackedWidget->setCurrentWidget(ui->train_result);
            QString str = QString("本次训练赛得分为 :   %1  ").arg(m_train_score);//显示分数
            ui->train_score->setText(str);
        }
        else
        {
            train_SetQuestion();//超时进入下一题
        }
    }
    else    //回答错误  显示正确答案三秒钟 进入下一题
    {
        m_trainSec = 3;
        show_train_rightAnswer();

    }
}

void StudyPower::on_train_C_clicked()
{
    ui->train_A->setDisabled(1);//按键失效，避免抢答出正确答案
    ui->train_B->setDisabled(1);
    ui->train_C->setDisabled(1);
    ui->train_D->setDisabled(1);
    m_train_answer_condition = 1;
    m_trainAnswer = 3;
    if(m_trainAnswer == m_trainRightAnswer)//选择正确，加分，下一题
    {
        m_train_score += 20;
        m_train_current_question++;
        if(5 == m_train_current_question)//已完成所有题目
        {
            m_trainTimer.stop();//关闭计时器
            ui->stackedWidget->setCurrentWidget(ui->train_result);
            QString str = QString("本次训练赛得分为 :   %1  ").arg(m_train_score);//显示分数
            ui->train_score->setText(str);
        }
        else
        {
            train_SetQuestion();//超时进入下一题
        }
    }
    else    //回答错误  显示正确答案三秒钟 进入下一题
    {
        m_trainSec = 3;
        show_train_rightAnswer();

    }
}

void StudyPower::on_train_D_clicked()
{
    ui->train_A->setDisabled(1);//按键失效，避免抢答出正确答案
    ui->train_B->setDisabled(1);
    ui->train_C->setDisabled(1);
    ui->train_D->setDisabled(1);
    m_train_answer_condition = 1;
    m_trainAnswer = 4;
    if(m_trainAnswer == m_trainRightAnswer)//选择正确，加分，下一题
    {
        m_train_score += 20;
        m_train_current_question++;
        if(5 == m_train_current_question)//已完成所有题目
        {
            m_trainTimer.stop();//关闭计时器
            ui->stackedWidget->setCurrentWidget(ui->train_result);
            QString str = QString("本次训练赛得分为 :   %1  ").arg(m_train_score);//显示分数
            ui->train_score->setText(str);
        }
        else
        {
            train_SetQuestion();//超时进入下一题
        }
    }
    else    //回答错误  显示正确答案三秒钟 进入下一题
    {
        m_trainSec = 3;
        show_train_rightAnswer();

    }
}

void StudyPower::show_train_rightAnswer()
{
    switch(m_trainRightAnswer)
    {
    case 1:
    {
         QString str = QString("正确答案为 :   %1  ").arg(m_trainJson["selection1"].toArray().at(m_train_current_question).toString());
         ui->train_right_answer->setText(str);
    }
        break;
    case 2:
    {
         QString str = QString("正确答案为 :   %1  ").arg(m_trainJson["selection2"].toArray().at(m_train_current_question).toString());
         ui->train_right_answer->setText(str);
    }
        break;
    case 3:
    {
         QString str = QString("正确答案为 :   %1  ").arg(m_trainJson["selection3"].toArray().at(m_train_current_question).toString());
         ui->train_right_answer->setText(str);
    }
        break;
    case 4:
    {
         QString str = QString("正确答案为 :   %1  ").arg(m_trainJson["selection4"].toArray().at(m_train_current_question).toString());
         ui->train_right_answer->setText(str);
    }
        break;
    default:
        break;
    }
}

void StudyPower::on_train_result_back_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->main_widget);
}

void StudyPower::on_main_rank_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->rank_wait);
    //向服务器发送消息
    QJsonObject json;
    json["cmd"] = RANK;
    json["rank_num"] = m_rank;

    m_com->writeData(json);
}

void StudyPower::rank_cb(QJsonObject Injson)
{
    if(OK != Injson["result"].toInt())
    {
        QMessageBox::warning(this,"排位模式","题目获取失败！");
        return;
    }
    //界面跳转到匹配界面
    ui->stackedWidget->setCurrentWidget(ui->rank_match_result);
    //用计时器实现匹配界面等待三秒
    m_rankSec = 3;
    m_rank_score_condition = 0;
    m_rankTimer.start(1000);
    m_rank_rivalName = Injson["rivalName"].toString();
    QString str = QString("rival_name : %1 ").arg(Injson["rivalName"].toString());
    ui->rival_name->setText(str);
    QString ptr = QString("rival_rank : %1 ").arg(Injson["rivalrank"].toInt());
    ui->rival_rank->setText(ptr);
    m_rank_score = 0;//排位赛初始成绩
    m_rank_current_question = 0;  //初始化题目
    m_rankJson = Injson["question"].toObject();//获取question的json格式
}

void StudyPower::rank_timeout()
{
    m_rankSec--;
    if(0 == m_rankSec)
    {
        ui->stackedWidget->setCurrentWidget(ui->rank_run);
        rank_SetQuestion();
        m_rankTimer.stop();
    }
}

void StudyPower::rank_SetQuestion()
{

    m_rankSec = 10;
    //打开计时器
    m_rankRuningTimer.start(1000);//每秒钟发出一次timeout信号
    ui->rank_lcdNumber->display(m_rankSec);
    m_rankRightAnswer = m_rankJson["answer"].toArray().at(m_rank_current_question).toString().toInt();
    ui->rank_question->setText(m_trainJson["question"].toArray().at(m_rank_current_question).toString());
    ui->rank_A->setText(m_rankJson["selection1"].toArray().at(m_rank_current_question).toString());
    ui->rank_B->setText(m_rankJson["selection2"].toArray().at(m_rank_current_question).toString());
    ui->rank_C->setText(m_rankJson["selection3"].toArray().at(m_rank_current_question).toString());
    ui->rank_D->setText(m_rankJson["selection4"].toArray().at(m_rank_current_question).toString());
    //每次题目变更，刷新得分
    QString str = QString("当前得分 : %1").arg(m_rank_score);
    ui->rank_current_score->setText(str);

    ui->rank_A->setEnabled(1);//按键生效
    ui->rank_B->setEnabled(1);
    ui->rank_C->setEnabled(1);
    ui->rank_D->setEnabled(1);
}


void StudyPower::on_rank_A_clicked()
{
    ui->rank_A->setDisabled(1);
    ui->rank_B->setDisabled(1);
    ui->rank_C->setDisabled(1);
    ui->rank_D->setDisabled(1);

    m_rankAnswer = 1;
    if(m_rankAnswer == m_rankRightAnswer)//选择正确，加分，下一题，谁先获得100分，谁先获胜
    {
        m_rank_score += 20;
        if(100 > m_rank_score)
        {
            m_rank_current_question++;
            rank_SetQuestion();
        }
        else
        {
            QJsonObject json;
            json["cmd"] = RANKSCORE;
            json["score"] = m_rank_score;
            json["rivalName"] = m_rank_rivalName;

            m_com->writeData(json);
            m_rank_score_condition = 1;
        }


    }
    else    //回答错误  直接进入下一题
    {
         m_rank_current_question++;
         rank_SetQuestion();
    }
}

void StudyPower::on_rank_B_clicked()
{
    ui->rank_A->setDisabled(1);
    ui->rank_B->setDisabled(1);
    ui->rank_C->setDisabled(1);
    ui->rank_D->setDisabled(1);

    m_rankAnswer = 2;
    if(m_rankAnswer == m_rankRightAnswer)//选择正确，加分，下一题，谁先获得100分，谁先获胜
    {
        m_rank_score += 20;
        if(100 > m_rank_score)
        {
            m_rank_current_question++;
            rank_SetQuestion();
        }
        else
        {
            QJsonObject json;
            json["cmd"] = RANKSCORE;
            json["score"] = m_rank_score;
            json["rivalName"] = m_rank_rivalName;

            m_com->writeData(json);
            m_rank_score_condition = 1;
        }


    }
    else    //回答错误  直接进入下一题
    {
         m_rank_current_question++;
         rank_SetQuestion();
    }
}

void StudyPower::on_rank_C_clicked()
{
    ui->rank_A->setDisabled(1);
    ui->rank_B->setDisabled(1);
    ui->rank_C->setDisabled(1);
    ui->rank_D->setDisabled(1);

    m_rankAnswer = 3;
    if(m_rankAnswer == m_rankRightAnswer)//选择正确，加分，下一题，谁先获得100分，谁先获胜
    {
        m_rank_score += 20;
        if(100 > m_rank_score)
        {
            m_rank_current_question++;
            rank_SetQuestion();
        }
        else
        {
            QJsonObject json;
            json["cmd"] = RANKSCORE;
            json["score"] = m_rank_score;
            json["rivalName"] = m_rank_rivalName;

            m_com->writeData(json);
            m_rank_score_condition = 1;
        }
    }
    else    //回答错误  直接进入下一题
    {
         m_rank_current_question++;
         rank_SetQuestion();
    }
}

void StudyPower::on_rank_D_clicked()
{
    ui->rank_A->setDisabled(1);
    ui->rank_B->setDisabled(1);
    ui->rank_C->setDisabled(1);
    ui->rank_D->setDisabled(1);

    m_rankAnswer = 4;
    if(m_rankAnswer == m_rankRightAnswer)//选择正确，加分，下一题，谁先获得100分，谁先获胜
    {
        m_rank_score += 20;
        if(100 > m_rank_score)
        {
            m_rank_current_question++;
            rank_SetQuestion();
        }
        else
        {
            QJsonObject json;
            json["cmd"] = RANKSCORE;
            json["score"] = m_rank_score;
            json["rivalName"] = m_rank_rivalName;

            m_com->writeData(json);
            m_rank_score_condition = 1;
        }

    }
    else    //回答错误  直接进入下一题
    {
         m_rank_current_question++;
         rank_SetQuestion();
    }
}

void StudyPower::rank_runningTimeout()              //答题计时器的timeout
{
    m_rankSec--;
    ui->rank_lcdNumber->display(m_rankSec);
    if(0 == m_rankSec)          //超时作答,不加分,直接前往下一题
    {
        m_rank_current_question++;
        rank_SetQuestion();
    }
}

void StudyPower::rankscore_cb(QJsonObject Injson)
{
    m_rankRuningTimer.stop();
    if(0 == m_rank_score_condition)  //未发送我方得分
    {
        QJsonObject json;
        json["cmd"] = RANKSCORE;
        json["score"] = m_rank_score;
        json["rivalName"] = m_rank_rivalName;

        m_com->writeData(json);
        m_rank_score_condition = 1;

        int score = Injson["rivalScore"].toInt();
        if(m_rank_score < score)        //排位赛失败
        {
            m_rank_score -= 4;
            QString ztr = QString("排位结果 ： %1 ----> %2 ").arg(m_rank + 4).arg(m_rank);
            ui->rank_my_score->setText(ztr);
        }
        else
        {
            m_rank_score += 5;
            QString ztr = QString("排位结果 ： %1 ----> %2 ").arg(m_rank - 5).arg(m_rank);
            ui->rank_my_score->setText(ztr);
        }
        json["cmd"] = RANKRESULT;
        json["rank_num"] = m_rank;

        m_com->writeData(json);
        ui->stackedWidget->setCurrentWidget(ui->rank_result);
        QString str = QString("我方得分 ： %1").arg(m_rank_score);
        ui->rank_my_score->setText(str);
        QString ptr = QString("对方得分 ： %1").arg(score);
        ui->rank_my_score->setText(ptr);

    }
    else                //已发送
    {
        int score = Injson["rivalScore"].toInt();
        if(m_rank_score < score)        //排位赛失败
        {
            m_rank_score -= 4;
            QString ztr = QString("排位结果 ： %1 ----> %2 ").arg(m_rank + 4).arg(m_rank);
            ui->rank_my_score->setText(ztr);
        }
        else
        {
            m_rank_score += 5;
            QString ztr = QString("排位结果 ： %1 ----> %2 ").arg(m_rank - 5).arg(m_rank);
            ui->rank_my_score->setText(ztr);
        }
        QJsonObject json;
        json["cmd"] = RANKRESULT;
        json["rank_num"] = m_rank;

        m_com->writeData(json);
        ui->stackedWidget->setCurrentWidget(ui->rank_result);
        QString str = QString("我方得分 ： %1").arg(m_rank_score);
        ui->rank_my_score->setText(str);
        QString ptr = QString("对方得分 ： %1").arg(score);
        ui->rank_my_score->setText(ptr);

    }
}

void StudyPower::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->main_widget);
    QString ptr = QString("rank :   %1").arg(m_rank);
    ui->main_rank_num->setText(ptr);
}

void StudyPower::on_main_ranking_list_clicked()
{
    QJsonObject json;
    json["cmd"] = RIVALLIST;

    m_com->writeData(json);
}

void StudyPower::rival_list_cb(QJsonObject Injson)
{
    ui->stackedWidget->setCurrentWidget(ui->rivallist);
    QJsonObject listJson = Injson["rivallist"].toObject();
    QString str = QString("第一名 : %1    %2").arg(listJson["name"].toArray().at(0).toString())
            .arg(listJson["rank_num"].toArray().at(0).toString().toInt());
    ui->rival_first->setText(str);
    QString ptr = QString("第二名 : %1    %2").arg(listJson["name"].toArray().at(1).toString())
            .arg(listJson["rank_num"].toArray().at(1).toString().toInt());
    ui->rival_second->setText(ptr);
    QString ztr = QString("第三名 : %1    %2").arg(listJson["name"].toArray().at(2).toString())
            .arg(listJson["rank_num"].toArray().at(2).toString().toInt());
    ui->rival_third->setText(ztr);
}

void StudyPower::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->main_widget);
}
