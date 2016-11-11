#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "event.h"
#include "opennew.h"
#include "createnew.h"
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
#include <db.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    int offset;
    static QDateTime curr_time;
    void refreshAgenda(int offset);
    void setinit();
    CreateNew *ct = new CreateNew(this);
    void mouseDoubleClickEvent(QMouseEvent *);
    QTextStream MyEvent;
    QTextStream YourEvent;
    static QList<Event*>* mylist;
    static QList<Event*>* yourlist;
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

signals:
    void openNewSignal(QMouseEvent *);
    //void updateEvent(int, int, int, int);
    //void removeUI(Event *event);

public slots:
    //void update(int,int,int,int);
    void open();
    void add(QString, QString, QString);
    void forward();
    void backwards();
    void currentTime();
    void openNew(QMouseEvent *);
    void createNewEvent(QString, QString, QDateTime, QDateTime, int);
    QLabel* addEventUI(Event *);
    void loadFromDB();

private:
    Ui::MainWindow *ui;
    QLabel *month = new QLabel(this);
    QLabel *dayLabels[7];
    QLabel *weekLabels[7];
    void setWindowStyle();
};

#endif // MAINWINDOW_H
