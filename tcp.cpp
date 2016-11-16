#include "tcp.h"

Tcp::Tcp(QWidget *parent, QFile *MyEventList, QFile *YourEventList) : QDialog(parent)
{
    sdFile = MyEventList;
    sdFileName = MyEventList->fileName();
    rcFile = YourEventList;
    rcFileName = YourEventList->fileName();
    sdLoadSize = 4*1024;
    sdTotalBytes = 0;
    sdBytesWritten = 0;
    sdBytesToWrite = 0;
    rcTotalBytes = 0;
    rcBytesReceived = 0;
    rcFileNameSize = 0;
    tcpSocket = new QTcpSocket(this);
    setWindowTitle("Update");

    //当发现新连接时发出newConnection()信号，弹出对话框
    connect(&tcpServer,SIGNAL(newConnection()),this,SLOT(requestDialog()));
    connect(&tcpServer,SIGNAL(newConnection()),this,SLOT(startTransfer()));
    //当连接服务器成功时，发出connected()信号，我们开始传送文件
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(startTransfer()));
    connect(tcpSocket,SIGNAL(connected()), this, SLOT(acceptConnection()));

    //当有数据发送成功时，我们更新进度
    connect(tcpSocket,SIGNAL(bytesWritten(qint64)),this,SLOT(updateClientProgress(qint64)));
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));

    //始终监听，监听地址为本机
    if(!tcpServer.listen(QHostAddress::LocalHost,6666))
    {
       qDebug() << tcpServer.errorString();
       close();
       return;
    }
}

void Tcp::requestDialog()
{
    QMessageBox messageBox(this);
    messageBox.setText("收到同步事件请求，是否接受？");
    QAbstractButton *rejectBt = messageBox.addButton(QMessageBox::No);
    QAbstractButton *acceptBt = messageBox.addButton(QMessageBox::Yes);
    messageBox.exec();
    //如果确认接收，开始连接
    connect(acceptBt, SIGNAL(clicked(bool)), this, SLOT(receiverSetinit()));
    connect(acceptBt, SIGNAL(clicked(bool)), this, SLOT(acceptConnection()));
    connect(acceptBt, SIGNAL(clicked(bool)), this, SLOT(close()));
}

void Tcp::senderSetinit()
{
    sdFile->close();
    rcFile->close();
    QLabel *host = new QLabel(this);
    QLabel *port = new QLabel(this);
    host->setText("主机：");
    host->setGeometry(30,30,30,40);
    host->show();
    port->setText("端口：");
    port->setGeometry(30,70,30,40);
    port->show();
    confirmBt->hide();
    hostEdit->setGeometry(70,40,120,20);
    portEdit->setGeometry(70,80,120,20);
    status->setText("请输入主机地址和端口号！");
    status->setGeometry(30,110,160,40);
    syncBt->setText("同步");
    syncBt->setStyleSheet("QPushButton {color: black;}");
    syncBt->setGeometry(90,160,100,20);
    connect(syncBt,SIGNAL(clicked(bool)),this,SLOT(send()));
}

void Tcp::receiverSetinit()
{
    sdFile->close();
    rcFile->close();
    hostEdit->hide();
    portEdit->hide();
    syncBt->hide();
    status->setGeometry(30,70,160,40);
    confirmBt->setText("确认");
    confirmBt->setGeometry(90,160,100,20);
    confirmBt->show();
    confirmBt->setEnabled(false);
    connect(confirmBt,SIGNAL(clicked(bool)),this,SLOT(close()));
}

void Tcp::send()   //连接到服务器，执行发送
{
    syncBt->setEnabled(false);
    status->setText(tr("连接中..."));
    tcpSocket->connectToHost(hostEdit->text(),portEdit->text().toInt());//连接
}

