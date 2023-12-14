#include "scene.h"
#include "player.h"
#include "enemy.h"
#include "missile.h"
#include "mousetracker.h"
#include "playerhud.h"
#include "enemyhud.h"
#include "keyhud.h"

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
    setSceneRect(sceneRect);
    addRect(sceneRect);

    m_topRect = addRect(0.0, -10.0, 800.0, 10.0);
    m_bottomRect = addRect(0.0, 600.0, 800.0, 10.0);
    m_leftRect = addRect(-10.0, 0.0, 10.0, 600.0);
    m_rightRect = addRect(800.0, 0.0, 10.0, 600.0);

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

    m_player->setPos(50, 50);
    addItem(m_player);

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

    for (Missile *missile : m_missileList)
    {
        missile->move();
    }
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    const int key = event->key();
    if (key == m_upKey.code())
    {
        m_player->moveUp();
    }
    else if (key == m_downKey.code())
    {
        m_player->moveDown();
    }
    else if (key == m_leftKey.code())
    {
        m_player->moveLeft();
    }
    else if (key == m_rightKey.code())
    {
        m_player->moveRight();
    }
    else if (key == m_shootKey.code())
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
