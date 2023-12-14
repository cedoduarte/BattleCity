#ifndef ENEMY_H
#define ENEMY_H

#include "tank.h"

class Enemy : public Tank
{
public:
    explicit Enemy(QGraphicsItem *parent = nullptr);
    virtual ~Enemy();
    static double tankSpeed() { return s_tankSpeed; }
    static void setTankSpeed(double speed) { s_tankSpeed = speed; }
    static double tankMissileSpeed() { return s_tankMissileSpeed; }
    static void setTankMissileSpeed(double speed) { s_tankMissileSpeed = speed; }
protected:
    void loadImageFromResource() override;
    void setSpeed() override;
    void setLifes() override;
    void setTankType() override;
    void setShootSpeed() override;
private:
    static double s_tankSpeed;
    static double s_tankMissileSpeed;
};

#endif // ENEMY_H
