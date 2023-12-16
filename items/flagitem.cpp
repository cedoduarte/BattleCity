#include "flagitem.h"

FlagItem::FlagItem(QGraphicsItem *parent)
    : ImageItem(parent)
{
    loadImageFromResource();
}

FlagItem::~FlagItem()
{
}

void FlagItem::loadImageFromResource()
{
    setPixmap(QPixmap(":/img/flag.png"));
}
