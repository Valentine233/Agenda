#include "tcpserver.h"

TcpServer::TcpServer(QWidget *parent) : QDialog(parent)
{
    if (!QDir(QStandardPaths::writableLocation(QStandardPaths::DataLocation)).exists())
        QDir().mkdir(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
    localFile->setFileName(QStandardPaths::writableLocation(QStandardPaths::DataLocation) +"/MyEventList.txt");
    fileName = localFile->fileName();
    totalBytes = 0;
    setWindowTitle("Update Request");

    //当发现新连接时发出newConnection()信号，弹出询问对话框
    connect(&tcpServer,SIGNAL(newConnection()),this,SLOT(requestDialog()));
    QHostAddress add;
    tcpServer.listen(add,6666);

}

void TcpServer::requestDialog()
{
    QMessageBox messageBox(this);
    messageBox.setText("收到同步事件请求，是否接受？");
    QAbstractButton *rejectBt = messageBox.addButton(QMessageBox::No);
    QAbstractButton *acceptBt = messageBox.addButton(QMessageBox::Yes);
    messageBox.exec();
    //如果确认接收，开始连接
    if (messageBox.clickedButton() == acceptBt) {
        writeToFile();
        setinit();
        acceptConnection();
    }
    if (messageBox.clickedButton() == rejectBt) {
        this->close();
    }
}

void TcpServer::setinit()
{
    status->setGeometry(30,70,160,40);
    status->show();
    confirmBt->setText("确认");
    confirmBt->setGeometry(90,160,100,20);
    confirmBt->setEnabled(false);
    confirmBt->setStyleSheet("QPushButton {color: black;}");
    confirmBt->show();
    connect(confirmBt,SIGNAL(clicked(bool)),this,SLOT(close()));
    this->show();
}

void TcpServer::acceptConnection()  //接受连接
{
    tcpServerConnection = tcpServer.nextPendingConnection();
    //当有数据发送成功时，更新进度
    connect(tcpServerConnection,SIGNAL(bytesWritten(qint64)),this,SLOT(updateServerProgress(qint64)));
    connect(tcpServerConnection,SIGNAL(error(QAbstractSocket::SocketError)),this,
           SLOT(displayError(QAbstractSocket::SocketError)));
    status->setText(tr("对方接受连接"));
    startTransfer();
    tcpServer.close();
}

void TcpServer::startTransfer()  //实现文件大小等信息的发送
{
    if(!localFile->open(QFile::ReadOnly))
    {
       qDebug() << "TcpServer::startTransfer()" << localFile->errorString();
       return;
    }

    //文件总大小
    totalBytes = localFile->size();

    QDataStream sendOut(&outBlock,QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_5_7);
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

    if(bytesToWrite > 0) { //如果有待发送的数据
       //发送所有数据
       outBlock = localFile->readAll();
       //发送完一次数据后还剩余数据的大小
       bytesToWrite -= (int)tcpServerConnection->write(outBlock);
       //清空发送缓冲区
       outBlock.resize(0);
    }
    else {
       localFile->close(); //如果没有发送任何数据，则关闭文件
    }

    if(bytesWritten == totalBytes) //发送完毕
    {
       status->setText(tr("传送文件成功"));
       localFile->close();
       tcpServerConnection->close();
       confirmBt->setEnabled(true);
       //重新监听连接请求
       QHostAddress add;
       tcpServer.listen(add,6666);
       tcpServerConnection = new QTcpSocket;
    }
}

void TcpServer::displayError(QAbstractSocket::SocketError) //错误处理
{
    qDebug() << tcpServerConnection->errorString();
    tcpServerConnection->close();
    status->setText(tr("就绪"));
    confirmBt->setEnabled(true);
}

void TcpServer::writeToFile() //从数据库写入MyEventList文件中，再发送给对方
{
    if (!localFile->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<<"WriteError: Can't open the file!\n";
        return;
    }
    QTextStream out(localFile);
    QSqlQuery query =  ((MainWindow*)parent())->db->readAllMyEvent();
    QSqlRecord record = query.record();
    int idName = record.indexOf("name");
    int idPlace = record.indexOf("place");
    int idStart = record.indexOf("starttime");
    int idEnd = record.indexOf("endtime");
    int idType = record.indexOf("type");
    while (query.next())
    {
       QString name = query.value(idName).toString();
       QString place = query.value(idPlace).toString();
       QDateTime starttime = QDateTime::fromString(query.value(idStart).toString());
       QDateTime endtime = QDateTime::fromString(query.value(idEnd).toString());
       int type = query.value(idType).toString().toInt();
       QString start = starttime.toString("yyyy/MM/dd HH:mm");
       QString end = endtime.toString("yyyy/MM/dd HH:mm");
       out<<name<<",;"<<place<<",;"<<start<<",;"<<end<<",;"<<type<<"\n";
    }
    localFile->close();
}
