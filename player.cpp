#include "player.h"

Player::Player(QGraphicsItem *parent)
    : Tank(parent)
{
    loadImageFromResource();
    setSpeed();
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
