#include "synsetinfo.h"

SynsetInfo::SynsetInfo(Trie<QList<Block*>*>* trie, QString fileName, QWidget *parent) : QWidget(parent), trie(trie){
    this->setWindowTitle(fileName + " (INFO)");
    this->setWindowFlag(Qt::Drawer);
    wordTXT = new QLineEdit(this);
    availableWordsLST = new QListWidget(this);
    mainLay = new QVBoxLayout();
    infoLayout = new QHBoxLayout();
    defLBL = new QLabel("Definition : ");
    defLBL->setWordWrap(true);

    this->setLayout(mainLay);
    mainLay->addWidget(wordTXT);
    mainLay->addWidget(availableWordsLST);
    mainLay->addLayout(infoLayout);
    infoLayout->addWidget(defLBL);

    connect(wordTXT, &QLineEdit::textChanged, this, &SynsetInfo::wordTXTChanged);
    connect(availableWordsLST, &QListWidget::currentTextChanged, this, &SynsetInfo::selectedWordChanged);
}

void SynsetInfo::wordTXTChanged(const QString s){
    availableWordsLST->clear();
    availableWordsLST->addItems(*(trie->stringsStartWith(s)));
}

void SynsetInfo::selectedWordChanged(QString w){
    if(w.compare("")){
        defLBL->setText("");
        for(Block *root : *(trie->getValue(w))){
            qDebug() << root->getName();
            for(Block* b : *(root->getValue())){
                qDebug() << b->getName();
                if(!b->getName().compare("def")){
                    qDebug() << "HERE";
                    defLBL->setText(defLBL->text() + "Definition : " + (*(b->getValue()))[0]->getName() + "\n");
                    break;
                }
            }
        }
    }
}
