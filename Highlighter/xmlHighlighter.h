#ifndef XMLHIGHLIGHTER_H
#define XMLHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QDebug>
#include "Highlighter/highlighter.h"

class XMLHighlighter :public Highlighter{

public:
    XMLHighlighter(QTextDocument *parent = nullptr);
};

#endif // XMLHIGHLIGHTER_H
