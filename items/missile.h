#ifndef MISSILE_H
#define MISSILE_H

#include "movableitem.h"

class Missile : public MovableItem
{
public:
    explicit Missile(bool shootedByPlayer, QGraphicsItem *parent = nullptr);
    virtual ~Missile();
    void move();
    int& directionRef() { return m_direction; }
    void setShootedByPlayer(bool shootedByPlayer) { m_shootedByPlayer = shootedByPlayer; }
    bool shootedByPlayer() const { return m_shootedByPlayer; }
protected:
    void loadImageFromResource() override { setPixmap(QPixmap(":/img/missile.png")); }
    void setSpeed() override {
        setSpeedX(20.0);
        setSpeedY(20.0);
    }
private:
    bool m_shootedByPlayer;
};

#endif // MISSILE_H
