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
protected:
    virtual void setSpeed() = 0;
    double m_xSpeed;
    double m_ySpeed;

    void setDirection(int direction);
    int m_direction;
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
};

#endif // MOVABLEITEM_H
