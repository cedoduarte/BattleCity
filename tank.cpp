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

void Tank::shoot() const
{
    QSize tankSize = pixmap().size();
    QPointF tankPos = scenePos();
    Missile *missile = new Missile(m_tankType == PLAYER_TANK);
    QSize missileSize = missile->pixmap().size();
    QPointF missilePos;
    double dxMissile = 0.0;
    double dyMissile = 0.0;
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
    missilePos.rx() = tankPos.x() + dxMissile;
    missilePos.ry() = tankPos.y() + dyMissile;
    missile->setPos(missilePos);
    missile->setRotation(rotation());
    missile->directionRef() = m_direction;
    Scene::scene()->addMissile(missile);
}
