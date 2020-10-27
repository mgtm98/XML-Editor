#ifndef FILES_CONVERTER_H_
#define FILES_CONVERTER_H_

#include <QString>
#include <QFile>
#include <QString>
#include <QTextStream>
#include "data_tree.h"

using namespace std;

class FilesConverter
{
private:
    QTextStream *out;
    DataTree *dataTree;
    unsigned int indentCounter;

    void generateJSONObject(Block *currentBlock, bool isLast);
    void generateIndentation();

public:
    FilesConverter(DataTree *dataTree, QString fileName);
    void generateXMLFile();
    void generateJSONFile();
    ~FilesConverter();
};

#endif /* FILES_CONVERTER_H_ */
