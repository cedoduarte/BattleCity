#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <list>

class Player;
class Missile;
class QTimer;

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(const QSize &size, QObject *parent = nullptr);
    virtual ~Scene();
    Player *player() const { return m_player; }
    void addMissile(Missile *missile);
private slots:
    void timeOut();
protected:
    void keyPressEvent(QKeyEvent *event) override;
private:
    QTimer *m_timer;
    Player *m_player;
    std::list<Missile*> m_missileList;
};

#endif // SCENE_H
