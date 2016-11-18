#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tcpclient.h"
#include "tcpserver.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QDateTime>
#include <QPushButton>
#include <QDialog>
#include <QMouseEvent>
#include <QWidget>
#include <QPixmap>
#include <QFile>
#include <QTextStream>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QList>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QFile>
#include "myeventlabel.h"
#include "youreventlabel.h"
#include "db.h"
#include "opennew.h"
#include "event.h"
#include <QTextCodec>
#include <QCoreApplication>
#include <QDateEdit>

class TcpClient;
class TcpServer;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int offset;
    static QDateTime curr_time;
    QDateEdit *dateEdit;
    QDate chooseDate;
    QPushButton *gotoBt;
    QLabel *gotoLabel;
    QPushButton *confirmDateBt;
    void refreshAgenda(int offset);
    void setinit();
    QTextStream MyEvent;
    QTextStream YourEvent;
    QList<Event*>* list;
    void turnToEventTime(Event *);
    void removeEventUI();
    QLabel* tempUI = NULL;
    const static int leftX = 50;
    const static int topY = 100;
    const static int gridHight = 40;
    const static int gridWidth = 50;
    const static int rightX = leftX + 14 * gridWidth;
    const static int bottomY = topY + 12 * gridHight;
    DB* db;
    QFile MyEventList;
    QFile YourEventList;
    TcpServer *tcpServer;
    void eventsLoseFocus();
    QLabel* detailLabel;
    int myTimeZone;
    int yourTimeZone;
    QLabel *yourZone;
    QLineEdit *lineEditZone;
    QPushButton *editZoneBt;
    QPushButton *confirmZoneBt;
    QString myColorDefault = "MyEventLabel {background-color: rgba(173,210,255,0.8); color: #333333}";
    QString myColorFocus = "MyEventLabel {background-color: rgba(108,174,255,0.8); color:white}";
    QString yourColorDefault = "YourEventLabel {background-color: rgba(240, 54, 60, 50); color: #333333}";
    QString yourColorFocus = "YourEventLabel {background-color: rgba(240, 54, 60, 90); color:white}";

signals:
    void openNewSignal(QMouseEvent *);
    void diffDaysSignal();

public slots:
    void forward();
    void backwards();
    void currentTime();
    void openSpecialNew(QMouseEvent *);
    void openGeneralNew();
    void createNewEvent(QString, QString, QDateTime, QDateTime, int);
    void createNewEventPl(QString,QString,QDate,QDate,QTime,QTime,int*,int);
    void editEvent(QString, QString, QDateTime, QDateTime, int, QString, QString, QDateTime, QDateTime);
    void deleteEvent(QString, QString, QDateTime, QDateTime, int);
    EventLabel* addEventUI(Event *);
    void loadFromDB();
    void writeToFile();
    void readFromFile();
    void showDetail(Event*);
    void updatedata();
    void editTimeZone();
    void toEditZone();
    void todate();
    void notTimeZone();
    void editCurrTime();
    void diffDays();

private:
    Ui::MainWindow *ui;
    QLabel *month = new QLabel(this);
    QLabel *dayLabels[7];
    QLabel *weekLabels[7];
    void setWindowStyle();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
};

#endif // MAINWINDOW_H
