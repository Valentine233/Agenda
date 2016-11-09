#include "db.h"

DB::DB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库
    db.setDatabaseName("agenda.db");     //创建一个note.db的文件存储数据
    db.open();   //开启数据库
}
DB::addEvent(QString q) {
    QSqlQuery query;
    query.prepare("sql");
}
