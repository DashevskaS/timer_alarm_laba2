#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "timerw.h"
#include "alarmw.h"
#include "ring.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_timer_clicked();
    void call_ring();

    void on_alarm_clicked();

//    void on_not_disturb_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    TimerW *timers = new TimerW;
    AlarmW *alarms = new AlarmW;
    Ring general_ring;



};
#endif // MAINWINDOW_H
