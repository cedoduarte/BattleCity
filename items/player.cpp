#include "player.h"

Player* Player::s_player = nullptr;

Player::Player(QGraphicsItem *parent)
    : Tank(parent)
{
    loadImageFromResource();
    setSpeed();
    setLifes();
    setTankType();
    setShootSpeed();
}

Player::~Player()
{
}

void Player::addLife()
{
    m_lifeCount++;
}

void Player::reduceLife()
{
    m_lifeCount--;
}

void Player::loadImageFromResource()
{
    setPixmap(QPixmap(":/img/player.png"));
}

void Player::setSpeed()
{
    setSpeedX(5.0);
    setSpeedY(5.0);
}

void Player::setLifes()
{
    setLifeCount(3);
}

void Player::setTankType()
{
    m_tankType = PLAYER_TANK;
}

void Player::setShootSpeed()
{
    setMissileSpeed(20.0);
}
