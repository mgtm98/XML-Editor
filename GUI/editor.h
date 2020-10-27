#ifndef EDITOR_H
#define EDITOR_H

#include <QPlainTextEdit>
#include <QPainter>
#include <QTextBlock>
#include <QtDebug>
#include <QSyntaxHighlighter>
#include <QCompleter>
#include <QAbstractItemView>
#include <QScrollBar>

class LineNumberArea;

class Editor : public QPlainTextEdit{
    Q_OBJECT

public:
    Editor(QWidget *parent = nullptr);
    Editor(QSyntaxHighlighter*,QWidget*);
    void setCompleter(QCompleter *c);
    void setHighlighterCurrentLine(bool &s);
    void setHighlighterCurrentLineColor(QColor &c);
    void setTabWidth(int);
    void highlightLine(int, QColor &&);
    void reset();
    QString textUnderCursor();
    ~Editor();

// Made for xml editor project 2020 3rd Computer
signals:
    void beautify();
    void minify();
    void showSynsetInfo();
    void convertToJson();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void focusInEvent(QFocusEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;

private:
    LineNumberArea *numArea;
    QSyntaxHighlighter *pyHighlightrt;
    QColor currentLineHighlighterColor = QColor(Qt::white);
    bool isHighlightCurrentLine = false;
    QCompleter *completer = nullptr;

    void initFont();
    void updateNumAreaWidth(int);
    void highlightCurrentLine();
    void updateNumArea(const QRect &, int);
    void lineNumberPaintEvent(QPaintEvent *e);
    int lineNumberWidth();
    void insertCompletion(const QString &completion);

friend class LineNumberArea;
};

class LineNumberArea : public QWidget{
    Q_OBJECT

public:
    LineNumberArea(Editor *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const override {
        return QSize(codeEditor->lineNumberWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        codeEditor->lineNumberPaintEvent(event);
    }
private:
    Editor *codeEditor;
};


#endif // EDITOR_H
