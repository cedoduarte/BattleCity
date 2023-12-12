#include "tank.h"

#include "missile.h"

#include <QGraphicsScene>

Tank::Tank(QGraphicsItem *parent)
    : MovableItem(parent)
{
}

Tank::~Tank()
{
}

void Tank::shoot() const
{
    // todo... move misil, colisiones, etc...
    Missile *missile = new Missile;
    missile->setPos(200, 100);
    scene()->addItem(missile);
}
