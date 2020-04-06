#include "highlighter.h"

QTextCharFormat Highlighter::format(const QColor &color, const QString &style){
    QTextCharFormat format;
    format.setForeground(color);
    if(style.contains("bold"))
        format.setFontWeight(QFont::Bold);
    if(style.contains("italic"))
        format.setFontItalic(true);
    return format;
}

void Highlighter::addRule(const QRegularExpression &rgex, const QTextCharFormat &frmt){
    HighlightingRule r;
    r.pattern = rgex;
    r.format = frmt;
    highlightingRules.append(r);
}

void Highlighter::highlightBlock(const QString &text){
    for(const HighlightingRule &rule : qAsConst(highlightingRules)){
        QRegularExpressionMatchIterator iterator = rule.pattern.globalMatch(text);
        while(iterator.hasNext()){
            QRegularExpressionMatch match = iterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}


Highlighter::Highlighter(QTextDocument *parent):QSyntaxHighlighter(parent){

}
