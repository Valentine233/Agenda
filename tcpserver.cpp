#include "tcpserver.h"

TcpServer::TcpServer(QWidget *parent, QFile *MyEventList) : QDialog(parent)
{
    localFile = MyEventList;
    fileName = localFile->fileName();
    totalBytes = 0;

    //当发现新连接时发出newConnection()信号，弹出对话框
    connect(&tcpServer,SIGNAL(newConnection()),this,SLOT(requestDialog()));
    if(!tcpServer.listen(QHostAddress::LocalHost,6666))
    {
       qDebug() << tcpServer.errorString();
       close();
       return;
    }
}

void TcpServer::requestDialog()
{
    QMessageBox messageBox(this);
    messageBox.setText("收到同步事件请求，是否接受？");
    QAbstractButton *rejectBt = messageBox.addButton(QMessageBox::No);
    QAbstractButton *acceptBt = messageBox.addButton(QMessageBox::Yes);
    messageBox.exec();
    //如果确认接收，开始连接
    connect(acceptBt, SIGNAL(clicked(bool)), this, SLOT(setinit()));
    connect(acceptBt, SIGNAL(clicked(bool)), this, SLOT(acceptConnection()));
    connect(acceptBt, SIGNAL(clicked(bool)), this, SLOT(close()));
}

void TcpServer::setinit()
{
    status->setGeometry(30,70,160,40);
    status->show();
    confirmBt->setText("确认");
    confirmBt->setGeometry(90,160,100,20);
    confirmBt->setEnabled(false);
    confirmBt->show();
    connect(confirmBt,SIGNAL(clicked(bool)),this,SLOT(close()));

}

//void TcpServer::start() //开始监听
//{
//    ui->startButton->setEnabled(false);
//    bytesReceived =0;
//    if(!tcpServer.listen(QHostAddress::LocalHost,6666))
//    {
//       qDebug() << tcpServer.errorString();
//       close();
//       return;
//    }
//    ui->serverStatusLabel->setText(tr("监听"));
//}

void TcpServer::acceptConnection()  //接受连接
{
    tcpServerConnection = tcpServer.nextPendingConnection();
//    connect(tcpServerConnection,SIGNAL(readyRead()),this,SLOT(updateServerProgress()));
    //当有数据发送成功时，我们更新进度
    connect(tcpServerConnection,SIGNAL(bytesWritten(qint64)),this,SLOT(updateServerProgress(qint64)));
    connect(tcpServerConnection,SIGNAL(error(QAbstractSocket::SocketError)),this,
           SLOT(displayError(QAbstractSocket::SocketError)));
    status->setText(tr("接受连接"));
    startTransfer();
    tcpServer.close();
}

void TcpServer::startTransfer()  //实现文件大小等信息的发送
{
    if(!localFile->open(QFile::ReadOnly))
    {
       qDebug() << "open file error!";
       return;
    }

    //文件总大小
    totalBytes = localFile->size();

    QDataStream sendOut(&outBlock,QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_4_6);
    QString currentFileName = fileName.right(fileName.size() - fileName.lastIndexOf('/')-1);

    //依次写入总大小信息空间，文件名大小信息空间，文件名
    sendOut << qint64(0) << qint64(0) << currentFileName;

    //这里的总大小是文件名大小等信息和实际文件大小的总和
    totalBytes += outBlock.size();

    sendOut.device()->seek(0);
    //返回outBolock的开始，用实际的大小信息代替两个qint64(0)空间
    sendOut<<totalBytes<<qint64((outBlock.size() - sizeof(qint64)*2));

    //发送完头数据后剩余数据的大小
    bytesToWrite = totalBytes - tcpServerConnection->write(outBlock);

    status->setText(tr("已连接"));
    outBlock.resize(0);
}

//更新进度，实现文件的传送
void TcpServer::updateServerProgress(qint64 numBytes)
{
    //已经发送数据的大小
    bytesWritten += (int)numBytes;

    if(bytesToWrite > 0) //如果已经发送了数据
    {
   //每次发送loadSize大小的数据，这里设置为4KB，如果剩余的数据不足4KB，
   //就发送剩余数据的大小
       outBlock = localFile->read(qMin(bytesToWrite,loadSize));

       //发送完一次数据后还剩余数据的大小
       bytesToWrite -= (int)tcpServerConnection->write(outBlock);

       //清空发送缓冲区
       outBlock.resize(0);

    } else {
       localFile->close(); //如果没有发送任何数据，则关闭文件
    }

    if(bytesWritten == totalBytes) //发送完毕
    {
     status->setText(tr("传送文件 %1 成功").arg(fileName));
       localFile->close();
       tcpServerConnection->close();
    }
}

//void TcpServer::updateServerProgress()  //更新进度条，接收数据
//{
//   QDataStream in(tcpServerConnection);
//   in.setVersion(QDataStream::Qt_4_6);
//   if(bytesReceived <= sizeof(qint64)*2)
//   { //如果接收到的数据小于16个字节，那么是刚开始接收数据，我们保存到//来的头文件信息
//       if((tcpServerConnection->bytesAvailable() >= sizeof(qint64)*2)
//           && (fileNameSize == 0))
//       { //接收数据总大小信息和文件名大小信息
//           in >> totalBytes >> fileNameSize;
//           bytesReceived += sizeof(qint64) * 2;
//       }
//       if((tcpServerConnection->bytesAvailable() >= fileNameSize)
//           && (fileNameSize != 0))
//       {  //接收文件名，并建立文件
//           in >> fileName;
//           ui->serverStatusLabel->setText(tr("接收文件 %1 ...")
//                                           .arg(fileName));
//           bytesReceived += fileNameSize;
//           localFile= new QFile(fileName);
//           if(!localFile->open(QFile::WriteOnly))
//           {
//                qDebug() << "open file error!";
//                return;
//           }
//       }
//       else return;
//   }
//   if(bytesReceived < totalBytes)
//   {  //如果接收的数据小于总数据，那么写入文件
//      bytesReceived += tcpServerConnection->bytesAvailable();
//      inBlock= tcpServerConnection->readAll();
//      localFile->write(inBlock);
//      inBlock.resize(0);
//   }

//   if(bytesReceived == totalBytes)
//   { //接收数据完成时
//    tcpServerConnection->close();
//    localFile->close();
//    ui->startButton->setEnabled(true);
//ui->serverStatusLabel->setText(tr("接收文件 %1 成功！")
//.arg(fileName));
//   }
//}

void TcpServer::displayError(QAbstractSocket::SocketError) //错误处理
{
    qDebug() << tcpServerConnection->errorString();
    tcpServerConnection->close();
    status->setText(tr("发送错误"));
}
