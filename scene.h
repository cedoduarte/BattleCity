#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <list>
#include <map>

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
    Player *player() const { return m_player; }
    void addMissile(Missile *missile);
    static Scene* scene() { return s_scene; }
    static void setScene(Scene *scene) { s_scene = scene; }
    void removeMissile(Missile *missile);
private slots:
    void timeOut();
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
private:
    std::map<Missile*, Enemy*> getCollisionMapWithEnemies() const;

    QTimer *m_timer;
    Player *m_player;
    std::list<Missile*> m_missileList;
    std::list<Enemy*> m_enemyList;
    QGraphicsProxyWidget *m_mouseTrackerProxy;
    QGraphicsProxyWidget *m_playerHUDProxy;
    static Scene *s_scene;
    QGraphicsRectItem *m_topRect;
    QGraphicsRectItem *m_bottomRect;
    QGraphicsRectItem *m_leftRect;
    QGraphicsRectItem *m_rightRect;
};

#endif // SCENE_H
