#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setStyleSheet("color: black; background-color: #E9E9E9;");
    this->setWindowTitle("годинник");
    connect(timers, SIGNAL(timer_ring()), this, SLOT(call_ring()));
    connect(alarms, SIGNAL(alarm_ring()), this, SLOT(call_ring()));
    QString path = QDir::currentPath();

    path = path.left(path.lastIndexOf(QChar('/')));
    path += "/Users/sofia/Downloads/Telegram Desktop/динь динь.mp3";
    general_ring.file_dialog.setDirectory(path);
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_timer_clicked()
{

        timers->show();
        timers->setWindowTitle("таймер");

}
void MainWindow::call_ring(){
    bool flag = ui->not_disturb->checkState();
    if(!flag){
        general_ring.call();
    }else{
        QMessageBox ms;
        ms.warning(this, "попередження", "час вичерпано");
    }
}

void MainWindow::on_alarm_clicked()
{
    alarms->show();
    alarms->setWindowTitle("будильник");

}




