#ifndef ALARMW_H
#define ALARMW_H

#include <QDialog>
#include <element_alarm.h>

namespace Ui {
class AlarmW;
}

class AlarmW : public QDialog
{
    Q_OBJECT

public:
    explicit AlarmW(QWidget *parent = nullptr);
    ~AlarmW();
    static QString time_to(QDateTime time);
signals:
    void alarm_ring();


private slots:
    void on_add_new_alarm_clicked();
    void push_alarm(Element_Alarm *element);
    void changed_weekday(QListWidgetItem* Item);
    void check_alarm();

    void on_on_off_alarm_clicked();
    void output_list_of_alarms();
    void on_delete_alarm_clicked();
    void output_list_of_weekday();
    void output_correct_abutton_name();
    void changed_current_row_filtrbox(int current);

private:
    Ui::AlarmW *ui;
    QVector<Element_Alarm*> alarms;
    bool Complement = false;
    bool flag = false;
};

#endif // ALARMW_H
