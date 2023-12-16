#ifndef TANK_H
#define TANK_H

#include "movableitem.h"

class Tank : public MovableItem
{
public:
    enum TankType
    {
        PLAYER_TANK,
        ENEMY_TANK
    };

    explicit Tank(QGraphicsItem *parent = nullptr);
    virtual ~Tank();
    void shoot() const;
    int lifeCount() const { return m_lifeCount; }
    void setLifeCount(int lifeCount) { m_lifeCount = lifeCount; }
    int missileSpeed() const { return m_missileSpeed; }
    void setMissileSpeed(int speed) { m_missileSpeed = speed; }
protected:
    virtual void setLifes() = 0;
    virtual void setTankType() = 0;
    virtual void setShootSpeed() = 0;

    int m_lifeCount;
    TankType m_tankType;
    int m_missileSpeed;
};

#endif // TANK_H
