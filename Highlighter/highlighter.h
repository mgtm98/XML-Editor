#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QTextCharFormat>

class Highlighter : public QSyntaxHighlighter{
    Q_OBJECT
public:
    Highlighter(QTextDocument *parent = nullptr);
    static QTextCharFormat format(const QColor &color, const QString &style = QString());

protected:
    void addRule(const QRegularExpression &rgex, const QTextCharFormat &frmt);

private:
    struct HighlightingRule{
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

protected:
    void highlightBlock(const QString &text) override;
};

#endif // HIGHLIGHTER_H
