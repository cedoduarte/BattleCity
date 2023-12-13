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

void Missile::move()
{
    switch (m_direction)
    {
        case NORTH:
        {
            moveBy(0.0, -m_ySpeed);
            break;
        }
        case SOUTH:
        {
            moveBy(0.0, m_ySpeed);
            break;
        }
        case EAST:
        {
            moveBy(m_xSpeed, 0.0);
            break;
        }
        case WEST:
        {
            moveBy(-m_xSpeed, 0.0);
            break;
        }
    }
}

void Missile::loadImageFromResource()
{
    setPixmap(QPixmap(":/img/missile.png"));
}

void Missile::setSpeed()
{
    setSpeedX(20.0);
    setSpeedY(20.0);
}
