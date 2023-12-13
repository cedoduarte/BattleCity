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
protected:
    virtual void setLifes() = 0;
    virtual void setTankType() = 0;

    int m_lifeCount;
    TankType m_tankType;
};

#endif // TANK_H
