#ifndef ELEMENT_ALARM_H
#define ELEMENT_ALARM_H

#include <QDialog>
#include <QDateTime>
#include <QDebug>
#include <QListWidgetItem>

namespace Ui {
class Element_Alarm;
}

class Element_Alarm : public QDialog
{
    Q_OBJECT

public:
    explicit Element_Alarm(QWidget *parent = nullptr);
    ~Element_Alarm();
    QString name;
    QTime time;
    bool isTurn = false;
    bool WeekDay[7] = {};
signals:
    void return_element_alarm(Element_Alarm *element);
private slots:

    void on_set_time_alarm_clicked();

private:
    Ui::Element_Alarm *ui;
};

#endif // ELEMENT_ALARM_H
