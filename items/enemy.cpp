#include "enemy.h"
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
    createThreads();
}

Enemy::~Enemy()
{
    m_directionThread->terminate();
    m_directionThread->deleteLater();

    m_shootThread->terminate();
    m_shootThread->deleteLater();
}

void Enemy::createThreads()
{
    m_directionThread = new DirectionThread;
    m_directionThread->setEnemy(this);
    DirectionThread::connect(m_directionThread,
                             &DirectionThread::timeOut,
                             m_directionThread,
                             &DirectionThread::onTimeOut,
                             Qt::QueuedConnection);
    m_directionThread->start(QThread::NormalPriority);

    m_shootThread = new ShootThread;
    m_shootThread->setEnemy(this);
    ShootThread::connect(m_shootThread,
                         &ShootThread::timeOut,
                         m_shootThread,
                         &ShootThread::onTimeOut,
                         Qt::QueuedConnection);
    m_shootThread->start(QThread::NormalPriority);
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

void Enemy::setSpeed()
{
    setSpeedX(s_tankSpeed);
    setSpeedY(s_tankSpeed);
}

void DirectionThread::run()
{
    while (true)
    {
        emit timeOut();
        msleep(5000);
    }
}

void ShootThread::run()
{
    while (true)
    {
        emit timeOut();
        msleep(3000);
    }
}

