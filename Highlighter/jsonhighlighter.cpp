#include "jsonhighlighter.h"

JSONHighlighter::JSONHighlighter(QTextDocument *parent): Highlighter(parent){
    addRule(QRegularExpression(QString("\"(.*?)\"")), format(QColor(152, 220, 254)));
    addRule(QRegularExpression(QString("(?<=:\\s)(\"(.*?)\")")), format(QColor(206, 145, 120)));
}
