#include "alarmw.h"
#include "ui_alarmw.h"
#include <QTimer>
#include <QColor>
#include <QDate>

AlarmW::AlarmW(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlarmW)
{
    ui->setupUi(this);
    this->setStyleSheet("color: black; background-color: #E9E9E9;");
    this->setWindowTitle("будильник");
    QTimer *timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(output_list_of_alarms()));
    connect(ui->filtr_box, SIGNAL(currentIndexChanged(int)), this, SLOT(changed_current_row_filtrbox(int)));
    timer->start(10);
    QStringList strList;
    strList<<"понеділок"<<"вівторок"<<"середа"<<"четвер"<<"п'ятниця"<<"субота"<<"неділя";
    ui->weekday->addItems(strList);
    QListWidgetItem* Item;
    for(int i = 0; i < 7;i++){
        Item = ui->weekday->item(i);
        Item->setFlags(Item->flags() |Qt::ItemIsUserCheckable);
        Item->setCheckState(Qt::Unchecked);
    }
    connect(ui->list_of_alarms, SIGNAL(itemSelectionChanged()), this, SLOT(output_list_of_weekday()));
    connect(ui->weekday, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(changed_weekday(QListWidgetItem*)));

}

AlarmW::~AlarmW()
{
    delete ui;
}

void AlarmW::on_add_new_alarm_clicked()
{
    Element_Alarm *elementAlarm = new Element_Alarm;
    elementAlarm->show();
    connect(elementAlarm, SIGNAL(return_element_alarm(Element_Alarm*)), this, SLOT(push_alarm(Element_Alarm*)));
}
void AlarmW::push_alarm(Element_Alarm *element){
    alarms.push_back(element);
}

QString AlarmW::time_to(QDateTime time){
    int sec = QDateTime::currentDateTime().secsTo(time);

    QTime tmpl;
    tmpl.setHMS(0, 0, 0);
    tmpl = tmpl.addSecs(sec%86400);
    return QString::number(sec/86400)+':'+tmpl.toString("hh:mm:ss");
}
QString for_write(Element_Alarm *element, int i){
    QString s = QString::number(i+1)+") ";
    s = s + element->name;
    s = s + element->time.toString(" h:mm ");
    QDateTime mom;
    mom.setTime(element->time);
    QDate date = QDate::currentDate();
    if(!element->isTurn)
        return s;
    bool tmp = false;
    for(int i = 0; i < 7;i++){
        if(element->WeekDay[i])
            tmp = true;
    }
    if(tmp){
        //for today

        if(element->WeekDay[date.dayOfWeek()-1]){
            if(QTime::currentTime() < mom.time()){
                mom.setDate(date);
                s = s + AlarmW::time_to(mom);
                return s;
            }
        }
        //for another day
        {
            date = date.addDays(1); //add date
            while(!element->WeekDay[date.dayOfWeek()-1]){
                date = date.addDays(1);
            }
            qDebug() << date;
            mom.setDate(date);
            s = s + AlarmW::time_to(mom);
            return s;
        }
    }else{
        if(QTime::currentTime() < mom.time()){
            mom.setDate(date);
            s = s + AlarmW::time_to(mom);
        }else{
            mom.setDate(date.addDays(1));
            s = s + AlarmW::time_to(mom);
            return s;
        }
    }
    s = s + AlarmW::time_to(mom);
    return s;
}
void AlarmW::changed_weekday(QListWidgetItem* Item){
    if(flag) return;
    QStringList strList;
    strList<<"понеділок"<<"вівторок"<<"середа"<<"четвер"<<"п'ятниця"<<"субота"<<"неділя";
    for(int i = 0;i < 7;i++){
        if(Item->text() == strList[i]){
            alarms[ui->list_of_alarms->currentRow()]->WeekDay[i] =!alarms[ui->list_of_alarms->currentRow()]->WeekDay[i];
            output_list_of_weekday();
            return;
        }
    }
}

void AlarmW::check_alarm(){
    int size_list = alarms.size();
    for(int i = 0;i < size_list;i++){
        if(alarms[i]->isTurn){
            if(alarms[i]->WeekDay[QDate::currentDate().dayOfWeek()-1] &&
                    alarms[i]->time.hour() == QTime::currentTime().hour() &&
                    alarms[i]->time.minute() == QTime::currentTime().minute()){
                emit alarm_ring();
                alarms[i]->isTurn = false;
            }
        }
    }
}

void AlarmW::on_on_off_alarm_clicked()
{
    if(alarms[ui->list_of_alarms->currentRow()]->isTurn)
        alarms[ui->list_of_alarms->currentRow()]->isTurn = false;
    else
        alarms[ui->list_of_alarms->currentRow()]->isTurn = true;
}

void AlarmW::output_list_of_alarms(){
    int current_row = ui->list_of_alarms->currentRow();
    ui->list_of_alarms->clear();
    int size_list = alarms.size();
    switch (ui->filtr_box->currentIndex()){
    case 0://All
    {
        if(Complement) break;
        for(int i = 0; i < size_list;i++){
            ui->list_of_alarms->addItem(for_write(alarms[i], i));
            if(!alarms[i]->isTurn)
                ui->list_of_alarms->item(i)->setForeground(Qt::red);
        }
        break;
    }
    case 1:
    {
        int count = 0;
        for(int i = 0; i < size_list;i++){
            if(!(alarms[i]->isTurn^Complement))
                continue;
            ui->list_of_alarms->addItem(for_write(alarms[i], i));
            if(!alarms[i]->isTurn)
                ui->list_of_alarms->item(count)->setForeground(Qt::red);
            count++;
        }
        break;
    }
    }
    ui->list_of_alarms->setCurrentRow(current_row);
    check_alarm();
    output_correct_abutton_name();
}
void AlarmW::on_delete_alarm_clicked()
{
    alarms.erase(alarms.begin() + ui->list_of_alarms->currentRow());
}

void AlarmW::output_list_of_weekday(){
    flag = true;
    int current_row = -1;
    current_row = ui->list_of_alarms->currentRow();
    if(current_row == -1) return;
    for(int i = 0;i < 7;i++){
        if(alarms[current_row]->WeekDay[i])
            ui->weekday->item(i)->setCheckState(Qt::Checked);
        else
            ui->weekday->item(i)->setCheckState(Qt::Unchecked);
    }
    flag = false;
}

void AlarmW::output_correct_abutton_name(){
    int current_row = -1;
    current_row = ui->list_of_alarms->currentRow();
    //button om|off
    {
        if(current_row == -1){
            ui->on_off_alarm->setHidden(true);
        }else{
            ui->on_off_alarm->setHidden(false);
            if(alarms[current_row]->isTurn)
                ui->on_off_alarm->setText("выключить");
            else
                ui->on_off_alarm->setText("включить");
        }
    }
    //button delete
    {
        if(current_row == -1)
            ui->delete_alarm->setHidden(true);
        else
            ui->delete_alarm->setHidden(false);
    }
    //list
    {
        if(current_row == -1)
            ui->weekday->setHidden(true);
        else
            ui->weekday->setHidden(false);
    }

}
void AlarmW::changed_current_row_filtrbox(int current){
    switch (current) {
    case 0:
    {
        ui->Edit_for_subname->setHidden(true);
        break;
    }   case 1:
        ui->Edit_for_subname->setHidden(true);
        break;

    }
}
