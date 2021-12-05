#ifndef TIMERW_H
#define TIMERW_H

#include <QDialog>
#include <elemet_timer.h>

namespace Ui {
class TimerW;
}

class TimerW : public QDialog
{
    Q_OBJECT

public:
    explicit TimerW(QWidget *parent = nullptr);
    ~TimerW();
signals:
    void timer_ring();

private slots:
    void on_start_stop_timer_clicked();

    void on_add_new_timer_clicked();
    void push_timer(Elemet_Timer *element);
    void check_timer();
    void output_correct_tbutton_name();
    void on_delete_timer_clicked();

    void on_pause_continue_timer_clicked();


    void output_list_of_timers();
private:
    Ui::TimerW *ui;
    QVector<Elemet_Timer*> timers;
    int TimesToRepeat=1;
};

#endif // TIMERW_H
