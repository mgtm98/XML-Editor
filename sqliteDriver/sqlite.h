#ifndef SQLITECLASS_H
#define SQLITECLASS_H

#include <QSqlDatabase>
#include <QSql>
#include <QSqlError>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QSqlQuery>
#include <QString>
#include <QStringList>
#include <QSqlError>

class SQLite{
public:
    SQLite(QString);
    SQLite(QString connName, QString dbName);
    bool open();
    bool open(QString path);
    QSqlQuery sql_getQuery();
    int sql_insert(QString table, QStringList columns, QStringList values);
    int sql_select(QString select, QString from, QString where);
    int sql_update(QString table, QStringList columns, QStringList values, QString where);
    int sql_delete(QString table, QString where);
    int sql_create(QString table, QStringList columns, QStringList types);
    int sql_close();
private:
    QSqlDatabase db;
    QSqlQuery query;
    QString path;
    QString connName;

};

#endif // SQLITECLASS_H
