#include "xmlHighlighter.h"

XMLHighlighter::XMLHighlighter(QTextDocument *parent):Highlighter(parent){
    addRule(QRegularExpression(QString("<[^>]+>|\\n+")), format(QColor(Qt::darkCyan)));
    addRule(QRegularExpression(QString("[0-9]+")), format(QColor(Qt::darkYellow)));
}
