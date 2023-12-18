#ifndef ENEMY_H
#define ENEMY_H

#include "tank.h"
#include "util.h"

#include <QThread>

class DirectionThread;
class ShootThread;

class Enemy : public Tank
{
public:
    explicit Enemy(QGraphicsItem *parent = nullptr);
    virtual ~Enemy();
    static double tankSpeed() { return s_tankSpeed; }
    static void setTankSpeed(double speed) { s_tankSpeed = speed; }
    static double tankMissileSpeed() { return s_tankMissileSpeed; }
    static void setTankMissileSpeed(double speed) { s_tankMissileSpeed = speed; }
    void changeDirection() { setDirection(Util::randomItem({ NORTH, SOUTH, EAST, WEST })); }
    void changeDirectionAvoiding(int direction);
    void changeDirectionIfNeeded(QGraphicsRectItem *boundaryRect, int direction);
    void updateSpeed() { setSpeed(); }
    void updateShootSpeed() { setShootSpeed(); }
protected:
    void loadImageFromResource() override { setPixmap(QPixmap(":/img/enemy.png")); }
    void setSpeed() override {
        setSpeedX(s_tankSpeed);
        setSpeedY(s_tankSpeed);
    }
    void setLifes() override { setLifeCount(1); }
    void setTankType() override { m_tankType = ENEMY_TANK; }
    void setShootSpeed() override { setMissileSpeed(s_tankMissileSpeed); }
private:
    void createThreads();

    DirectionThread *m_directionThread;
    ShootThread *m_shootThread;
    static double s_tankSpeed;
    static double s_tankMissileSpeed;
};

class DirectionThread : public QThread
{
    Q_OBJECT
public:
    explicit DirectionThread(QObject *parent = nullptr) : QThread(parent) {}
    virtual ~DirectionThread() {}
    void setEnemy(Enemy *enemy) { m_enemy = enemy; }
signals:
    void timeOut();
public slots:
    void onTimeOut() { m_enemy->changeDirection(); }
protected:
    void run() override;
private:
    Enemy *m_enemy;
};

class ShootThread : public QThread
{
    Q_OBJECT
public:
    explicit ShootThread(QObject *parent = nullptr) : QThread(parent) {}
    virtual ~ShootThread() {}
    void setEnemy(Enemy *enemy) { m_enemy = enemy; }
signals:
    void timeOut();
public slots:
    void onTimeOut() { m_enemy->shoot(); }
protected:
    void run() override;
private:
    Enemy *m_enemy;
};

#endif // ENEMY_H
