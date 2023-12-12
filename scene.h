#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class Player;

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(const QSize &size, QObject *parent = nullptr);
    virtual ~Scene();
    Player *player() const { return m_player; }
protected:
    void keyPressEvent(QKeyEvent *event) override;
private:
    Player *m_player;
};

#endif // SCENE_H
