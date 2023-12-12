#ifndef ENEMY_H
#define ENEMY_H

#include "tank.h"

class Enemy : public Tank
{
public:
    explicit Enemy(QGraphicsItem *parent = nullptr);
    virtual ~Enemy();
protected:
    void loadImageFromResource() override;
    void setSpeed() override;
};

#endif // ENEMY_H
