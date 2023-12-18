#ifndef SCENE_H
#define SCENE_H

#include "namekey.h"

#include <QGraphicsScene>
#include <list>
#include <map>
#include <QThread>

class QSoundEffect;
class Brick;
class Tank;
class FlagItem;
class Enemy;
class Player;
class Missile;
class QTimer;
class QGraphicsProxyWidget;
class SceneThread;

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(const QRectF &sceneRect, QObject *parent = nullptr);
    virtual ~Scene();
    Player* player() const { return m_player; }
    void addMissile(Missile *missile);
    static Scene* scene() { return s_scene; }
    static void setScene(Scene *scene) { s_scene = scene; }
    NameKey upKey() const { return m_upKey; }
    NameKey downKey() const { return m_downKey; }
    NameKey leftKey() const { return m_leftKey; }
    NameKey rightKey() const { return m_rightKey; }
    NameKey shootKey() const { return m_shootKey; }
    void setUpKey(const NameKey &key) { m_upKey = key; }
    void setDownKey(const NameKey &key) { m_downKey = key; }
    void setLeftKey(const NameKey &key) { m_leftKey = key; }
    void setRightKey(const NameKey &key) { m_rightKey = key; }
    void setShootKey(const NameKey &key) { m_shootKey = key; }
    void loadHUDs();
    void startThread(int msecs);
    std::list<Enemy*> getEnemySiblings(Enemy *enemy) const;
    const std::list<Enemy*>& enemyList() const { return m_enemyList; }
    const std::list<Brick*>& brickList() const { return m_brickList; }
    int enemyCount() const { return m_enemyCount; }
public slots:
    void timeOut();
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
private:
    std::map<Missile*, Enemy*> getCollisionMapWithEnemies() const;
    std::list<Missile*> getEnemyMissileList() const;
    std::list<Missile*> getPlayerMissileList() const;
    void addBrickSet(const std::list<Brick*> &brickSet);
    void missileCollisions();
    void playerCollisions();
    void enemyMoveAndCollisions();
    void createBrickBlocks();
    void createEnemies();
    void createKeys();
    void createHUDs();
    void createBounds(QColor sceneColor);
    QColor setupScene(const QRectF &sceneRect);
    void createPlayer();
    void createFlagItem();
    void playerCollidesWithBounds();
    void playerCollidesWithBricks();
    void playerCollidesWithEnemies();
    void init(const QRectF &sceneRect);
    void moveMissiles();
    void collitionsBetweenMissilesAndBounds();
    void collisionsBetweenMissilesAndBricks();
    void collisionsBetweenMissiles();
    void collisionsBetweenMissilesAndEnemies();
    void collisionsBetweenMissilesAndPlayerAndFlag();
    void addMissingEnemies();
    void createSoundEffects();
    void createEnemy(double x, double y);
    void createThread();

    FlagItem *m_flagItem;
    Player *m_player;
    std::list<Missile*> m_missileList;
    std::list<Enemy*> m_enemyList;
    std::list<Brick*> m_brickList;
    QGraphicsProxyWidget *m_mouseTrackerProxy;
    QGraphicsProxyWidget *m_playerHUDProxy;
    QGraphicsProxyWidget *m_enemyHUDProxy;
    QGraphicsProxyWidget *m_keyHUDProxy;
    static Scene *s_scene;
    QGraphicsRectItem *m_topRect;
    QGraphicsRectItem *m_bottomRect;
    QGraphicsRectItem *m_leftRect;
    QGraphicsRectItem *m_rightRect;
    NameKey m_upKey;
    NameKey m_downKey;
    NameKey m_leftKey;
    NameKey m_rightKey;
    NameKey m_shootKey;
    int m_enemyCount;
    QSoundEffect *m_shootSound;
    QSoundEffect *m_boomSound;
    QSoundEffect *m_boomSound2;
    QSoundEffect *m_backgroundSound;
    SceneThread *m_thread;
};

class SceneThread : public QThread
{
    Q_OBJECT
public:
    explicit SceneThread(QObject *parent = nullptr) : QThread(parent) {}
    virtual ~SceneThread() {}
    void setScene(Scene *scene) { m_scene = scene; }
    void setMilliseconds(int milliseconds) { m_milliseconds = milliseconds; }
public slots:
    void onTimeOut() { m_scene->timeOut(); }
signals:
    void timeOut();
protected:
    void run() override;
private:
    Scene *m_scene;
    int m_milliseconds;
};

#endif // SCENE_H
