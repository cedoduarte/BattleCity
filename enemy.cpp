#include "enemy.h"

Enemy::Enemy(QGraphicsItem *parent)
    : Tank(parent)
{
    loadImageFromResource();
    setSpeed();
}

Enemy::~Enemy()
{
}

void Enemy::loadImageFromResource()
{
    setPixmap(QPixmap(":/img/enemy.png"));
}

void Enemy::setSpeed()
{
    setSpeedX(3.0);
    setSpeedY(3.0);
}
