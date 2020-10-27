#include "xmlHighlighter.h"

XMLHighlighter::XMLHighlighter(QTextDocument *parent):Highlighter(parent){
    addRule(QRegularExpression(QString("<[^>]+>|\\n+")), format(QColor(86, 156, 214)));
    addRule(QRegularExpression(QString("\\b(?<=\\s)(.*?)(?=\\=)\\b")), format(QColor(156, 220, 254)));
    addRule(QRegularExpression(QString("\"(.*?)\"")), format(QColor(206, 145, 120)));
    addRule(QRegularExpression(QString("<")), format(QColor(128, 128, 128)));
    addRule(QRegularExpression(QString(">")), format(QColor(128, 128, 128)));
    addRule(QRegularExpression(QString("</")), format(QColor(128, 128, 128)));
    addRule(QRegularExpression(QString("/>")), format(QColor(128, 128, 128)));
    addRule(QRegularExpression(QString("\\?")), format(QColor(128, 128, 128)));
    addRule(QRegularExpression(QString("=")), format(QColor(212, 212, 212)));
}
