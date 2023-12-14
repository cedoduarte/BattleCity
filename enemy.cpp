#include "enemy.h"

double Enemy::s_tankSpeed = 3.0;
double Enemy::s_tankMissileSpeed = 20.0;

Enemy::Enemy(QGraphicsItem *parent)
    : Tank(parent)
{
    loadImageFromResource();
    setSpeed();
    setLifes();
    setTankType();
    setShootSpeed();
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
    setSpeedX(s_tankSpeed);
    setSpeedY(s_tankSpeed);
}

void Enemy::setLifes()
{
    setLifeCount(1);
}

void Enemy::setTankType()
{
    m_tankType = ENEMY_TANK;
}

void Enemy::setShootSpeed()
{
    setMissileSpeed(s_tankMissileSpeed);
}
