#ifndef MOVABLEITEM_H
#define MOVABLEITEM_H

#include "imageitem.h"

class MovableItem : public ImageItem
{
public:
    enum Direction
    {
        NORTH,
        SOUTH,
        EAST,
        WEST
    };

    explicit MovableItem(QGraphicsItem *parent = nullptr);
    virtual ~MovableItem();
    void setSpeedX(double speed) { m_xSpeed = speed; }
    void setSpeedY(double speed) { m_ySpeed = speed; }
    double xSpeed() const { return m_xSpeed; }
    double ySpeed() const { return m_ySpeed; }
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    bool isMoveRightEnabled() const { return m_moveRightEnabled; }
    bool isMoveLeftEnabled() const { return m_moveLeftEnabled; }
    bool isMoveUpEnabled() const { return m_moveUpEnabled; }
    bool isMoveDownEnabled() const { return m_moveDownEnabled; }
    void setMoveRightEnabled(bool enabled) { m_moveRightEnabled = enabled; }
    void setMoveLeftEnabled(bool enabled) { m_moveLeftEnabled = enabled; }
    void setMoveUpEnabled(bool enabled) { m_moveUpEnabled = enabled; }
    void setMoveDownEnabled(bool enabled) { m_moveDownEnabled = enabled; }
    int direction() const { return m_direction; }
    void setDirection(int direction);
    void setCanMove(bool canMove) { m_canMove = canMove; }
    bool canMove() const { return m_canMove; }
protected:
    virtual void setSpeed() = 0;

    double m_xSpeed;
    double m_ySpeed;
    int m_direction;
    bool m_canMove;
private:
    void changeDirectionFromNorthTo(int to);
    void changeDirectionFromSouthTo(int to);
    void changeDirectionFromEastTo(int to);
    void changeDirectionFromWestTo(int to);
    void setDirectionFromNorthToSouth();
    void setDirectionFromNorthToEast();
    void setDirectionFromNorthToWest();
    void setDirectionFromSouthToNorth();
    void setDirectionFromSouthToEast();
    void setDirectionFromSouthToWest();
    void setDirectionFromEastToNorth();
    void setDirectionFromEastToSouth();
    void setDirectionFromEastToWest();
    void setDirectionFromWestToNorth();
    void setDirectionFromWestToSouth();
    void setDirectionFromWestToEast();

    bool m_moveRightEnabled;
    bool m_moveLeftEnabled;
    bool m_moveUpEnabled;
    bool m_moveDownEnabled;
};

#endif // MOVABLEITEM_H
