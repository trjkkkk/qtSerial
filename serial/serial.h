#ifndef SERIAL_H
#define SERIAL_H

#include <QMainWindow>

/*-----------user-----------*/
//port
#include <QSerialPort>
//debug
#include <QtDebug>
/*--------------------------*/
namespace Ui {
class Serial;
}

class Serial : public QMainWindow
{
    Q_OBJECT

public:
    explicit Serial(QWidget *parent = 0);
    ~Serial();

private slots:

    //button
    void btn_open_port(bool);
    void btn_close_port(bool);
    void btn_send_data(bool);

    //receive data
    void receive_data();


private:
    Ui::Serial *ui;

    /*-----------function---------------*/
    void system_init();
    /*-----------variable-------------*/
    QSerialPort globle_port;
};

#endif // SERIAL_H
