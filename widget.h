#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget(); 
    void bind(void);    // 信号绑定

// 自定义槽函数
private slots:
    void btn_open_handle(void);
    void btn_close_handle(void);
    void btn_cmd1_handle(void);
    void btn_cmd2_handle(void);

private:
    Ui::Widget *ui;
    QSerialPort *serial_port;
};
#endif // WIDGET_H
