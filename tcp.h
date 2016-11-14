#ifndef TCP_H
#define TCP_H

#include "mainwindow.h"
#include <QtNetwork>
#include <QFileDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QProgressBar>
#include <QMessageBox>
#include <QFile>

class Tcp : public QWidget
{
    Q_OBJECT
public:
    Tcp(QWidget *parent, QFile *MyEventList, QFile *YourEventList);
    void senderSetinit();
    void receiverSetinit();

private slots:
    void requestDialog();  //是否接受连接询问对话框
    void send();  //连接服务器
    void startTransfer();  //发送文件大小等信息
    void updateServerProgress(qint64); //更新服务器进度
    void updateClientProgress(qint64); //更新客户端进度
    void acceptConnection();  //建立连接
    void displayError(QAbstractSocket::SocketError); //显示错误

private:
    QLineEdit *hostEdit = new QLineEdit(this); //主机
    QLineEdit *portEdit = new QLineEdit(this); //端口
    QLabel *status = new QLabel(this); //状态栏
    QPushButton *syncBt = new QPushButton(this); //同步键
    QTcpSocket *tcpSocket;
    QFile *sdFile;  //发送的文件
    qint64 sdTotalBytes;  //数据总大小
    qint64 sdBytesWritten;  //已经发送数据大小
    qint64 sdBytesToWrite;   //剩余数据大小
    qint64 sdLoadSize;   //每次发送数据的大小
    QString sdFileName;  //保存文件路径
    QByteArray outBlock;  //数据缓冲区，即存放每次要发送的数据

    QTcpServer tcpServer;
    QPushButton *confirmBt = new QPushButton(this); //确认键
    QFile *rcFile;  //收到的文件
    qint64 rcTotalBytes;  //存放总大小信息
    qint64 rcBytesReceived;  //已收到数据的大小
    qint64 rcFileNameSize;  //文件名的大小信息
    QString rcFileName;   //存放文件名
    QByteArray inBlock;   //数据缓冲区
};
#endif // TCP_H
