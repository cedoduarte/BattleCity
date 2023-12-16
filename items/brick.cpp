#include "brick.h"

#include <QPen>
#include <QBrush>

Brick::Brick(QGraphicsItem *parent)
    : QGraphicsRectItem(parent)
{
    QRectF brick(0.0, 0.0, 10.0, 5.0);
    QPen contour(Qt::gray, 2.0);
    QBrush background(Qt::red);
    setRect(brick);
    setPen(contour);
    setBrush(background);
}

Brick::~Brick()
{
}
