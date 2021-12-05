#include "ring.h"
#include "ui_ring.h"
#include <QDebug>

Ring::Ring(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ring)
{
    ui->setupUi(this);
    this->setStyleSheet("color: black; background-color: #E9E9E9;");


    player.setMedia(QUrl::fromLocalFile("/Users/sofia/Downloads/Telegram Desktop/динь динь.mp3"));
    player.setVolume(50);
}

Ring::~Ring()
{
    delete ui;
}
void Ring::call(){
    show();
    this->setWindowTitle("попередження");
    ui->label->setText("час вичерпано");

    player.play();
}

//void Ring::close_event(QCloseEvent *event){
//    this->player.stop();
//}

void Ring::on_pushButton_clicked()
{
    player.stop();
    this->close();

}

