#include "scene.h"
#include "player.h"
#include "enemy.h"
#include "missile.h"
#include "mousetracker.h"
#include "playerhud.h"
#include "enemyhud.h"
#include "keyhud.h"
#include "flagitem.h"

#include <QTimer>
#include <vector>
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsProxyWidget>

Scene* Scene::s_scene = nullptr;

Scene::Scene(const QRectF &sceneRect, QObject *parent)
    : QGraphicsScene(parent)
{
    setBackgroundBrush(QBrush(QColor(0x100000)));
    setSceneRect(sceneRect);
    QColor sceneColor(0x403c3b);
    addRect(sceneRect, QPen(sceneColor), QBrush(sceneColor));

    m_topRect = addRect(0.0, -10.0, 800.0, 10.0, QPen(sceneColor), QBrush(sceneColor));
    m_bottomRect = addRect(0.0, 600.0, 800.0, 10.0, QPen(sceneColor), QBrush(sceneColor));
    m_leftRect = addRect(-10.0, 0.0, 10.0, 600.0, QPen(sceneColor), QBrush(sceneColor));
    m_rightRect = addRect(800.0, 0.0, 10.0, 600.0, QPen(sceneColor), QBrush(sceneColor));

    m_mouseTrackerProxy = addWidget(new MouseTracker);
    m_mouseTrackerProxy->setPos(-150.0, 0.0);

    m_playerHUDProxy = addWidget(new PlayerHUD);
    m_playerHUDProxy->setPos(-280.0, 100.0);

    m_enemyHUDProxy = addWidget(new EnemyHUD);
    m_enemyHUDProxy->setPos(-280.0, 266.0);

    m_keyHUDProxy = addWidget(new KeyHUD);
    m_keyHUDProxy->setPos(826.0, 0.0);

    m_upKey = NameKey::getNameKey(Qt::Key_Up);
    m_downKey = NameKey::getNameKey(Qt::Key_Down);
    m_leftKey = NameKey::getNameKey(Qt::Key_Left);
    m_rightKey = NameKey::getNameKey(Qt::Key_Right);
    m_shootKey = NameKey::getNameKey(Qt::Key_X);

    m_player = new Player;
    Player::setPlayer(m_player);
    m_player->setPos(310.0, 555.0);
    addItem(m_player);

    m_flagItem = new FlagItem;
    m_flagItem->setPos(350.0, 540.0);
    addItem(m_flagItem);

    Enemy *enemy = new Enemy;
    enemy->setPos(100, 100);
    m_enemyList.push_back(enemy);
    addItem(enemy);

    enemy = new Enemy;
    enemy->setPos(60, 80);
    m_enemyList.push_back(enemy);
    addItem(enemy);

    enemy = new Enemy;
    enemy->setPos(200, 140);
    m_enemyList.push_back(enemy);
    addItem(enemy);

    enemy = new Enemy;
    enemy->setPos(400, 100);
    m_enemyList.push_back(enemy);
    addItem(enemy);

    enemy = new Enemy;
    enemy->setPos(740, 100);
    m_enemyList.push_back(enemy);
    addItem(enemy);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &Scene::timeOut);
}

Scene::~Scene()
{
}

void Scene::addMissile(Missile *missile)
{
    addItem(missile);
    m_missileList.push_back(missile);
}

void Scene::removeMissile(Missile *missile)
{
    m_missileList.remove(missile);
    removeItem(missile);
    delete missile;
}

void Scene::loadHUDs()
{
    dynamic_cast<PlayerHUD*>(m_playerHUDProxy->widget())->loadData();
    dynamic_cast<EnemyHUD*>(m_enemyHUDProxy->widget())->loadData();
    dynamic_cast<KeyHUD*>(m_keyHUDProxy->widget())->loadData();
}

void Scene::startTimer(int msecs)
{
    m_timer->start(msecs);
}

std::list<Enemy*> Scene::getEnemySiblings(Enemy *enemy) const
{
    std::list<Enemy*> siblings;
    for (Enemy *sibling : m_enemyList)
    {
        if (sibling != enemy)
        {
            siblings.push_back(sibling);
        }
    }
    return siblings;
}

