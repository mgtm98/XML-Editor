#include "langcontroller.h"

LangController::LangController(Editor *e, QString filePath, QString ext):editor(e),db(filePath){
    this->filePath = filePath;
    QString dbPath = filePath.replace(ext,"db");
    if(!QFile::exists(dbPath)){
        db.open(dbPath);
        db.sql_create("Completer", {"id", "word", "occurence"}, {"INTEGER PRIMARY KEY AUTOINCREMENT", "TEXT", "INTEGER"});
    }else{
        db.open(dbPath);
    }
    completer = new QCompleter(createModel(db));
    e->setCompleter(completer);
//    QStringListModel *strModel = qobject_cast<QStringListModel*>(completer->model());
//    strModel->setStringList(strModel->stringList() << "Ahmed");
}

QStringListModel* LangController::createModel(SQLite db){
    QGuiApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    QStringList words;
    db.sql_select("word","Completer","1=1");
    while(db.sql_getQuery().next()){
        words.append(db.sql_getQuery().value(0).toString());
    }
    QGuiApplication::restoreOverrideCursor();
    return new QStringListModel(words);
}

LangController::~LangController(){
    db.sql_close();
    qDebug("Deleting langController");
}


