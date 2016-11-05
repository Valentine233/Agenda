#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    //void settime();
    void setinit();
    void time(int time = 0);
    //void button();
    CreateNew *ct = new CreateNew(this);
    int offset;
    void mouseDoubleClickEvent(QMouseEvent *event);

signals:
    void openNewSignal(QMouseEvent *);

public slots:
    void open();
    void add(QString, QString, QString);
    void forward();
    void backwards();
    void currenttime();
    void openNew(QMouseEvent *event);

private:
    Ui::MainWindow *ui;
    QLabel *month = new QLabel(this);
    QLabel *dayLabels[7];
    QLabel *weekLabels[7];
};

#endif // MAINWINDOW_H
