#include "tank.h"
#include "missile.h"
#include "scene.h"

Tank::Tank(QGraphicsItem *parent)
    : MovableItem(parent)
{
}

Tank::~Tank()
{
}

void Tank::compute_dx_dy(double &dxMissile, double &dyMissile, const QSize &tankSize, const QSize &missileSize) const
{
    switch (m_direction)
    {
        case NORTH:
        {
            dxMissile = tankSize.width()*0.5 - missileSize.width()*0.5;
            dyMissile = tankSize.height()*0.5 - missileSize.height()*0.5;
            break;
        }
        case SOUTH:
        {
            dxMissile = tankSize.width()*0.5 - missileSize.width()*2.75;
            dyMissile = tankSize.height()*0.5 - missileSize.height()*0.5;
            break;
        }
        case EAST:
        {
            dxMissile = tankSize.width()*0.5 - missileSize.width()*0.5;
            dyMissile = tankSize.height()*0.5 - missileSize.height()*0.15;
            break;
        }
        case WEST:
        {
            dxMissile = tankSize.width()*0.5 - missileSize.width()*1.3;
            dyMissile = tankSize.height()*0.5 - missileSize.height()*0.75;
            break;
        }
    }
}

void Tank::shoot() const
{    
    Missile *missile = new Missile(m_tankType == PLAYER_TANK);
    missile->setSpeedX(m_missileSpeed);
    missile->setSpeedY(m_missileSpeed);    
    double dxMissile = 0.0, dyMissile = 0.0;
    compute_dx_dy(dxMissile, dyMissile, pixmap().size(), missile->pixmap().size());
    QPointF tankPos = scenePos();
    QPointF missilePos;
    missilePos.rx() = tankPos.x() + dxMissile;
    missilePos.ry() = tankPos.y() + dyMissile;
    missile->setPos(missilePos);
    missile->setRotation(rotation());
    missile->directionRef() = m_direction;
    Scene::scene()->addMissile(missile);
}
