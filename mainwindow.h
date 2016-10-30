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
    void time(int time = 0);
    void button();
    void setinit();
    CreateNew *ct = new CreateNew(this);
    int offset;

public slots:
    void open();
    void add(QString, QString, QString);

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
