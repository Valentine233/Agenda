#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
//#include "eventlabel.h"
#include "myeventlabel.h"
#include "youreventlabel.h"
#include "db.h"
#include "opennew.h"
#include "event.h"
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
    void eventsLoseFocus();
    QLabel* detailLabel;

signals:
    void openNewSignal(QMouseEvent *);

public slots:
    void forward();
    void backwards();
    void currentTime();
    void openSpecialNew(QMouseEvent *);
    void openGeneralNew();
    void createNewEvent(QString, QString, QDateTime, QDateTime, int);
    void editEvent(QString, QString, QDateTime, QDateTime, int, QString, QString, QDateTime, QDateTime);
    void deleteEvent(QString, QString, QDateTime, QDateTime, int);
    EventLabel* addEventUI(Event *);
    void loadFromDB();
    void writeToFile();
    void readFromFile();


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
