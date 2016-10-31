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
<<<<<<< HEAD
    void settime();
=======
    void time(int time = 0);
    void button();
>>>>>>> 01e57b3acbb00a2d30f1e6901502bb593d092658
    void setinit();
    CreateNew *ct = new CreateNew(this);
    int offset;

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
};

#endif // MAINWINDOW_H
