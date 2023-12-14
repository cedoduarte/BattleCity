#ifndef PLAYER_H
#define PLAYER_H

#include "tank.h"

class Player : public Tank
{
public:
    explicit Player(QGraphicsItem *parent = nullptr);
    virtual ~Player();
    static Player* player() { return s_player; }
    static void setPlayer(Player *player) { s_player = player; }
protected:
    void loadImageFromResource() override;
    void setSpeed() override;
    void setLifes() override;
    void setTankType() override;
    void setShootSpeed() override;
private:
    static Player *s_player;
};

#endif // PLAYER_H
