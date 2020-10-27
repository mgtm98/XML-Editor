#ifndef SYNSETINFO_H
#define SYNSETINFO_H

#include "Core/Block/block.h"
#include "Data_Structures/trie.h"
#include <QWidget>
#include <QLineEdit>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>

class SynsetInfo : public QWidget{
    Q_OBJECT
public:
    SynsetInfo(Trie<QList<Block*>*>* trie, QString fileName, QWidget *parent = nullptr);

private:
    QLineEdit *wordTXT;
    QListWidget *availableWordsLST;
    QVBoxLayout *mainLay;
    Trie<QList<Block*>*>* trie;
    QHBoxLayout *infoLayout;
    QLabel *defLBL;
    void wordTXTChanged(const QString s);
    void selectedWordChanged(QString w);
};

#endif // SYNSETINFO_H
