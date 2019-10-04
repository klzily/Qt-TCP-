#include "servewidget.h"
#include "ui_servewidget.h"

ServeWidget::ServeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServeWidget)
{
    ui->setupUi(this);
    //初始化套接字
    tcpServer = NULL;
    tcpSocket = NULL;
    //监听套接字，指定父对象自动回收空间
    tcpServer = new QTcpServer(this);
    //设定端口
    tcpServer->listen(QHostAddress::Any,8888);
    //新连接建立的信号槽
    connect(tcpServer,&QTcpServer::newConnection,[=]()
    {
    //取出建立好连接的套接字
        tcpSocket = tcpServer->nextPendingConnection();
    //获取对方的IP和端口
    QString ip = tcpSocket->peerAddress().toString();
    qint16 port = tcpSocket->peerPort();
    //将信息显示到UI
    QString temp = QString("[%1:%2]:成功连接").arg(ip).arg(port);
    ui->textEditRead->setText(temp);
    //连接建立后，读取到数据的信号槽
    connect(tcpSocket,&QTcpSocket::readyRead,
            [=]()
            {
             //从通信套接字取出内容
             QByteArray array = tcpSocket->readAll();
             //显示到UI
             ui->textEditRead->append(array);
            } );
    });
    setWindowTitle("TCP服务器，端口:8888");
}

ServeWidget::~ServeWidget()
{
    delete ui;
}

void ServeWidget::on_ButtonSend_clicked()
{   if(NULL == tcpSocket)
    {return;}
    //获取编辑区内容
    QString str = ui->textEditWrite->toPlainText();
    //给对方发数据,使用的套接字为tcpSocket
    tcpSocket->write( str.toUtf8().data() );
}

void ServeWidget::on_ButtonClose_clicked()
{   if(NULL == tcpSocket)
    {return;}
    //主动和客户端断开连接
    tcpSocket->disconnectFromHost();
    //关闭套接字
    tcpSocket->close();
    tcpSocket = NULL;

}
