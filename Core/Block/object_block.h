#ifndef OBJECT_BLOCK_H_
#define OBJECT_BLOCK_H_

#include "block.h"
#include "../../Data_Structures/map_vector.h"
#include <QString>
#include <QVector>

class ObjectBlock : public Block
{
private:
    QVector<Block *> *blocks;
    Map<QString, QString> *attributes;

public:
    ObjectBlock(QString name, TagType tagType);
    virtual QVector<Block *> *getValue();
    virtual Map<QString, QString> *getAttributes();
    void addBlock(Block *blockPtr);
    virtual ~ObjectBlock();
};

#endif /* OBJECT_BLOCK_H_ */
