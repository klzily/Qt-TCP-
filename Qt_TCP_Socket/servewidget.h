#ifndef SERVEWIDGET_H
#define SERVEWIDGET_H

#include <QWidget>
#include<QTcpServer>//监听套接字
#include<QTcpSocket>//建立连接的通信套接字

namespace Ui {
class ServeWidget;
}

class ServeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ServeWidget(QWidget *parent = 0);
    ~ServeWidget();

private slots:
    void on_ButtonSend_clicked();

    void on_ButtonClose_clicked();

private:
    Ui::ServeWidget *ui;
    QTcpServer *tcpServer;//监听套接字
    QTcpSocket *tcpSocket;//通信套接字
};

#endif // SERVEWIDGET_H
