#include "enemy.h"
#include "util.h"
#include "scene.h"
#include "player.h"
#include "brick.h"

#include <set>

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
    m_directionTimer->start(5000);

    m_shootTimer = new ShootTimer;
    m_shootTimer->setEnemy(this);
    m_shootTimer->start(2000);
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
    shoot();
}

void Enemy::changeDirectionAvoiding(int direction)
{
    std::vector<int> directions { NORTH, SOUTH, EAST, WEST };
    int i = 0;
    while (i < directions.size())
    {
        if (directions[i] == direction)
        {
            break;
        }
        i++;
    }
    auto it = directions.begin();
    std::advance(it, i);
    directions.erase(it);
    setDirection(Util::randomItem(directions));
}

void Enemy::changeDirectionIfNeeded(QGraphicsRectItem *boundaryRect, int direction)
{
    if (collidesWithItem(boundaryRect))
    {
        changeDirectionAvoiding(direction);
    }
    if (collidesWithItem(Player::player()))
    {
        changeDirectionAvoiding(direction);
    }
    std::set<Brick*> collidingBrickSet;
    for (Brick *brick : Scene::scene()->brickList())
    {
        if (collidesWithItem(brick))
        {
            collidingBrickSet.insert(brick);
        }
    }
    if (collidingBrickSet.size() > 0)
    {
        changeDirectionAvoiding(direction);
    }
}
