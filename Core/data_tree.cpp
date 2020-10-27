#include "data_tree.h"
#include <QStringList>
#include <QTextStream>
#include <QStack>
#include <QStringBuilder>
#include <QDebug>

DataTree::DataTree(QString fileText)
{
    parseText(fileText);
}

DataTree::DataTree(QFile *inFileStream)
{
    parseText(getText(inFileStream));
}

DataTree *DataTree::readFile(QString inFileName)
{
    QFile *inFileStream = new QFile(inFileName);
    inFileStream->open(QIODevice::ReadOnly | QIODevice::Text);
    QString fileText = getText(inFileStream);
    delete inFileStream;
    DataTree *tree = new DataTree(fileText);
    return tree;
}

Block *DataTree::getRoot()
{
    return this->root;
}

QString DataTree::getText(QFile *inFileStream)
{
    QString fileText = "";
    QString temp;
    QTextStream in(inFileStream);
    while (!in.atEnd())
    {
        temp = in.readLine();
        fileText.append(temp);
    }
    return fileText;
}

void DataTree::parseText(const QString fileText)
{
    QVector<QString> *parts = getPartsOfText(fileText);
    buildTreeFromParts(parts);
}

QVector<QString> *DataTree::getPartsOfText(const QString fileText)
{
    QVector<QString> *parts = new QVector<QString>();
    QString temp = "";
    bool letterExist = false;
    bool inComment = false;
    QChar currentLetter;
    unsigned long length = fileText.length();
    for (unsigned long i = 0; i < length; i++)
    {
        currentLetter = fileText.at(i);
        // push the part inside parts in case a new tag(start tag or end tag) is found
        if (currentLetter == '<')
        {
            if (fileText.at(i + 1) == '!') {
                inComment = true;
            } else if (!inComment) {
                if (temp != "") {
                    parts->push_back(temp);
                }
                temp = "<";
                letterExist = true;
            }
        }
        // push the part inside parts in case the current tag is closed
        else if (currentLetter == '>' && !inComment)
        {
            temp += '>';
            parts->push_back(temp);
            temp = "";
            letterExist = false;
        }
        // add the current character to temp
        else if (letterExist || (currentLetter != ' ' && currentLetter != '\t' && currentLetter != '\n'))
        {
            if (currentLetter == '-' && inComment)  {
                if (fileText.mid(i, 3) == "-->") {
                    inComment = false;
                    i += 2;
                }
            } else if (!inComment) {
                temp += fileText.at(i);
                letterExist = true;
            }
        }
    }
    return parts;
}

void DataTree::buildTreeFromParts(QVector<QString> *parts)
{
    // root is the root block of the tree
    root = new ObjectBlock("root", TagType::NORMAL);
    // A stack to store the blocks and which levels they are in
    QStack<Block *> blocksStack;
    blocksStack.push(root);
    QString part;
    for (int i = 0; i < parts->size(); i++)
    {
        part = (*parts)[i];
        // In case the part was a single character like "x" or "y"
        if (part.length() == 1)
        {
            // It is of course a string
            blocksStack.top()->getValue()->push_back(new StringBlock(part));
        }
        // In case of ending tag
        else if (part.mid(0, 2) == "</")
        {
            // In case there was no value between the start tag and the end tag
            if ((*parts)[i - 1][0] == '<' && (*parts)[i - 1][1] != '/')
            {
                blocksStack.top()->getValue()->push_back(new StringBlock(""));
            }
            blocksStack.pop();
        }
        // In case of start tag
        else if (part[0] == '<')
        {
            //            qDebug() << part;
            //            part = part.mid(1, (*parts)[i].length() - 2);
            //            QStringList partsOfStartTag = part.split(' ', QString::SkipEmptyParts);
            QStringList partsOfStartTag = getPartsOfStartTag(part);
            // Create a new block and take the tag name from the tag string
            Block *temp = new ObjectBlock(partsOfStartTag[0], TagType::NORMAL);
            //            qDebug() << partsOfStartTag[0];
            for (int i = 1; i < partsOfStartTag.size(); i++)
            {
                if (i % 2 == 1 && partsOfStartTag[i] != "/")
                {
                    //                    qDebug() << partsOfStartTag[i];
                    //                    qDebug() << partsOfStartTag[i + 1];
                    temp->getAttributes()->insert(partsOfStartTag[i], partsOfStartTag[i + 1]);
                }
                else if (partsOfStartTag[i] == "/")
                {
                    temp->setTagType(TagType::SELF_ENDED);
                }
            }
            // Put the new tag inside the old tag
            blocksStack.top()->getValue()->push_back(temp);
            // Check if it is not the "xml" tag or "xml-model" tag or an ending solo tag
            if (partsOfStartTag[0] != "xml" && partsOfStartTag[0] != "xml-model" && temp->getTagType() != TagType::SELF_ENDED)
            {
                // push the tag into the stack
                blocksStack.push(temp);
            }
            else if (temp->getTagType() != TagType::SELF_ENDED)
            {
                temp->setTagType(TagType::INFO);
            }
        }
        // In case of a string(value)
        else
        {
            blocksStack.top()->getValue()->push_back(new StringBlock(part));
        }
    }
}

QStringList DataTree::getPartsOfStartTag(QString startTag)
{
    startTag = startTag.mid(1, startTag.length() - 1);
    QStringList parts;
    QString temp = QString("");
    bool insideAttributeValue = false;
    for (QChar letter : startTag)
    {
        if (letter == ' ')
        {
            if (insideAttributeValue)
            {
                temp += letter;
            }
            else if (temp != "")
            {
                parts.append(temp);
                temp = "";
            }
        }
        else if (letter == '"')
        {
            if (insideAttributeValue)
            {
                parts.append(temp);
                temp = "";
            }
            insideAttributeValue = !insideAttributeValue;
        }
        else if (letter == '=')
        {
            parts.append(temp);
            temp = "";
        }
        else if (letter == '?' && temp == "")
        {
            continue;
        }
        else if (letter == '>' && temp != "")
        {
            parts.append(temp);
        }
        else if (letter == '/' && !insideAttributeValue)
        {
            parts.append(QString("/"));
        }
        else
        {
            temp += letter;
        }
    }
    return parts;
}

DataTree::~DataTree()
{
    if (root != nullptr)
        delete root;
}
