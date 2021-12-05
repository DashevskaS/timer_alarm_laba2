#ifndef RING_H
#define RING_H

#include <QDialog>
#include <QDir>
#include <QFileDialog>
#include <QMediaPlayer>


namespace Ui {
class Ring;
}

class Ring : public QDialog
{
    Q_OBJECT

public:
    explicit Ring(QWidget *parent = nullptr);
    ~Ring();

    QMediaPlayer player;
    QFileDialog file_dialog;

    void call();
    void close_event(QCloseEvent *event);
private slots:
    void on_pushButton_clicked();

private:
    Ui::Ring *ui;
};

#endif // RING_H
