#ifndef BRICK_H
#define BRICK_H

#include <QGraphicsRectItem>
#include <list>

class Brick : public QGraphicsRectItem
{
public:
    explicit Brick(QGraphicsItem *parent = nullptr);
    virtual ~Brick();
    static std::list<Brick*> createBrickSet(double x, double y, int rows, int columns);
};

#endif // BRICK_H
