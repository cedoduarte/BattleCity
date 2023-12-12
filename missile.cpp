#include "missile.h"

Missile::Missile(QGraphicsItem *parent)
    : MovableItem(parent)
{
    loadImageFromResource();
    setSpeed();
}

Missile::~Missile()
{
}

void Missile::loadImageFromResource()
{
    setPixmap(QPixmap(":/img/missile.png"));
}

void Missile::setSpeed()
{
    setSpeedX(10.0);
    setSpeedY(10.0);
}
