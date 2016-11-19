#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QtNetwork>
#include <QFileDialog>
#include <QPushButton>
#include <QLabel>
#include <QFile>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSql>
#include <QSqlRecord>
#include <mainwindow.h>
class TcpServer : public QDialog
{
    Q_OBJECT
public:
    TcpServer(QWidget *parent);
    void startTransfer();
    void writeToFile();

private slots:
    //void start();   //开始监听
    void setinit();
    void acceptConnection();  //建立连接
    void updateServerProgress(qint64 numBytes);  //发送数据
    void requestDialog();   //是否接受连接询问对话框

    //显示错误
    void displayError(QAbstractSocket::SocketError socketError);

private:
    QLabel *status = new QLabel(this); //状态栏
    QPushButton *confirmBt = new QPushButton(this); //确认键
    QTcpServer tcpServer;
    QTcpSocket *tcpServerConnection;
    QFile *localFile = new QFile();  //要发送的文件
    qint64 totalBytes;  //数据总大小
    qint64 bytesWritten;  //已经发送数据大小
    qint64 bytesToWrite;   //剩余数据大小
    qint64 loadSize;   //每次发送数据的大小
    QString fileName;  //保存文件路径
    QByteArray outBlock;  //数据缓冲区，即存放每次要发送的数据
//    qint64 totalBytes;  //存放总大小信息
//    qint64 bytesReceived;  //已收到数据的大小
//    qint64 fileNameSize;  //文件名的大小信息
//    QString fileName;   //存放文件名
//    QFile *localFile;   //本地文件
//    QByteArray inBlock;   //数据缓冲区
};

#endif // TCPSERVER_H
