#include "element_alarm.h"
#include "ui_element_alarm.h"

static int current_index_alarm = 1;

Element_Alarm::Element_Alarm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Element_Alarm)
{
    ui->setupUi(this);
    this->setWindowTitle("будильник");
    this->setStyleSheet("color: black; background-color: #E9E9E9;");
    ui->timeEdit->setTime(QTime::currentTime());
    ui->NameEdit->setMaxLength(8);
    QStringList strList;
    strList<<"понеділок"<<"вівторок"<<"середа"<<"четвер"<<"п'ятниця"<<"субота"<<"неділя";
    ui->WeekDay->addItems(strList);
    QListWidgetItem* Item;
    for(int i = 0; i < 7;i++){
        Item = ui->WeekDay->item(i);
        Item->setFlags(Item->flags() |Qt::ItemIsUserCheckable);
        Item->setCheckState(Qt::Unchecked);
    }
}

Element_Alarm::~Element_Alarm()
{
    delete ui;
}

void Element_Alarm::on_set_time_alarm_clicked()
{

    time = ui->timeEdit->time();
    time.setHMS(time.hour(), time.minute(), 0);
    this->close();
    isTurn = true;
    if(ui->NameEdit->text().isEmpty()){
        name = "будильник:" + QString::number(current_index_alarm);
    }else{
        name = ui->NameEdit->text();
    }
    current_index_alarm++;
    for(int i = 0;i < 7;i++){
        WeekDay[i] = ui->WeekDay->item(i)->checkState();
    }
    emit return_element_alarm(this);
}

