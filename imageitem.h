#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include <QGraphicsPixmapItem>

class ImageItem : public QGraphicsPixmapItem
{
public:
    explicit ImageItem(QGraphicsItem *parent = nullptr);
    virtual ~ImageItem();
protected:
    virtual void loadImageFromResource() = 0;
};

#endif // IMAGEITEM_H
