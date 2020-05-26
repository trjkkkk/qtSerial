#include "serial.h"
#include "ui_serial.h"

Serial::Serial(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Serial)
{
    ui->setupUi(this);
    //user
    system_init();
}

Serial::~Serial()
{
    delete ui;
}

/*----------------------------------------
 *functions
 * ---------------------------------------*/
void Serial::system_init()
{
        globle_port.setParity(QSerialPort::NoParity);
        globle_port.setDataBits(QSerialPort::Data8);
        globle_port.setStopBits(QSerialPort::OneStop);


        //connect
        connect(ui->btn_open,&QPushButton::clicked,this,&Serial::btn_open_port);
        connect(ui->btn_close,&QPushButton::clicked,this,&Serial::btn_close_port);
        connect(ui->btn_send,&QPushButton::clicked,this,&Serial::btn_send_data);
        connect(&globle_port,&QSerialPort::readyRead,this,&receive_data);
}

/*----------------------------------------
 *slots
 * ---------------------------------------*/

void Serial::btn_open_port(bool)
{

    /*----------port name---------------*/
    //qDebug()<<"调用成功";
    qDebug()<<ui->cmb_port_name->currentIndex();
    switch (ui->cmb_port_name->currentIndex()) {
    case 0:
            globle_port.setPortName("COM1");
        break;
    case 1:
            globle_port.setPortName("COM2");
        break;
    case 2:
            globle_port.setPortName("COM3");
        break;
    case 3:
            globle_port.setPortName("COM4");
        break;
    case 4:
            globle_port.setPortName("COM5");
        break;
    case 5:
            globle_port.setPortName("COM6");
        break;
    case 6:
            globle_port.setPortName("COM7");
        break;

    default:
            globle_port.setPortName("COM8");
        break;
    }

    /*-----------------baud rate--------------------*/

    switch (ui->cmb_baud_rate->currentIndex()) {
    case 0:
        globle_port.setBaudRate(QSerialPort::Baud115200);
        break;
    case 1:
        globle_port.setBaudRate(QSerialPort::Baud57600);
        break;
    case 2:
        globle_port.setBaudRate(QSerialPort::Baud38400);
        break;
    case 3:
        globle_port.setBaudRate(QSerialPort::Baud19200);
        break;
    case 4:
        globle_port.setBaudRate(QSerialPort::Baud9600);
        break;
    case 5:
        globle_port.setBaudRate(QSerialPort::Baud4800);
        break;
    case 6:
        globle_port.setBaudRate(QSerialPort::Baud2400);
        break;
    default:
        globle_port.setBaudRate(QSerialPort::Baud1200);
        break;
    }
    //open
    globle_port.open(QIODevice::ReadWrite);
    //test
    globle_port.write("1");

    ui->lab_status->setText("Connected");

}

void Serial::btn_close_port(bool)
{
    globle_port.close();
    ui->lab_status->setText("Disconnected");
}

/*-------------sending data-----------------*/

void Serial::btn_send_data(bool)
{
    QString data=ui->line_send_data->text();
    QByteArray array=data.toLatin1();
    globle_port.write(array);

}

/*--------------receive data---------------*/

void Serial::receive_data()
{
    QByteArray array = globle_port.readAll();
    qDebug()<<array;
    if(ui->checkBox->checkState()==Qt::Checked)
    {
        ui->plainTextEdit->insertPlainText(QString(array.toHex(' ').toUpper().append(' ')));
    }else
    {
        ui->plainTextEdit->insertPlainText(QString(array));
    }
    //ui->plainTextEdit->insertPlainText(QString(array));

}
