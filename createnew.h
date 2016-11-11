#ifndef CREATENEW_H
#define CREATENEW_H

#include <QDialog>
#include <QWidget>
#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDateTimeEdit>

class CreateNew : public QDialog
{
    Q_OBJECT

public:
    CreateNew(QWidget* parent=Q_NULLPTR);
    void setinit();

protected slots:
    void send()
    {
        emit trans(day->text(), time1->text(), time2->text());
    }

signals:
    void trans(QString, QString, QString);

private:
    QLineEdit* day;
    QLineEdit* time1;
    QLineEdit* time2;
};

#endif // CREATENEW_H
