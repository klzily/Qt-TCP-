#include "clientwidget.h"
#include "ui_clientwidget.h"
#include<QHostAddress>
#include <QDebug>
ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);
    //初始化套接字
    tcpSocket = NULL;
    //分配空间，指定父对象
    tcpSocket = new QTcpSocket(this);
    //建立连接的信号槽
    connect(tcpSocket,&QTcpSocket::connected,
            [=]()
            {
                 ui->textEditRead->setText("恭喜，成功连接服务器！");
            }
            );
    //连接建立后收到服务器数据的信号槽
    connect(tcpSocket,&QTcpSocket::readyRead,
            [=]()
           {
         //获取对方发送的内容
        QByteArray array = tcpSocket->readAll();
        //显示到编辑框
        ui->textEditRead->append(array);//append，添加内容
            }
            );
    //设置窗口标题
    setWindowTitle("TCP客户端");
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_buttonConnect_clicked()
{
    //获取服务器IP和端口
    QString ip = ui->lineEditIP->text();
    qint16 port = ui->lineEditPort->text().toInt();
    //主动连接服务器
    tcpSocket->connectToHost(QHostAddress(ip),port);
}

void ClientWidget::on_buttonSend_clicked()
{
    //获取编辑框内容
     QString str = ui->textEditWrite->toPlainText();
     //发送数据
     tcpSocket->write( str.toUtf8().data() );

}

void ClientWidget::on_buttonClose_clicked()
{ //主动断开连接
    tcpSocket->disconnectFromHost();
}
