#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QTextCharFormat>

class Highlighter : public QSyntaxHighlighter{
    Q_OBJECT

protected:
    enum Format{
        BOLD, ITALIC, BOLD_ITALIC, REGULAR
    };

public:
    Highlighter(QTextDocument *parent = nullptr);
    static QTextCharFormat format(const QColor &color, Highlighter::Format f = REGULAR);

protected:
    void addRule(const QRegularExpression &rgex, const QTextCharFormat &frmt);
    void highlightBlock(const QString &text) override;

private:
    struct HighlightingRule{
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

};

#endif // HIGHLIGHTER_H
