#ifndef ENEMY_H
#define ENEMY_H

#include "tank.h"

#include <QTimer>

class DirectionTimer;
class ShootTimer;

class Enemy : public Tank
{
public:
    explicit Enemy(QGraphicsItem *parent = nullptr);
    virtual ~Enemy();
    static double tankSpeed() { return s_tankSpeed; }
    static void setTankSpeed(double speed) { s_tankSpeed = speed; }
    static double tankMissileSpeed() { return s_tankMissileSpeed; }
    static void setTankMissileSpeed(double speed) { s_tankMissileSpeed = speed; }
    void changeDirection();
    void onShootTimeOut();
    void changeDirectionAvoiding(int direction);
    void changeDirectionIfNeeded(QGraphicsRectItem *boundaryRect, int direction);
    void updateSpeed() { setSpeed(); }
    void updateShootSpeed() { setShootSpeed(); }
protected:
    void loadImageFromResource() override;
    void setSpeed() override;
    void setLifes() override;
    void setTankType() override;
    void setShootSpeed() override;
private:
    DirectionTimer *m_directionTimer;
    ShootTimer *m_shootTimer;
    static double s_tankSpeed;
    static double s_tankMissileSpeed;
};

class DirectionTimer : public QTimer
{
    Q_OBJECT
public:
    explicit DirectionTimer(QObject *parent = nullptr) : QTimer(parent) {
        connect(this, &DirectionTimer::timeout, this, &DirectionTimer::onTimeOut);
    }
    virtual ~DirectionTimer() {}
    void setEnemy(Enemy *enemy) { m_enemy = enemy; }
public slots:
    void onTimeOut() { m_enemy->changeDirection(); }
private:
    Enemy *m_enemy;
};

class ShootTimer : public QTimer
{
    Q_OBJECT
public:
    explicit ShootTimer(QObject *parent = nullptr) : QTimer(parent) {
        connect(this, &ShootTimer::timeout, this, &ShootTimer::onTimeOut);
    }
    virtual ~ShootTimer() {}
    void setEnemy(Enemy *enemy) { m_enemy = enemy; }
public slots:
    void onTimeOut() { m_enemy->onShootTimeOut(); }
private:
    Enemy *m_enemy;
};

#endif // ENEMY_H
