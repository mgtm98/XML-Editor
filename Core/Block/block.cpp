#include "block.h"

Block::Block(QString name, TagType tagType) : name{name}, tagType{tagType} {}

void Block::setName(QString name)
{
    this->name = name;
}

QString Block::getName()
{
    return name;
}

void Block::setTagType(TagType tagType) {
    this->tagType = tagType;
}

TagType Block::getTagType() {
    return tagType;
}

Block::~Block()
{
}
