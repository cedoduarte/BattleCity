#include "flagitem.h"

FlagItem::FlagItem(QGraphicsItem *parent)
    : ImageItem(parent)
{
    loadImageFromResource();
}

FlagItem::~FlagItem()
{
}
