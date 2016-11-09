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
    QDateTime curr_time;
    void setTime(int offset);
    void setinit();
    CreateNew *ct = new CreateNew(this);
    void mouseDoubleClickEvent(QMouseEvent *);
    static QTextStream MyEvent;
    static QTextStream YourEvent;
    static QList<Event> *mylist;
    static QList<Event> *yourlist;
    void turnToEventTime(Event *);

signals:
    void openNewSignal(QMouseEvent *);
    //void updateEvent(int, int, int, int);

public slots:
    //void update(int,int,int,int);
    void open();
    void add(QString, QString, QString);
    void forward();
    void backwards();
    void currenttime();
    void openNew(QMouseEvent *);
    void addtoEventList(QString, QString, QDateTime, QDateTime, int);
    void addEventUI(Event *);

private:
    Ui::MainWindow *ui;
    QLabel *month = new QLabel(this);
    QLabel *dayLabels[7];
    QLabel *weekLabels[7];
    void setWindowStyle();
};

#endif // MAINWINDOW_H
