#ifndef TANK_H
#define TANK_H

#include "movableitem.h"

class Tank : public MovableItem
{
public:
    explicit Tank(QGraphicsItem *parent = nullptr);
    virtual ~Tank();
    void shoot() const;
};

#endif // TANK_H
