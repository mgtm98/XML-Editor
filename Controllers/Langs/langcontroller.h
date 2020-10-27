#ifndef LANGCONTROLLER_H
#define LANGCONTROLLER_H

#include <QObject>
#include <QTextDocument>
#include <QDebug>
#include <QStringListModel>
#include <QAbstractItemModel>
#include <QGuiApplication>
#include <QCompleter>
#include <QDir>

#include <QObject>
#include "../../GUI/editor.h"
#include "../../sqliteDriver/sqlite.h"

class LangController : public QObject{
    Q_OBJECT
public:
    LangController(Editor *e, QString filePath, QString ext);
    ~LangController();
    virtual void onTextChanged() = 0;
    static QStringListModel* createModel(SQLite db);

protected:
    Editor *editor;
    QCompleter *completer;
    QString filePath;
    SQLite db;
};

#endif // LANGCONTROLLER_H
