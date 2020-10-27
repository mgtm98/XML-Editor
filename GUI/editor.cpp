#include "editor.h"

Editor::Editor(QWidget *parent):Editor(nullptr, parent){
}

Editor::Editor(QSyntaxHighlighter *highlighter, QWidget *parent):QPlainTextEdit(parent){
    numArea = new LineNumberArea(this);
    this->setBackgroundVisible(true);
    if(highlighter != nullptr) highlighter->setDocument(document());

    setViewportMargins(lineNumberWidth(),0,0,0);
    setLineWrapMode(QPlainTextEdit::NoWrap);
    initFont();
    setTabWidth(4);

    connect(this, &Editor::blockCountChanged, this, &Editor::updateNumAreaWidth);
    connect(this, &Editor::updateRequest, this, &Editor::updateNumArea);
    connect(this, &Editor::cursorPositionChanged, this, &Editor::highlightCurrentLine);
}

void Editor::initFont(){
    QFont font;
    font.setFamily("Courier");
    font.setStyleHint(QFont::Monospace);
    font.setFixedPitch(true);
    font.setPointSize(10);
    setFont(font);
}

int Editor::lineNumberWidth(){
    int digits = 1;
    int max = qMax(1, blockCount());
    while(max >= 10){
        max /= 10;
        digits ++;
    }
    int space = 3 + digits * fontMetrics().horizontalAdvance("9");
    return space + 40;
}

void Editor::updateNumAreaWidth(int){
    setViewportMargins(lineNumberWidth(),0,0,0);
}

void Editor::updateNumArea(const QRect &rect, int dy){
    if (dy)
        numArea->scroll(0, dy);
    else
        numArea->update(0, rect.y(), numArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateNumAreaWidth(0);
}

void Editor::resizeEvent(QResizeEvent *e){
    QPlainTextEdit::resizeEvent(e);
    QRect cr = contentsRect();
    numArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberWidth(), cr.height()));
}

void Editor::lineNumberPaintEvent(QPaintEvent *event){
    QPainter painter(numArea);
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    qreal top = blockBoundingGeometry(block).translated(contentOffset()).top();
    qreal bottom = top + blockBoundingRect(block).height();
    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.drawText(-20, top, numArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }
        block = block.next();
        top = bottom;
        bottom = top + blockBoundingRect(block).height();
        ++blockNumber;
    }
}

void Editor::highlightCurrentLine(){
    QList<QTextEdit::ExtraSelection> extraSelections;
    if (!isReadOnly() && isHighlightCurrentLine) {
        QTextEdit::ExtraSelection selection;
        selection.format.setBackground(currentLineHighlighterColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }
    setExtraSelections(extraSelections);
}

void Editor::setHighlighterCurrentLine(bool &s){
    isHighlightCurrentLine = s;
}

void Editor::setHighlighterCurrentLineColor(QColor &c){
    currentLineHighlighterColor = c;
}

void Editor::setTabWidth(int tabWidth){
   QFontMetrics metrics(this->font());
   setTabStopWidth(tabWidth * metrics.width(' '));
}

void Editor::highlightLine(int line, QColor &&c){
        QTextCursor cursor(this->document()->findBlockByLineNumber(line));
        QTextBlockFormat blockFormat = cursor.blockFormat();
        blockFormat.setBackground(c);
        cursor.setBlockFormat(blockFormat);
}

void Editor::reset(){
    for(int a = 0; a < this->document()->blockCount(); a++){
        highlightLine(a, QColor(Qt::transparent));
    }
}

void Editor::setCompleter(QCompleter *c){
    if(c == nullptr) return;
    if(completer) completer->disconnect(this);
    completer = c;
    completer->setWidget(this);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    connect(c, QOverload<const QString &>::of(&QCompleter::activated), this, &Editor::insertCompletion);
}

void Editor::focusInEvent(QFocusEvent *e){
    if(completer != nullptr) completer->setWidget(this);
    QPlainTextEdit::focusInEvent(e);
}

void Editor::insertCompletion(const QString &completion){
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::SelectionType::WordUnderCursor);
    tc.removeSelectedText();
    tc.insertText(completion);
    setTextCursor(tc);
}

QString Editor::textUnderCursor(){
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    return tc.selectedText();
}

void Editor::keyPressEvent(QKeyEvent *e){
    if(completer == nullptr){
        QPlainTextEdit::keyPressEvent(e);
        return;
    }

    if (completer->popup()->isVisible()) {
      switch (e->key()) {
      case Qt::Key_Enter:
      case Qt::Key_Return:
      case Qt::Key_Escape:
      case Qt::Key_Tab:
      case Qt::Key_Backtab:
           e->ignore();
           return;
      default:
          break;
      }
   }

   bool isShortcut = (e->modifiers().testFlag(Qt::ControlModifier) && e->key() == Qt::Key_E); // CTRL+E
   bool ctrlOrShift = e->modifiers().testFlag(Qt::ControlModifier) || e->modifiers().testFlag(Qt::ShiftModifier);
   bool hasModifier = (e->modifiers() != Qt::NoModifier) && !ctrlOrShift;
   QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-= "); // end of word
   QString completionPrefix = textUnderCursor();

   if (!isShortcut) QPlainTextEdit::keyPressEvent(e);
   if (ctrlOrShift && e->text().isEmpty()) return;

   if (!isShortcut && (hasModifier || e->text().isEmpty()|| completionPrefix.length() < 1
                     || eow.contains(e->text().right(1)))) {
       completer->popup()->hide();
       return;
   }

   if (completionPrefix != completer->completionPrefix()) {
       completer->setCompletionPrefix(completionPrefix);
       completer->popup()->setCurrentIndex(completer->completionModel()->index(0, 0));
   }

   QRect cr = cursorRect();
   cr.setWidth(completer->popup()->sizeHintForColumn(0)
               + completer->popup()->verticalScrollBar()->sizeHint().width());
   completer->popup()->setObjectName("autoCompletePopup");
   completer->complete(cr); // popup it up!
}

Editor::~Editor(){
}
