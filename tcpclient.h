#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QtNetwork>
#include <QFileDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QFile>

class TcpClient : public QDialog
{
    Q_OBJECT
public:
    TcpClient(QWidget *parent, QFile *YourEventList);
    void setinit();

private slots:
    void send();  //连接服务器
    void acceptfile();
//    void startTransfer();  //发送文件大小等信息
    void updateClientProgress(); //接收数据
    void displayError(QAbstractSocket::SocketError); //显示错误
//    void openFile();  //打开文件

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
    QFile *localFile;   //本地文件
    QByteArray inBlock;   //数据缓冲区
//    QFile *localFile;  //要发送的文件
//    qint64 totalBytes;  //数据总大小
//    qint64 bytesWritten;  //已经发送数据大小
//    qint64 bytesToWrite;   //剩余数据大小
//    qint64 loadSize;   //每次发送数据的大小
//    QString fileName;  //保存文件路径
//    QByteArray outBlock;  //数据缓冲区，即存放每次要发送的数据

};

#endif // TCPCLIENT_H
