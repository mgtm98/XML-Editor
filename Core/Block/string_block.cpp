#include "string_block.h"

StringBlock::StringBlock(QString name) : Block{name, TagType::STRING} {}

QVector<Block *> *StringBlock::getValue()
{
    return nullptr;
}

Map<QString, QString> *StringBlock::getAttributes() {
    return nullptr;
}

StringBlock::~StringBlock()
{
}
