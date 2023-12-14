#include "enemy.h"
#include "util.h"

double Enemy::s_tankSpeed = 5.0;
double Enemy::s_tankMissileSpeed = 20.0;

Enemy::Enemy(QGraphicsItem *parent)
    : Tank(parent)
{
    loadImageFromResource();
    setSpeed();
    setLifes();
    setTankType();
    setShootSpeed();

    m_directionTimer = new DirectionTimer;
    m_directionTimer->setEnemy(this);
    m_directionTimer->start(1500); // cambia de dirección cada segundo y medio

    m_shootTimer = new ShootTimer;
    m_shootTimer->setEnemy(this);
    m_shootTimer->start();
}

Enemy::~Enemy()
{
    delete m_directionTimer;
    delete m_shootTimer;
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

void Enemy::changeDirection()
{
    setDirection(Util::randomItem({ NORTH, SOUTH, EAST, WEST }));
}

void Enemy::onShootTimeOut()
{
// todo...
}
