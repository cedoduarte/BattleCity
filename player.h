#ifndef PLAYER_H
#define PLAYER_H

#include "tank.h"

class Player : public Tank
{
public:
    explicit Player(QGraphicsItem *parent = nullptr);
    virtual ~Player();
protected:
    void loadImageFromResource() override;
    void setSpeed() override;
};

#endif // PLAYER_H
