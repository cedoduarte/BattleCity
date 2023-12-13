#include "player.h"

Player* Player::s_player = nullptr;

Player::Player(QGraphicsItem *parent)
    : Tank(parent)
{
    loadImageFromResource();
    setSpeed();
    setLifes();
    setTankType();
}

Player::~Player()
{
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
