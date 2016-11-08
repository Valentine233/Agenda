#ifndef DB_H
#define DB_H

#include <QString>
#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QObject>

class DB
{
public:
    DB();
    static QSqlDatabase db;
    static QSqlQuery query;
    void AddEvent(QString, QString, QString, QString);
};

#endif // DB_H