std::list<Missile *> Scene::getEnemyMissileList() const
{
    std::list<Missile*> enemyMissileList;
    for (Missile *missile : m_missileList)
    {
        if (!missile->shootedByPlayer())
        {
            enemyMissileList.push_back(missile);
        }
    }
    return enemyMissileList;
}

void Scene::timeOut()
{
    // collisions between missiles and bounds
    auto missileIt = m_missileList.begin();
    while (missileIt != m_missileList.end())
    {
        if ((**missileIt).collidesWithItem(m_topRect)
            || (**missileIt).collidesWithItem(m_bottomRect)
            || (**missileIt).collidesWithItem(m_leftRect)
            || (**missileIt).collidesWithItem(m_rightRect))
        {
            removeItem(*missileIt);
            delete *missileIt;
            missileIt = m_missileList.erase(missileIt);
        }
        else
        {
            missileIt++;
        }
    }

    // collisions between player's missiles and enemies
    auto collisionMap = getCollisionMapWithEnemies();
    for (auto it = collisionMap.begin(); it != collisionMap.end(); it++)
    {
        removeItem(it->first);
        removeItem(it->second);
        m_missileList.remove(it->first);
        m_enemyList.remove(it->second);
        delete it->first;
        delete it->second;
    }

    // collision between enemies' missiles and player
    for (Missile *missile : getEnemyMissileList())
    {
        if (missile->collidesWithItem(m_player))
        {
            removeItem(missile);
            m_missileList.remove(missile);
            delete missile;
            // todo... quitar una vida al player y moverlo a la posición inicial
        }
    }

    // player collides with bounds
    m_player->setMoveUpEnabled(!m_player->collidesWithItem(m_topRect));
    m_player->setMoveDownEnabled(!m_player->collidesWithItem(m_bottomRect));
    m_player->setMoveLeftEnabled(!m_player->collidesWithItem(m_leftRect));
    m_player->setMoveRightEnabled(!m_player->collidesWithItem(m_rightRect));

    // enemies are moved
    for (Enemy *enemy : m_enemyList)
    {
        switch (enemy->direction())
        {
            case MovableItem::NORTH:
            {
                enemy->moveUp();
                enemy->changeDirectionIfNeeded(m_topRect, MovableItem::NORTH);
                break;
            }
            case MovableItem::SOUTH:
            {
                enemy->moveDown();
                enemy->changeDirectionIfNeeded(m_bottomRect, MovableItem::SOUTH);
                break;
            }
            case MovableItem::EAST:
            {
                enemy->moveRight();
                enemy->changeDirectionIfNeeded(m_rightRect, MovableItem::EAST);
                break;
            }
            case MovableItem::WEST:
            {
                enemy->moveLeft();
                enemy->changeDirectionIfNeeded(m_leftRect, MovableItem::WEST);
                break;
            }
        }
    }

    // missiles are moved
    for (Missile *missile : m_missileList)
    {
        missile->move();
    }
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    const int key = event->key();
    if (m_upKey.match(key))
    {
        m_player->moveUp();
    }
    else if (m_downKey.match(key))
    {
        m_player->moveDown();
    }
    else if (m_leftKey.match(key))
    {
        m_player->moveLeft();
    }
    else if (m_rightKey.match(key))
    {
        m_player->moveRight();
    }
    else if (m_shootKey.match(key))
    {
        m_player->shoot();
    }
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    dynamic_cast<MouseTracker*>(m_mouseTrackerProxy->widget())->display(event->scenePos());
    QGraphicsScene::mouseMoveEvent(event);
}

std::map<Missile*, Enemy*> Scene::getCollisionMapWithEnemies() const
{
    std::map<Missile*, Enemy*> collisionMap;
    std::vector<Missile*> playerMissileList;
    for (Missile *missile : m_missileList)
    {
        if (missile->shootedByPlayer())
        {
            playerMissileList.push_back(missile);
        }
    }
    for (Missile *missile : playerMissileList)
    {
        for (Enemy *enemy : m_enemyList)
        {
            if (missile->collidesWithItem(enemy))
            {
                collisionMap[missile] = enemy;
            }
        }
    }
    return collisionMap;
}
