#ifndef HTMLHIGHLIGHTER_H
#define HTMLHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegExp>
#include <QDebug>

class HTMLHighlighter : public QSyntaxHighlighter{

public:
    explicit HTMLHighlighter(QTextDocument *parent = nullptr);

    // Helper
    static QTextCharFormat format(const QString &colorName, const QString &style = QString());

protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightingRule{
        QRegExp pattern;
        QTextCharFormat format;
        int matchIndex = 0;

        HighlightingRule() { }
        HighlightingRule(const QRegExp &r, int i, const QTextCharFormat &f) : pattern(r), format(f), matchIndex(i) { }
        HighlightingRule(const QString &p, int i, const QTextCharFormat &f) : pattern(QRegExp(p)), format(f), matchIndex(i) { }
    };

    void initialize();
    void highlightPythonBlock(const QString &text);
    bool matchMultiLine(const QString &text, const HighlightingRule &rule);

    QVector<HighlightingRule> _pythonHighlightingRules;
    HighlightingRule _triSingle, _triDouble;
};

#endif // HTMLHIGHLIGHTER_H
