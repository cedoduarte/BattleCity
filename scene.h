#ifndef SCENE_H
#define SCENE_H

#include "namekey.h"

#include <QGraphicsScene>
#include <list>
#include <map>

class Tank;
class FlagItem;
class Enemy;
class Player;
class Missile;
class QTimer;
class QGraphicsProxyWidget;

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
    void startTimer(int msecs);
    std::list<Enemy*> getEnemySiblings(Enemy *enemy) const;
    const std::list<Enemy*>& enemyList() const { return m_enemyList; }
private slots:
    void timeOut();
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
private:
    std::map<Missile*, Enemy*> getCollisionMapWithEnemies() const;
    std::list<Missile*> getEnemyMissileList() const;
    std::list<Missile*> getPlayerMissileList() const;

    FlagItem *m_flagItem;
    QTimer *m_timer;
    Player *m_player;
    std::list<Missile*> m_missileList;
    std::list<Enemy*> m_enemyList;
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
};

#endif // SCENE_H
