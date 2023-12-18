#ifndef PLAYER_H
#define PLAYER_H

#include "tank.h"

class Player : public Tank
{
public:
    explicit Player(QGraphicsItem *parent = nullptr);
    virtual ~Player();
    static Player* player() { return s_player; }
    static void setPlayer(Player *player) { s_player = player; }
    void addLife() { m_lifeCount++; }
    void reduceLife() { m_lifeCount--; }
protected:
    void loadImageFromResource() override { setPixmap(QPixmap(":/img/player.png")); }
    void setSpeed() override {
        setSpeedX(10.0);
        setSpeedY(10.0);
    }
    void setLifes() override { setLifeCount(3); }
    void setTankType() override { m_tankType = PLAYER_TANK; }
    void setShootSpeed() override { setMissileSpeed(20.0); }
private:
    static Player *s_player;
};

#endif // PLAYER_H