void Tcp::startTransfer()  //实现文件大小等信息的发送
{
    if(!sdFile->open(QFile::ReadOnly))
    {
       qDebug() << "Tcp::startTransfer():open file error!";
       qDebug() <<sdFile->fileName();
       qDebug() << sdFile->errorString();
       return;
    }

    //文件总大小
    sdTotalBytes = sdFile->size();

    QDataStream sendOut(&outBlock,QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_4_6);
    QString currentFileName = sdFileName.right(sdFileName.size() - sdFileName.lastIndexOf('/')-1);

    //依次写入总大小信息空间，文件名大小信息空间，文件名
    sendOut << qint64(0) << qint64(0) << currentFileName;

    //这里的总大小是文件名大小等信息和实际文件大小的总和
    sdTotalBytes += outBlock.size();

    sendOut.device()->seek(0);
    //返回outBolock的开始，用实际的大小信息代替两个qint64(0)空间
    sendOut<<sdTotalBytes<<qint64((outBlock.size() - sizeof(qint64)*2));

    //发送完头数据后剩余数据的大小
    sdBytesToWrite = sdTotalBytes - tcpSocket->write(outBlock);

    status->setText(tr("已连接"));
    outBlock.resize(0);
}

//更新进度，实现文件的传送
void Tcp::updateClientProgress(qint64 numBytes)
{
    //已经发送数据的大小
    sdBytesWritten += (int)numBytes;

    if(sdBytesToWrite > 0) //如果已经发送了数据
    {
   //每次发送loadSize大小的数据，这里设置为4KB，如果剩余的数据不足4KB，
   //就发送剩余数据的大小
       outBlock = sdFile->read(qMin(sdBytesToWrite,sdLoadSize));

       //发送完一次数据后还剩余数据的大小
       sdBytesToWrite -= (int)tcpSocket->write(outBlock);

       //清空发送缓冲区
       outBlock.resize(0);

    } else {
       sdFile->close(); //如果没有发送任何数据，则关闭文件
    }

    if(sdBytesWritten == sdTotalBytes) //发送完毕
    {
       status->setText(tr("传送文件 %1 成功").arg(sdFileName));
       sdFile->close();
       tcpSocket->close();
    }
}

void Tcp::acceptConnection()  //接受连接
{
    tcpSocket = tcpServer.nextPendingConnection();
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(updateServerProgress()));
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(displayError(QAbstractSocket::SocketError)));
    status->setText(tr("接受连接"));
    tcpServer.close();
}

void Tcp::updateServerProgress()  //接收数据
{
   QDataStream in(tcpSocket);
   in.setVersion(QDataStream::Qt_4_6);
   if(rcBytesReceived <= sizeof(qint64)*2)
   { //如果接收到的数据小于16个字节，那么是刚开始接收数据，我们保存到//来的头文件信息
       if((tcpSocket->bytesAvailable() >= sizeof(qint64)*2)
           && (rcFileNameSize == 0))
       { //接收数据总大小信息和文件名大小信息
           in >> rcTotalBytes >> rcFileNameSize;
           rcBytesReceived += sizeof(qint64) * 2;
       }
       if((tcpSocket->bytesAvailable() >= rcFileNameSize)
           && (rcFileNameSize != 0))
       {  //接收文件名，并建立文件
           in >> rcFileName;
           status->setText(tr("接收文件 %1 ...").arg(rcFileName));
           rcBytesReceived += rcFileNameSize;
           rcFile= new QFile(rcFileName);
           if(!rcFile->open(QFile::WriteOnly))
           {
                qDebug() << "Tcp::updateServerProgress():open file error!";
                return;
           }
       }
       else return;
   }
   if(rcBytesReceived < rcTotalBytes)
   {
       //如果接收的数据小于总数据，那么写入文件
       rcBytesReceived += tcpSocket->bytesAvailable();
       inBlock= tcpSocket->readAll();
       rcFile->write(inBlock);
       inBlock.resize(0);
   }

   if(rcBytesReceived == rcTotalBytes)
   {
       //接收数据完成时
       tcpSocket->close();
       rcFile->close();
       confirmBt->setEnabled(true);
       status->setText(tr("接收文件 %1 成功！").arg(rcFileName));
   }
}

void Tcp::displayError(QAbstractSocket::SocketError) //显示错误
{
    qDebug() << tcpSocket->errorString();
    tcpSocket->close();
    status->setText(tr("发生错误。。请重新输入"));
    confirmBt->setEnabled(true);
    syncBt->setEnabled(true);
}

