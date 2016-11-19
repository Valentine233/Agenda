#include "tcpclient.h"

TcpClient::TcpClient(QWidget *parent, QFile *YourEventList) : QDialog(parent)
{
    localFile = YourEventList;
    fileName = localFile->fileName();
    totalBytes = 0;
    bytesReceived = 0;
    fileNameSize = 0;

    tcpClient = new QTcpSocket(this);
    //当发现新连接时发出newConnection()信号
    connect(tcpClient,SIGNAL(connected()),this,SLOT(acceptfile()));
    connect(tcpClient,SIGNAL(error(QAbstractSocket::SocketError)),this,
           SLOT(displayError(QAbstractSocket::SocketError)));

    setWindowTitle("Update");
    setinit();

    //当连接服务器成功时，发出connected()信号，我们开始传送文件
//    connect(tcpClient,SIGNAL(connected()),this,SLOT(startTransfer()));

}

void TcpClient::setinit()
{
    QLabel *host = new QLabel(this);
    QLabel *port = new QLabel(this);
    host->setText("主机：");
    host->setGeometry(30,30,30,40);
//    host->show();
    port->setText("端口：");
    port->setGeometry(30,70,30,40);
//    port->show();
    hostEdit->setGeometry(70,40,120,20);
    portEdit->setGeometry(70,80,120,20);
    status->setText("请输入主机地址和端口号！");
    status->setGeometry(30,110,160,40);
    syncBt->setText("更新");
    syncBt->setStyleSheet("QPushButton {color: black;}");
    syncBt->setGeometry(90,160,100,20);
    connect(syncBt,SIGNAL(clicked(bool)),this,SLOT(send()));
}

void TcpClient::send()   //连接到服务器，执行发送
{
    syncBt->setEnabled(false);
    status->setText(tr("连接中..."));
    tcpClient->connectToHost(hostEdit->text(),
                             portEdit->text().toInt());//连接
}

void TcpClient::acceptfile()  //对方已接受连接
{
    connect(tcpClient,SIGNAL(readyRead()),this,SLOT(updateClientProgress()));
    connect(tcpClient,SIGNAL(error(QAbstractSocket::SocketError)),this,
           SLOT(displayError(QAbstractSocket::SocketError)));
}

void TcpClient::updateClientProgress()  //更新进度条，接收数据
{
   QDataStream in(tcpClient);
   in.setVersion(QDataStream::Qt_4_6);
   if(bytesReceived <= sizeof(qint64)*2)
   { //如果接收到的数据小于16个字节，那么是刚开始接收数据，我们保存到//来的头文件信息
       if((tcpClient->bytesAvailable() >= sizeof(qint64)*2)
           && (fileNameSize == 0))
       { //接收数据总大小信息和文件名大小信息
           in >> totalBytes >> fileNameSize;
           bytesReceived += sizeof(qint64) * 2;
       }
       if((tcpClient->bytesAvailable() >= fileNameSize)
           && (fileNameSize != 0))
       {  //接收文件名，并建立文件
           in >> fileName;
           status->setText(tr("接收文件 %1 ...").arg(fileName));
           bytesReceived += fileNameSize;
           if(!localFile->open(QFile::WriteOnly))
           {
                qDebug() << "open file error!";
                return;
           }
       }
       else return;
   }
   if(bytesReceived < totalBytes)
   {  //如果接收的数据小于总数据，那么写入文件
      bytesReceived += tcpClient->bytesAvailable();
      inBlock= tcpClient->readAll();
      localFile->write(inBlock);
      inBlock.resize(0);
   }

   if(bytesReceived == totalBytes)
   { //接收数据完成时
    tcpClient->close();
    localFile->close();
    syncBt->setEnabled(true);
    status->setText(tr("接收文件 %1 成功！").arg(fileName));
   }
}

void TcpClient::displayError(QAbstractSocket::SocketError) //显示错误
{
    qDebug() << tcpClient->errorString();
    tcpClient->close();
    status->setText(tr("发送错误"));
    syncBt->setEnabled(true);
}
