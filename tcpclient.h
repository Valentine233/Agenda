#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QtNetwork>
#include <QFileDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QFile>
#include <QSqlQuery>
#include <QSql>
#include <QSqlRecord>
#include <mainwindow.h>

class TcpClient : public QDialog
{
    Q_OBJECT
public:
    TcpClient(QWidget *parent);
    void setinit();
    void readFromFile();

private slots:
    void send();  //连接服务器
    void acceptfile();
    void updateClientProgress(); //接收数据
    void displayError(QAbstractSocket::SocketError); //显示错误

private:
    QLineEdit *hostEdit = new QLineEdit(this); //主机
    QLineEdit *portEdit = new QLineEdit(this); //端口
    QLabel *status = new QLabel(this); //状态栏
    QPushButton *syncBt = new QPushButton(this); //更新键
    QTcpSocket *tcpClient;
    qint64 totalBytes;  //存放总大小信息
    qint64 bytesReceived;  //已收到数据的大小
    qint64 fileNameSize;  //文件名的大小信息
    QString fileName;   //存放文件名
    QFile *localFile = new QFile();   //本地文件
    QByteArray inBlock;   //数据缓冲区


};

#endif // TCPCLIENT_H
