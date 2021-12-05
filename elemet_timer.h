#ifndef ELEMET_TIMER_H
#define ELEMET_TIMER_H

#include <QDialog>
#include <QTime>
#include <QTimer>

static int current_index_timer = 1;


namespace Ui {
class Elemet_Timer;
}

class Elemet_Timer : public QDialog
{
    Q_OBJECT

public:
    explicit Elemet_Timer(QWidget *parent = nullptr);
    ~Elemet_Timer();
    QTime time;
    QTime _pause;
    QTimer *timer;
    QString Name;
    bool pause = false;
    int TimesToRepeat;
signals:
    void return_element_timer(Elemet_Timer *element);
private slots:


    void on_set_time_clicked();
    void stop_timer();

private:
    Ui::Elemet_Timer *ui;
};

#endif // ELEMET_TIMER_H
