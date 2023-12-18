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
