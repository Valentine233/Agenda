#include "db.h"

DB::DB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/tmp/my.db");
    if (!db.open())
    {
        qDebug()<<query.lastError();
    }

    query = QSqlQuery(db);
    query.exec("CREATE TABLE IF NOT EXISTS event (id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "name NVARCHAR(20) NOT NULL,"
               "place NVARCHAR(20) NOT NULL,"
               "starttime NVARCHAR(50) NOT NULL,"
               "endtime NVARCHAR(50) NOT NULL,"
               "type INTEGER NOT NULL);");
}

void DB::dropDB() {
    query = QSqlQuery(db);
    query.exec("DROP TABLE IF EXISTS event;");
}

void DB::addEvent(QString name, QString place, QDateTime startTime, QDateTime endTime, int type)
{
    query = QSqlQuery(db);
    query.prepare("INSERT INTO event (name, place, starttime, endtime, type) VALUES(:name, :place, :start, :end, :type);");
    query.bindValue(":name", name);
    query.bindValue(":place", place);
    query.bindValue(":start", startTime.toString());
    query.bindValue(":end", endTime.toString());
    query.bindValue(":type", type);
    bool success = query.exec();
    if (!success) {
        qDebug()<<query.lastError();
    }
}

QSqlQuery DB::readEvent() {
    query = QSqlQuery(db);
    query.exec("SELECT * FROM event;");
    return query;
}

void DB::deleteEvent(QString name, QString place, QDateTime startTime, QDateTime endTime, int type) {
    query = QSqlQuery(db);
    query.prepare("DELETE FROM event WHERE name = :name AND place = :place AND starttime = :start AND endtime = :end AND type = :type;");
    query.bindValue(":name", name);
    query.bindValue(":place", place);
    query.bindValue(":start", startTime.toString());
    query.bindValue(":end", endTime.toString());
    query.bindValue(":type", type);
    if(!query.exec())
    {
        qDebug() << "deleteError\n";
        qDebug()<<query.lastError();
    }
}

void DB::updateEvent(QString name, QString place, QDateTime startTime, QDateTime endTime, int type, QString nameOld, QString placeOld, QDateTime startOld, QDateTime endOld)
{
    if(type != 0)
    {
        qDebug() << "Can't update others' events\n";
        return;
    }
    query = QSqlQuery(db);
    query.prepare("UPDATE event SET name = :name, place = :place, starttime = :start, endtime = :end"
                  " WHERE  name = :oldname AND place = :oldplace AND starttime = :oldstart AND endtime = :oldend AND type = 0;");
    query.bindValue(":name", name);
    query.bindValue(":place", place);
    query.bindValue(":start", startTime.toString());
    query.bindValue(":end", endTime.toString());
    query.bindValue(":oldname", nameOld);
    query.bindValue(":oldplace", placeOld);
    query.bindValue(":oldstart", startOld.toString());
    query.bindValue(":oldend", endOld.toString());
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
}
