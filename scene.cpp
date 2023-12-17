#include "scene.h"
#include "mousetracker.h"
#include "items/player.h"
#include "items/enemy.h"
#include "items/missile.h"
#include "items/flagitem.h"
#include "items/brick.h"
#include "huds/playerhud.h"
#include "huds/enemyhud.h"
#include "huds/keyhud.h"

#include <set>
#include <QTimer>
#include <vector>
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsProxyWidget>
#include <QSoundEffect>

Scene* Scene::s_scene = nullptr;

Scene::Scene(const QRectF &sceneRect, QObject *parent)
    : QGraphicsScene(parent)
{
    init(sceneRect);
}

Scene::~Scene()
{
    delete m_shootSound;
    delete m_boomSound;
    delete m_boomSound2;
    delete m_backgroundSound;
}

void Scene::init(const QRectF &sceneRect)
{
    QColor sceneColor = setupScene(sceneRect);
    createBounds(sceneColor);
    createHUDs();
    createKeys();
    createPlayer();
    createEnemies();
    createFlagItem();
    createBrickBlocks();    
    createSoundEffects();
    createTimer();
}

void Scene::createSoundEffects()
{
    m_shootSound = new QSoundEffect;
    m_shootSound->setSource(QUrl("qrc:/wav/shoot.wav"));
    m_shootSound->setVolume(0.25f);

    m_boomSound = new QSoundEffect;
    m_boomSound->setSource(QUrl("qrc:/wav/boom.wav"));
    m_boomSound->setVolume(0.25f);

    m_boomSound2 = new QSoundEffect;
    m_boomSound2->setSource(QUrl("qrc:/wav/boom2.wav"));
    m_boomSound2->setVolume(0.25f);

    m_backgroundSound = new QSoundEffect;
    m_backgroundSound->setSource(QUrl("qrc:/wav/background.wav"));
    m_backgroundSound->setLoopCount(QSoundEffect::Infinite);
    m_backgroundSound->setVolume(0.25f);
    m_backgroundSound->play();
}

void Scene::createBrickBlocks()
{
    addBrickSet(Brick::createBrickSet(300.0, 527.0, 12, 3));
    addBrickSet(Brick::createBrickSet(415.0, 527.0, 12, 3));
    addBrickSet(Brick::createBrickSet(330.0, 527.0, 3, 9));
    addBrickSet(Brick::createBrickSet(14.0, 50.0, 10, 75));
    addBrickSet(Brick::createBrickSet(350.0, 100.0, 80, 5));
    addBrickSet(Brick::createBrickSet(14.0, 200.0, 10, 75));
    addBrickSet(Brick::createBrickSet(14.0, 350.0, 10, 75));
}

void Scene::createEnemies()
{
    m_enemyCount = 20;

    Enemy *enemy = new Enemy;
    enemy->setPos(0.0, 0.0);
    m_enemyList.push_back(enemy);
    addItem(enemy);
    m_enemyCount--;

    enemy = new Enemy;
    enemy->setPos(350.0, 0.0);
    m_enemyList.push_back(enemy);
    addItem(enemy);
    m_enemyCount--;

    enemy = new Enemy;
    enemy->setPos(730.0, 0.0);
    m_enemyList.push_back(enemy);
    addItem(enemy);
    m_enemyCount--;
}

void Scene::createKeys()
{
    m_upKey = NameKey::getNameKey(Qt::Key_Up);
    m_downKey = NameKey::getNameKey(Qt::Key_Down);
    m_leftKey = NameKey::getNameKey(Qt::Key_Left);
    m_rightKey = NameKey::getNameKey(Qt::Key_Right);
    m_shootKey = NameKey::getNameKey(Qt::Key_X);
}

void Scene::createHUDs()
{
    m_mouseTrackerProxy = addWidget(new MouseTracker);
    m_mouseTrackerProxy->setPos(-150.0, 0.0);

    m_playerHUDProxy = addWidget(new PlayerHUD);
    m_playerHUDProxy->setPos(-280.0, 100.0);

    m_enemyHUDProxy = addWidget(new EnemyHUD);
    m_enemyHUDProxy->setPos(-280.0, 266.0);

    m_keyHUDProxy = addWidget(new KeyHUD);
    m_keyHUDProxy->setPos(826.0, 0.0);
}

void Scene::createBounds(QColor sceneColor)
{
    m_topRect = addRect(0.0, -10.0, 800.0, 10.0, QPen(sceneColor), QBrush(sceneColor));
    m_bottomRect = addRect(0.0, 600.0, 800.0, 10.0, QPen(sceneColor), QBrush(sceneColor));
    m_leftRect = addRect(-10.0, 0.0, 10.0, 600.0, QPen(sceneColor), QBrush(sceneColor));
    m_rightRect = addRect(800.0, 0.0, 10.0, 600.0, QPen(sceneColor), QBrush(sceneColor));
}

