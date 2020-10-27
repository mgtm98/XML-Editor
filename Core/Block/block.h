#ifndef BLOCK_H_
#define BLOCK_H_

#include <QString>
#include <QVector>
#include "../../Data_Structures/map_vector.h"

typedef enum TagType
{
    NORMAL,
    INFO,
    SELF_ENDED,
    STRING
} TagType;

class Block
{
protected:
    QString name;
    TagType tagType;

public:
    Block(QString name, TagType tagType);
    void setName(QString name);
    QString getName();
    void setTagType(TagType tagType);
    TagType getTagType();
    virtual QVector<Block *> *getValue() = 0;
    virtual Map<QString, QString> *getAttributes() = 0;
    virtual ~Block();
};

#endif /* BLOCK_H_ */
