#ifndef DATA_TREE_H_
#define DATA_TREE_H_

#include <QFile>
#include <QStringList>
#include "Block/object_block.h"
#include "Block/string_block.h"

class DataTree
{
private:
    Block *root = nullptr;
    void parseText(QString fileText);
    static QString getText(QFile *inFileStream);
    QVector<QString> *getPartsOfText(QString fileText);
    void buildTreeFromParts(QVector<QString> *);
    QStringList getPartsOfStartTag(QString startTag);

public:
    DataTree(QString fileText);
    static DataTree *readFile(QString inFileName);
    DataTree(QFile *inFileStream);
    Block *getRoot();
    ~DataTree();
};

#endif // DATA_TREE_H_
