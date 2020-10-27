#include <stack>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QVector>
#include <QDebug>
#include <QStack>
#include <vector>
#include "files_converter.h"

FilesConverter::FilesConverter(DataTree *dataTree, QString fileName) : dataTree{dataTree}
{
    QFile *fileStream = new QFile(fileName);
    fileStream->open(QIODevice::WriteOnly | QIODevice::Text);
    out = new QTextStream(fileStream);
}

void FilesConverter::generateXMLFile()
{
}

void FilesConverter::generateJSONFile()
{
    Block *root = dataTree->getRoot();
    (*out) << '{' << endl;
    indentCounter = 1;
    for (int i = 0; i < root->getValue()->size(); i++)
    {
        if (i == root->getValue()->size() - 1)
        {
            generateJSONObject((*(root->getValue()))[i], true);
        }
        else
        {
            generateJSONObject((*(root->getValue()))[i], false);
        }
    }
    (*out) << '}' << endl;
}

void FilesConverter::generateJSONObject(Block *currentBlock, bool isLast)
{
    if (currentBlock->getValue() != nullptr && currentBlock->getTagType() != TagType::INFO && currentBlock->getTagType() != TagType::SELF_ENDED)
    {
        if (currentBlock->getValue()->size() == 1 && (*(currentBlock->getValue()))[0]->getValue() == nullptr)
        {
            generateIndentation();
            (*out) << '"' << currentBlock->getName() << "\": ";
            if (currentBlock->getAttributes()->size() == 0)
            {
                (*out) << '"' << (*(currentBlock->getValue()))[0]->getName() << "\"" << (isLast ? "" : ",") << endl;
            }
            else
            {
                (*out) << "{" << endl;
                indentCounter++;
                vector<QString> keys = currentBlock->getAttributes()->keys();
                for (size_t i = 0; i < currentBlock->getAttributes()->size(); i++)
                {
                    generateIndentation();
                    (*out) << "\"@" << keys[i] << "\": \"" << currentBlock->getAttributes()->at(i) << "\",\n";
                }
                generateIndentation();
                (*out) << "\"#text\": \"" << (*(currentBlock->getValue()))[0]->getName() << "\"\n";
                indentCounter--;
                generateIndentation();
                (*out) << "}" << (isLast ? "" : ",") << endl;
            }
        }
        else
        {
            generateIndentation();
            (*out) << '"' << currentBlock->getName() << "\": {" << endl;
            indentCounter++;
            vector<QString> keys = currentBlock->getAttributes()->keys();
            for (size_t i = 0; i < currentBlock->getAttributes()->size(); i++)
            {
                generateIndentation();
                (*out) << "\"@" << keys[i] << "\": \"" << currentBlock->getAttributes()->at(i) << "\",\n";
            }
            for (int i = 0; i < currentBlock->getValue()->size(); i++)
            {

                if (i == currentBlock->getValue()->size() - 1)
                {
                    generateJSONObject((*(currentBlock->getValue()))[i], true);
                }
                else
                {
                    generateJSONObject((*(currentBlock->getValue()))[i], false);
                }
            }
            indentCounter--;
            generateIndentation();
            (*out) << "}" << (isLast ? "" : ",") << endl;
        }
    }
    else if (currentBlock->getTagType() == TagType::SELF_ENDED)
    {
        generateIndentation();
        (*out) << '"' << currentBlock->getName() << "\": ";
        if (currentBlock->getAttributes()->size() == 0)
        {
            (*out) << '"' << (*(currentBlock->getValue()))[0]->getName() << "\"" << (isLast ? "" : ",") << endl;
        }
        else
        {
            (*out) << "{" << endl;
            indentCounter++;
            vector<QString> keys = currentBlock->getAttributes()->keys();
            for (size_t i = 0; i < currentBlock->getAttributes()->size(); i++)
            {
                generateIndentation();
                (*out) << "\"@" << keys[i] << "\": \"" << currentBlock->getAttributes()->at(i) << "\"" << (i == currentBlock->getAttributes()->size() - 1 ? "" : ",") << "\n";
            }
            indentCounter--;
            generateIndentation();
            (*out) << "}" << (isLast ? "" : ",") << endl;
        }
    }
}

void FilesConverter::generateIndentation()
{
    for (unsigned int i = 0; i < indentCounter; i++)
    {
        (*out) << '\t';
    }
}

FilesConverter::~FilesConverter()
{
    if (out != nullptr)
        delete out;
}
