#ifndef XMLCONTROLLER_H
#define XMLCONTROLLER_H

#include <QObject>
#include <QTextDocument>
#include <QDebug>
#include "GUI/editor.h"

class XMLController : public QObject{
    Q_OBJECT
public:
    XMLController(Editor *e);
    void onTextChanged();
private:
    Editor *editor;
};

#endif // XMLCONTROLLER_H
