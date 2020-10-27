#include "object_block.h"

ObjectBlock::ObjectBlock(QString name, TagType tagType) : Block{name, tagType} {
    blocks = new QVector<Block *>();
    attributes = new Map<QString, QString>();
}

QVector<Block *> *ObjectBlock::getValue()
{
    return blocks;
}

void ObjectBlock::addBlock(Block *blockPtr)
{
    blocks->push_back(blockPtr);
}

Map<QString, QString> *ObjectBlock::getAttributes() {
    return attributes;
}

ObjectBlock::~ObjectBlock()
{
    for (int i = 0; i < blocks->size(); i++)
    {
        delete (*blocks)[i];
    }
    delete blocks;
}
