#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "createnew.h"
#include <QMainWindow>
#include <QWidget>
#include <QPushButton>

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
    void setTime(int offset);
    void setinit();
    CreateNew *ct = new CreateNew(this);

public slots:
    void open();
    void add(QString, QString, QString);
    void forward();
    void backwards();
    void currenttime();

private:
    Ui::MainWindow *ui;
    QLabel *month = new QLabel(this);
    QLabel *dayLabels[7];
    QLabel *weekLabels[7];
    void setWindowStyle();
};

#endif // MAINWINDOW_H
