#ifndef JSONHIGHLIGHTER_H
#define JSONHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QDebug>
#include "Highlighter/highlighter.h"

class JSONHighlighter: public Highlighter{
public:
    JSONHighlighter(QTextDocument *parent = nullptr);
};

#endif // JSONHIGHLIGHTER_H
