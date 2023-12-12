#ifndef MISSILE_H
#define MISSILE_H

#include "movableitem.h"

class Missile : public MovableItem
{
public:
    explicit Missile(QGraphicsItem *parent = nullptr);
    virtual ~Missile();
protected:
    void loadImageFromResource() override;
    void setSpeed() override;
};

#endif // MISSILE_H
