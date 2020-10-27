#ifndef STRING_BLOCK_H_
#define STRING_BLOCK_H_

#include "block.h"
#include <QString>
#include <QVector>

class StringBlock : public Block
{
public:
    StringBlock(QString name);
    virtual QVector<Block *> *getValue();
    virtual Map<QString, QString> *getAttributes();
    virtual ~StringBlock();
};

#endif /* STRING_BLOCK_H_ */
