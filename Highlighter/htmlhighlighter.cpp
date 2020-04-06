#include "htmlHighlighter.h"

typedef QMap<QString, QTextCharFormat> FormatMap;

static const FormatMap STYLES = {
    { "keyword", HTMLHighlighter::format("#569CD6") },
    { "operator", HTMLHighlighter::format("red") },
    { "brace", HTMLHighlighter::format("darkGray") },
    { "defclass", HTMLHighlighter::format("#4EC9B0", "bold") },
    { "deffunc", HTMLHighlighter::format("#DCDCAA") },
    { "string", HTMLHighlighter::format("magenta") },
    { "string2", HTMLHighlighter::format("darkMagenta") },
    { "comment", HTMLHighlighter::format("#6A9955") },
    { "self", HTMLHighlighter::format("#569CD6", "italic") },
    { "numbers", HTMLHighlighter::format("#B5CEA8") },
    { "keyword2", HTMLHighlighter::format("#C586C0") }

};

HTMLHighlighter::HTMLHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent){
    initialize();
}

void HTMLHighlighter::highlightBlock(const QString &text){
    highlightPythonBlock(text);
}

/////

void HTMLHighlighter::initialize(){

    _triSingle = HighlightingRule("'''", 1, STYLES["string2"]);
    _triDouble = HighlightingRule("\"\"\"", 2, STYLES["string2"]);

    // 'self'
    _pythonHighlightingRules += HighlightingRule("<[^>]+>", 0, STYLES["self"]);

//    // Double-quoted string, possibly containing escape sequences
//    _pythonHighlightingRules += HighlightingRule("\"[^\"\\\]*(\\\\.[^\"\\\]*)*\"", 0, STYLES["string"]);

//    // Single-quoted string, possibly containing escape sequences
//    _pythonHighlightingRules += HighlightingRule("\"[^'\\\]*(\\\\.[^'\\\]*)*\"", 0, STYLES["string"]);

//    // 'def' followed by an identifier
//    _pythonHighlightingRules += HighlightingRule("\\bdef\\b\\s*(\\w+)", 1, STYLES["deffunc"]);

//    // 'class' followed by an identifier
//    _pythonHighlightingRules += HighlightingRule("\\bclass\\b\\s*(\\w+)", 1, STYLES["defclass"]);

//    // From '#' until a newline
//    _pythonHighlightingRules += HighlightingRule("#[^\\n]*", 0, STYLES["comment"]);

    // Numeric literals
    _pythonHighlightingRules += HighlightingRule("\\b[+-]?[0-9]+[lL]?\\b", 0, STYLES["numbers"]);
    _pythonHighlightingRules += HighlightingRule("\\b[+-]?0[xX][0-9A-Fa-f]+[lL]?\\b", 0, STYLES["numbers"]);
    _pythonHighlightingRules += HighlightingRule("\\b[+-]?[0-9]+(?:\\.[0-9]+)?(?:[eE][+-]?[0-9]+)?\\b", 0, STYLES["numbers"]);
}

void HTMLHighlighter::highlightPythonBlock(const QString &text)
{
    if(text.isEmpty())
        return;

    int index = -1;

    // Do other syntax formatting
    for(const auto &rule : _pythonHighlightingRules)
    {
        index = rule.pattern.indexIn(text, 0);

        // We actually want the index of the nth match
        while(index >= 0)
        {
            index = rule.pattern.pos(rule.matchIndex);
            int length = rule.pattern.cap(rule.matchIndex).length();
            if(length > 0)
            {
                setFormat(index, length, rule.format);
                index = rule.pattern.indexIn(text, index + length);
            }
        }
    }

    setCurrentBlockState(0);

    // Do multi-line strings
    bool in_multiline = matchMultiLine(text, _triSingle);
    if(!in_multiline)
        in_multiline = matchMultiLine(text, _triDouble);
}


QTextCharFormat HTMLHighlighter::format(const QString &colorName, const QString &style){
    QColor color;
    color.setNamedColor(colorName);
    QTextCharFormat format;
    format.setForeground(color);
    if(style.contains("bold"))
        format.setFontWeight(QFont::Bold);
    if(style.contains("italic"))
        format.setFontItalic(true);
    return format;
}

bool HTMLHighlighter::matchMultiLine(const QString &text, const HighlightingRule &rule)
{
    int start, add, end, length;

    // If inside triple-single quotes, start at 0
    if(previousBlockState() == rule.matchIndex)
    {
        start = 0;
        add = 0;
    }
    // Otherwise, look for the delimiter on this line
    else
    {
        start = rule.pattern.indexIn(text);
        // Move past this match
        add = rule.pattern.matchedLength();
    }

    // As long as there's a delimiter match on this line...
    while(start >= 0)
    {
        // Look for the ending delimiter
        end = rule.pattern.indexIn(text, start + add);
        // Ending delimiter on this line?
        if(end >= add)
        {
            length = end - start + add + rule.pattern.matchedLength();
            setCurrentBlockState(0);
        }
        // No; multi-line string
        else
        {
            setCurrentBlockState(rule.matchIndex);
            length = text.length() - start + add;
        }

        // Apply formatting
        setFormat(start, length, rule.format);

        // Look for the next match
        start = rule.pattern.indexIn(text, start + length);
    }

    // Return True if still inside a multi-line string, False otherwise
    if(currentBlockState() == rule.matchIndex)
        return true;
    else
        return false;
}
