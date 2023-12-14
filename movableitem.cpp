#include "movableitem.h"

MovableItem::MovableItem(QGraphicsItem *parent)
    : ImageItem(parent)
{
    m_xSpeed = 0.0;
    m_ySpeed = 0.0;
    m_direction = NORTH;
    m_moveRightEnabled = true;
    m_moveLeftEnabled = true;
    m_moveUpEnabled = true;
    m_moveDownEnabled = true;
}

MovableItem::~MovableItem()
{
}

void MovableItem::moveRight()
{
    if (m_moveRightEnabled)
    {
        setDirection(EAST);
        moveBy(m_xSpeed, 0.0);
    }
}

void MovableItem::moveLeft()
{
    if (m_moveLeftEnabled)
    {
        setDirection(WEST);
        moveBy(-m_xSpeed, 0.0);
    }
}

void MovableItem::moveUp()
{
    if (m_moveUpEnabled)
    {
        setDirection(NORTH);
        moveBy(0.0, -m_ySpeed);
    }
}

void MovableItem::moveDown()
{
    if (m_moveDownEnabled)
    {
        setDirection(SOUTH);
        moveBy(0.0, m_ySpeed);
    }
}

void MovableItem::setDirection(int direction)
{
    switch (m_direction)
    {
        case NORTH:
        {
            changeDirectionFromNorthTo(direction);
            break;
        }
        case SOUTH:
        {
            changeDirectionFromSouthTo(direction);
            break;
        }
        case EAST:
        {
            changeDirectionFromEastTo(direction);
            break;
        }
        case WEST:
        {
            changeDirectionFromWestTo(direction);
            break;
        }
    }
}

void MovableItem::changeDirectionFromNorthTo(int to)
{
    switch (to)
    {
        case SOUTH:
        {
            setDirectionFromNorthToSouth();
            break;
        }
        case EAST:
        {
            setDirectionFromNorthToEast();
            break;
        }
        case WEST:
        {
            setDirectionFromNorthToWest();
            break;
        }
    }
}

void MovableItem::changeDirectionFromSouthTo(int to)
{
    switch (to)
    {
        case NORTH:
        {
            setDirectionFromSouthToNorth();
            break;
        }
        case EAST:
        {
            setDirectionFromSouthToEast();
            break;
        }
        case WEST:
        {
            setDirectionFromSouthToWest();
            break;
        }
    }
}

void MovableItem::changeDirectionFromEastTo(int to)
{
    switch (to)
    {
        case NORTH:
        {
            setDirectionFromEastToNorth();
            break;
        }
        case SOUTH:
        {
            setDirectionFromEastToSouth();
            break;
        }
        case WEST:
        {
            setDirectionFromEastToWest();
            break;
        }
    }
}

void MovableItem::changeDirectionFromWestTo(int to)
{
    switch (to)
    {
        case NORTH:
        {
            setDirectionFromWestToNorth();
            break;
        }
        case SOUTH:
        {
            setDirectionFromWestToSouth();
            break;
        }
        case EAST:
        {
            setDirectionFromWestToEast();
            break;
        }
    }
}

void MovableItem::setDirectionFromNorthToSouth()
{
    setTransformOriginPoint(boundingRect().center());
    setRotation(rotation() + 180.0);
    m_direction = SOUTH;
}

void MovableItem::setDirectionFromNorthToEast()
{
    setTransformOriginPoint(boundingRect().center());
    setRotation(rotation() + 90.0);
    m_direction = EAST;
}

void MovableItem::setDirectionFromNorthToWest()
{
    setTransformOriginPoint(boundingRect().center());
    setRotation(rotation() - 90.0);
    m_direction = WEST;
}

void MovableItem::setDirectionFromSouthToNorth()
{
    setTransformOriginPoint(boundingRect().center());
    setRotation(rotation() + 180.0);
    m_direction = NORTH;
}

void MovableItem::setDirectionFromSouthToEast()
{
    setTransformOriginPoint(boundingRect().center());
    setRotation(rotation() - 90.0);
    m_direction = EAST;
}

void MovableItem::setDirectionFromSouthToWest()
{
    setTransformOriginPoint(boundingRect().center());
    setRotation(rotation() + 90.0);
    m_direction = WEST;
}

void MovableItem::setDirectionFromEastToNorth()
{
    setTransformOriginPoint(boundingRect().center());
    setRotation(rotation() - 90.0);
    m_direction = NORTH;
}

void MovableItem::setDirectionFromEastToSouth()
{
    setTransformOriginPoint(boundingRect().center());
    setRotation(rotation() + 90.0);
    m_direction = SOUTH;
}

void MovableItem::setDirectionFromEastToWest()
{
    setTransformOriginPoint(boundingRect().center());
    setRotation(rotation() + 180.0);
    m_direction = WEST;
}

void MovableItem::setDirectionFromWestToNorth()
{
    setTransformOriginPoint(boundingRect().center());
    setRotation(rotation() + 90.0);
    m_direction = NORTH;
}

void MovableItem::setDirectionFromWestToSouth()
{
    setTransformOriginPoint(boundingRect().center());
    setRotation(rotation() - 90.0);
    m_direction = SOUTH;
}

void MovableItem::setDirectionFromWestToEast()
{
    setTransformOriginPoint(boundingRect().center());
    setRotation(rotation() + 180.0);
    m_direction = EAST;
}
