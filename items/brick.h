#ifndef BRICK_H
#define BRICK_H

#include <QGraphicsRectItem>

class Brick : public QGraphicsRectItem
{
public:
    explicit Brick(QGraphicsItem *parent = nullptr);
    virtual ~Brick();
};

#endif // BRICK_H
