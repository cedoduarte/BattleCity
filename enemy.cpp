#include "enemy.h"

Enemy::Enemy(QGraphicsItem *parent)
    : Tank(parent)
{
    loadImageFromResource();
    setSpeed();
    setLifes();
    setTankType();
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

void Enemy::setLifes()
{
    setLifeCount(1);
}

void Enemy::setTankType()
{
    m_tankType = ENEMY_TANK;
}
