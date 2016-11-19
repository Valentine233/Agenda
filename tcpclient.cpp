#include "tcpclient.h"

TcpClient::TcpClient(QWidget *parent) : QDialog(parent)
{
//    qDebug() << QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    if (!QDir(QStandardPaths::writableLocation(QStandardPaths::DataLocation)).exists())
        QDir().mkdir(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
    localFile->setFileName(QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/YourEventList.txt");
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
   qDebug() << "duang";
   QDataStream in(tcpClient);
   in.setVersion(QDataStream::Qt_5_7);
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
           qDebug() << fileName;
//           QString tmpFileName;
           in >> fileName;
//           fileName = localFile->fileName();
           qDebug() << fileName;
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
    readFromFile();
   }
}

void TcpClient::displayError(QAbstractSocket::SocketError) //显示错误
{
    qDebug() << tcpClient->errorString();
    tcpClient->close();
    status->setText(tr("发送错误"));
    syncBt->setEnabled(true);
}

void TcpClient::readFromFile() //接收对方文件时
{
    //未实现替换现有YourEventList文件！
    ((MainWindow*)parent())->db->deleteAllYourEvent();
    if(!localFile->open(QIODevice::ReadWrite | QIODevice::Text))
    {
         qDebug()<<"ReadError: Can't open the file!\n";
         return;
    }
    while(!localFile->atEnd()) {
        QByteArray line = localFile->readLine();
        QString str(line);
        int i=0;
        int flag=0;
        QString Name, Place, Start, End, Type;
        while(str[i]!='\x0')
        {
            while(str[i]!=',' || str[i+1]!=';')
            {
                switch (flag) {
                case 0: //0:eventName
                    Name += str[i];
                    break;
                case 1: //1:eventPlace
                    Place += str[i];
                    break;
                case 2: //2:eventStart
                    Start += str[i];
                    break;
                case 3: //3:eventEnd
                    End += str[i];
                    break;
                case 4: //4:eventType
                    Type += str[i];
                    break;
                default:
                    break;
                }
                if(str[i+1] == '\x0' || str[i+1] == '\n')
                    break;
                i++;
            }
            if(flag!=4)
                i++;
            flag++;
            i++;
        }
        QDateTime starttime = QDateTime::fromString(Start, "yyyy/MM/dd HH:mm");
        QDateTime endtime = QDateTime::fromString(End, "yyyy/MM/dd HH:mm");
        //set time zone of the other
        QTimeZone zone(((MainWindow*)parent())->yourTimeZone*3600);
        starttime.setTimeZone(zone);
        endtime.setTimeZone(zone);
        if(Type != "0") //对于对方来说是0事件
        {
            qDebug() << "type=" <<Type << "error";
        }
        int type = 1; //储存为1事件

        ((MainWindow*)parent())->createNewEvent(Name, Place, starttime, endtime, type);
    }
    ((MainWindow*)parent())->refreshAgenda(((MainWindow*)parent())->offset);
    localFile->close();
}
