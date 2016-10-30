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
    void time();
    void button();
    void setinit();
    CreateNew *ct = new CreateNew;

public slots:
    void open();
    void add(QString day, QString time1, QString time2);

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
