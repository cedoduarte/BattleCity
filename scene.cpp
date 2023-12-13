#include "scene.h"

#include "player.h"
#include "enemy.h"
#include "missile.h"

#include <QTimer>
#include <QKeyEvent>

Scene::Scene(const QSize &size, QObject *parent)
    : QGraphicsScene(parent)
{

    QRectF rect;
    rect.setX(0.0);
    rect.setY(0.0);
    rect.setSize(size);
    setSceneRect(rect);

    m_player = new Player;
    m_player->setPos(50, 50);

    Enemy *enemy = new Enemy;
    enemy->setPos(100, 100);

    addItem(m_player);
    addItem(enemy);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &Scene::timeOut);

    m_timer->start(50);
}

Scene::~Scene()
{
}

void Scene::addMissile(Missile *missile)
{
    addItem(missile);
    m_missileList.push_back(missile);
}

void Scene::timeOut()
{
    for (Missile *missile : m_missileList)
    {
        missile->move();
    }
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Left:
        {
            m_player->moveLeft();
            break;
        }
        case Qt::Key_Right:
        {
            m_player->moveRight();
            break;
        }
        case Qt::Key_Up:
        {
            m_player->moveUp();
            break;
        }
        case Qt::Key_Down:
        {
            m_player->moveDown();
            break;
        }
        case Qt::Key_X:
        {
            m_player->shoot();
            break;
        }
    }
}
