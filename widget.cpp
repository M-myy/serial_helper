#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    QStringList serial_port_names;
    QStringList baud_rate = {"300","600","1200","2400", "4800", "9600", "19200" ,"38400", "43000" ,"56000" ,"57600" ,"115200"};

    ui->setupUi(this);
    this->setWindowTitle("Serial LED");

    serial_port = new QSerialPort(this);

    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        serial_port_names << info.portName();
    }

    ui->serial_cb->addItems(serial_port_names);
    ui->baud_cb->addItems(baud_rate);
    bind();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::bind(void)
{
    QObject::connect(ui->switch_btn_open,SIGNAL(clicked()),this,SLOT(btn_open_handle()));
    QObject::connect(ui->switch_btn_close,SIGNAL(clicked()),this,SLOT(btn_close_handle()));
    QObject::connect(ui->cmd_btn_cmd1,SIGNAL(clicked()),this,SLOT(btn_cmd1_handle()));
    QObject::connect(ui->cmd_btn_cmd2,SIGNAL(clicked()),this,SLOT(btn_cmd2_handle()));
}

void Widget::btn_open_handle(void)
{
    QString port_name;
    port_name = ui->serial_cb->currentText();

    if(port_name.isEmpty())
    {
        qDebug() << "没有可用的串口！" << Qt::endl;
        QMessageBox::critical(this, "提示", "串口打开失败,没有可用的串口！");
        return;
    }

    // 配置串口
    serial_port->setPortName(port_name);
    serial_port->setBaudRate(ui->baud_cb->currentText().toInt());
    serial_port->setDataBits(QSerialPort::Data8);
    serial_port->setStopBits(QSerialPort::OneStop);
    serial_port->setParity(QSerialPort::NoParity);

    qDebug() << "串口" << port_name << "已经打开" << Qt::endl;
}

// 关闭串口
void Widget::btn_close_handle(void)
{
    serial_port->close();
    qDebug() << "串口" << serial_port->portName() << "已经关闭" << Qt::endl;
}

void Widget::btn_cmd1_handle(void)
{
    serial_port->write("cmd1\n");
    qDebug("cmd1\n");
}

void Widget::btn_cmd2_handle(void)
{
    serial_port->write("cmd2\n");
    qDebug("cmd2\n");
}
