#include "timerw.h"
#include "ui_timerw.h"

TimerW::TimerW(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimerW)
{
    ui->setupUi(this);
    this->setStyleSheet("color: black; background-color: #E9E9E9;");
    QTimer *timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(output_list_of_timers()));
    timer->start(10);
}

TimerW::~TimerW()
{
    delete ui;
}

void TimerW::on_start_stop_timer_clicked()
{
    int current_row = ui->list_of_timers->currentRow();
    if(timers[current_row]->timer->isActive() || timers[current_row]->pause){
        timers[current_row]->pause = false;
        timers[current_row]->_pause.setHMS(0, 0, 0);
        timers[current_row]->timer->stop();
    }else{
        timers[current_row]->timer->start(timers[current_row]->time.msecsSinceStartOfDay());
    }
}


void TimerW::on_add_new_timer_clicked()
{
    Elemet_Timer *el = new Elemet_Timer;
    el->show();
    connect(el, SIGNAL(return_element_timer(Elemet_Timer*)), this, SLOT(push_timer(Elemet_Timer*)));
}
void TimerW::push_timer(Elemet_Timer *element){
    timers.push_back(element);
    connect(element->timer, SIGNAL(timeout()), this, SLOT(check_timer()));
}
void TimerW::check_timer(){
    emit timer_ring();
}
void TimerW::output_correct_tbutton_name(){
    int current_row = -1;
    current_row = ui->list_of_timers->currentRow();
    //button start|stop
    {
        if(current_row == -1){
            ui->start_stop_timer->setHidden(true);
        }else{
            ui->start_stop_timer->setHidden(false);
            if (timers[current_row]->timer->isActive() || timers[current_row]->pause){
                ui->start_stop_timer->setText("стоп");
            }else{
                ui->start_stop_timer->setText("старт");
            }
        }
    }
    //button delete
    {
        if(current_row == -1)
            ui->delete_timer->setHidden(true);
        else
            ui->delete_timer->setHidden(false);
    }
    //button pause|continue
    {
        if(current_row == -1 || (!timers[current_row]->timer->isActive() && !timers[current_row]->pause)){
            ui->pause_continue_timer->setHidden(true);
        }else{
            ui->pause_continue_timer->setHidden(false);
            if(timers[current_row]->timer->isActive() && !timers[current_row]->pause){
                ui->pause_continue_timer->setText("пауза");
            }else{
                ui->pause_continue_timer->setText("продолжить");
            }
        }
    }

}

void TimerW::on_delete_timer_clicked()
{
    int current_row = ui->list_of_timers->currentRow();
    timers[current_row]->~Elemet_Timer();
    timers.erase(timers.begin()+current_row);
}


void TimerW::on_pause_continue_timer_clicked()
{
    Elemet_Timer *element = timers[ui->list_of_timers->currentRow()];
    if(element->pause){
        element->pause = false;
        element->timer->start(element->_pause.msecsSinceStartOfDay());
        element->_pause.setHMS(0, 0, 0);
    }else{
        element->pause = true;
        element->_pause = element->_pause.addMSecs(element->timer->remainingTime());
        element->timer->stop();
    }
}

void TimerW::output_list_of_timers(){
    output_correct_tbutton_name();
    int current_row = ui->list_of_timers->currentRow();
    ui->list_of_timers->clear();
    int size_of_list = timers.size();
    for(int i = 0; i < size_of_list; i++){
        QString s;
        s = QString::number(i+1)+") ";
        s = s + timers[i]->Name;
        s = s + timers[i]->time.toString("\th:mm:ss");
        if(timers[i]->timer->isActive() || timers[i]->pause){
            if(!timers[i]->pause){
                QTime t (0, 0, 0);
                t = t.addMSecs(timers[i]->timer->remainingTime());
                s = s + " "+t.toString("h:mm:ss");
            }else{
                s = s + " "+timers[i]->_pause.toString("h:mm:ss");
            }
        }
        ui->list_of_timers->addItem(s);
        if(!timers[i]->timer->isActive() && !timers[i]->pause)
            ui->list_of_timers->item(i)->setForeground(Qt::red);
    }
    ui->list_of_timers->setCurrentRow(current_row);
}