QColor Scene::setupScene(const QRectF &sceneRect)
{
    setBackgroundBrush(QColor(0x100000));
    setSceneRect(sceneRect);
    QColor sceneColor(0x403c3b);
    addRect(sceneRect, QPen(sceneColor), QBrush(sceneColor));
    return sceneColor;
}

void Scene::createPlayer()
{
    m_player = new Player;
    Player::setPlayer(m_player);
    m_player->setPos(250.0, 550.0);
    addItem(m_player);
}

void Scene::createFlagItem()
{
    m_flagItem = new FlagItem;
    m_flagItem->setPos(350.0, 550.0);
    addItem(m_flagItem);
}

void Scene::createTimer()
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &Scene::timeOut);
}

void Scene::addMissile(Missile *missile)
{
    addItem(missile);
    m_missileList.push_back(missile);
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

std::list<Missile *> Scene::getPlayerMissileList() const
{
    std::list<Missile*> playerMissileList;
    for (Missile *missile : m_missileList)
    {
        if (missile->shootedByPlayer())
        {
            playerMissileList.push_back(missile);
        }
    }
    return playerMissileList;
}

void Scene::addBrickSet(const std::list<Brick *> &brickSet)
{
    for (Brick *brick : brickSet)
    {
        addItem(brick);
        m_brickList.push_back(brick);
    }
}

void Scene::moveMissiles()
{
    for (Missile *missile : m_missileList)
    {
        missile->move();
    }
}

void Scene::collitionsBetweenMissilesAndBounds()
{
    std::set<Missile*> missileToBeDeleted1;
    for (Missile *missile : m_missileList)
    {
        if (missile->collidesWithItem(m_topRect)
            || missile->collidesWithItem(m_bottomRect)
            || missile->collidesWithItem(m_leftRect)
            || missile->collidesWithItem(m_rightRect))
        {
            missileToBeDeleted1.insert(missile);
        }
    }
    for (Missile *missile : missileToBeDeleted1)
    {
        removeItem(missile);
        m_missileList.remove(missile);
        delete missile;
    }
}

void Scene::collisionsBetweenMissilesAndBricks()
{
    std::set<Missile*> missileToBeDeleted2;
    std::set<Brick*> brickToBeDeleted;
    for (Missile *missile : m_missileList)
    {
        for (Brick *brick : m_brickList)
        {
            if (missile->collidesWithItem(brick))
            {
                missileToBeDeleted2.insert(missile);
                brickToBeDeleted.insert(brick);
            }
        }
    }
    for (Missile *missile : missileToBeDeleted2)
    {
        removeItem(missile);
        m_missileList.remove(missile);
        delete missile;
    }
    for (Brick *brick : brickToBeDeleted)
    {
        removeItem(brick);
        m_brickList.remove(brick);
        delete brick;
    }
}

void Scene::collisionsBetweenMissiles()
{
    std::set<Missile*> missileToBeDeleted3;
    for (Missile *enemyMissile : getEnemyMissileList())
    {
        for (Missile *playerMissile : getPlayerMissileList())
        {
            if (playerMissile->collidesWithItem(enemyMissile))
            {
                missileToBeDeleted3.insert(playerMissile);
                missileToBeDeleted3.insert(enemyMissile);
            }
        }
    }
    for (Missile *missile : missileToBeDeleted3)
    {
        removeItem(missile);
        m_missileList.remove(missile);
        delete missile;
    }
}

void Scene::collisionsBetweenMissilesAndEnemies()
{
    auto collisionMap = getCollisionMapWithEnemies();
    for (auto it = collisionMap.begin(); it != collisionMap.end(); it++)
    {
        removeItem(it->first);
        m_missileList.remove(it->first);
        delete it->first;

        removeItem(it->second);
        m_enemyList.remove(it->second);
        delete it->second;

        m_boomSound->play();
    }
}

void Scene::collisionsBetweenMissilesAndPlayerAndFlag()
{
    bool gameOver = false;
    for (Missile *missile : getEnemyMissileList())
    {
        if (missile->collidesWithItem(m_player))
        {
            removeItem(missile);
            m_missileList.remove(missile);
            delete missile;
            m_boomSound2->play();

            m_player->reduceLife();
            dynamic_cast<PlayerHUD*>(m_playerHUDProxy->widget())->loadData();
            m_player->setPos(250.0, 550.0);
            m_player->setDirection(MovableItem::NORTH);
            if (m_player->lifeCount() == 0)
            {
                gameOver = true;
                break;
            }
        }
    }
    for (Missile *missile : m_missileList)
    {
        if (missile->collidesWithItem(m_flagItem))
        {
            m_boomSound2->play();
            gameOver = true;
            break;
        }
    }
    if (gameOver)
    {
        m_timer->stop();
    }
}

void Scene::missileCollisions()
{
    collitionsBetweenMissilesAndBounds();
    collisionsBetweenMissilesAndBricks();
    collisionsBetweenMissiles();
    collisionsBetweenMissilesAndEnemies();
    collisionsBetweenMissilesAndPlayerAndFlag();
}

void Scene::playerCollidesWithBounds()
{
    m_player->setMoveUpEnabled(!m_player->collidesWithItem(m_topRect));
    m_player->setMoveDownEnabled(!m_player->collidesWithItem(m_bottomRect));
    m_player->setMoveLeftEnabled(!m_player->collidesWithItem(m_leftRect));
    m_player->setMoveRightEnabled(!m_player->collidesWithItem(m_rightRect));
}

void Scene::playerCollidesWithBricks()
{
    for (Brick *brick : m_brickList)
    {
        if (m_player->collidesWithItem(brick))
        {
            switch (m_player->direction())
            {
                case MovableItem::NORTH:
                {
                    m_player->setMoveUpEnabled(false);
                    break;
                }
                case MovableItem::SOUTH:
                {
                    m_player->setMoveDownEnabled(false);
                    break;
                }
                case MovableItem::EAST:
                {
                    m_player->setMoveRightEnabled(false);
                    break;
                }
                case MovableItem::WEST:
                {
                    m_player->setMoveLeftEnabled(false);
                    break;
                }
            }
        }
    }
}

void Scene::playerCollidesWithEnemies()
{
    for (Enemy *enemy : m_enemyList)
    {
        if (m_player->collidesWithItem(enemy))
        {
            switch (m_player->direction())
            {
                case MovableItem::NORTH:
                {
                    m_player->setMoveUpEnabled(false);
                    break;
                }
                case MovableItem::SOUTH:
                {
                    m_player->setMoveDownEnabled(false);
                    break;
                }
                case MovableItem::EAST:
                {
                    m_player->setMoveRightEnabled(false);
                    break;
                }
                case MovableItem::WEST:
                {
                    m_player->setMoveLeftEnabled(false);
                    break;
                }
            }
        }
    }
}

void Scene::playerCollisions()
{
    playerCollidesWithBounds();
    playerCollidesWithBricks();
    playerCollidesWithEnemies();
}

void Scene::enemyMoveAndCollisions()
{
    for (Enemy *enemy : m_enemyList)
    {
        switch (enemy->direction())
        {
            case MovableItem::NORTH:
            {
                enemy->moveUp();
                enemy->changeDirectionIfNeeded(m_topRect, enemy->direction());
                break;
            }
            case MovableItem::SOUTH:
            {
                enemy->moveDown();
                enemy->changeDirectionIfNeeded(m_bottomRect, enemy->direction());
                break;
            }
            case MovableItem::EAST:
            {
                enemy->moveRight();
                enemy->changeDirectionIfNeeded(m_rightRect, enemy->direction());
                break;
            }
            case MovableItem::WEST:
            {
                enemy->moveLeft();
                enemy->changeDirectionIfNeeded(m_leftRect, enemy->direction());
                break;
            }
        }
    }
}

void Scene::addMissingEnemies()
{
    if (m_enemyList.size() < 4)
    {
        Enemy *enemy = new Enemy;
        enemy->setPos(0.0, 0.0);
        m_enemyList.push_back(enemy);
        addItem(enemy);
        m_enemyCount--;
        dynamic_cast<EnemyHUD*>(m_enemyHUDProxy->widget())->loadData();
    }
}

void Scene::timeOut()
{
    moveMissiles();
    missileCollisions();
    playerCollisions();
    enemyMoveAndCollisions();
    addMissingEnemies();
    if (m_enemyCount == 0)
    {
        m_timer->stop();
        // you win!
    }
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    const int key = event->key();
    if (event->isAutoRepeat() && m_shootKey.match(key))
    {
        event->ignore();
        QGraphicsScene::keyPressEvent(event);
        return;
    }
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
        m_shootSound->play();
    }
    QGraphicsScene::keyPressEvent(event);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    dynamic_cast<MouseTracker*>(m_mouseTrackerProxy->widget())->display(event->scenePos());
    QGraphicsScene::mouseMoveEvent(event);
}

std::map<Missile*, Enemy*> Scene::getCollisionMapWithEnemies() const
{
    std::map<Missile*, Enemy*> collisionMap;
    for (Missile *missile : getPlayerMissileList())
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
