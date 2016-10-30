#ifndef CREATENEW_H
#define CREATENEW_H

#include <QDialog>
#include<QWidget>
#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
class CreateNew : public QDialog
{
    Q_OBJECT

public:
    CreateNew(QWidget* parent=nullptr);
    void setinit();

protected slots:
    void send()
    {
        emit trans(day->text(), time1->text(), time2->text());
    }

signals:
    void trans(QString day, QString time1, QString time2);

private:

    QLineEdit* time1;
    QLineEdit* day;
    QLineEdit* time2;


};

#endif // CREATENEW_H
