#ifndef XMLCONTROLLER_H
#define XMLCONTROLLER_H

#include "langcontroller.h"
#include "Core/data_tree.h"
#include "Core/Block/block.h"
#include "Core/files_converter.h"
#include "Data_Structures/map_vector.h"
#include "Data_Structures/trie.h"
#include "GUI/synsetinfo.h"
#include <QList>
#include <QApplication>
#include <QDesktopWidget>

class XMLController : public LangController{
    Q_OBJECT
public:
    XMLController(Editor *e, QString filePath);
    ~XMLController();
    void onTextChanged() override;
    void beautify();
    void minify();
    void showSynsetInfo();
    void convert2JSON();
    int getSynsetNumber();
    Trie<QList<Block*>*>* getBlockTrie();
private:
    typedef struct Info{
        QString tagName;
        Map<QString, QString> *attr;
        TagType type;
    } Info;
    void _readTree(Block *root, int level, QList<QString> &tagList, QList<QPair<Info, int>> &queue);
    static QString _buildXML(QList<QPair<Info, int>> &queue);
    int synsetNumber = 0;
    QList<QString> tagList;
    QList<QPair<Info, int>> l_queue;
};

#endif // XMLCONTROLLER_H
