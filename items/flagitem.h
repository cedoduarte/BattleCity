#ifndef FLAGITEM_H
#define FLAGITEM_H

#include "imageitem.h"

class FlagItem : public ImageItem
{
public:
    explicit FlagItem(QGraphicsItem *parent = nullptr);
    virtual ~FlagItem();
protected:
    void loadImageFromResource() override { setPixmap(QPixmap(":/img/flag.png")); }
};

#endif // FLAGITEM_H
