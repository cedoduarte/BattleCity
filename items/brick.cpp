#include "brick.h"

#include <QPen>
#include <QBrush>

Brick::Brick(QGraphicsItem *parent)
    : QGraphicsRectItem(parent)
{
    setRect(0.0, 0.0, 10.0, 5.0);
    setPen(QPen(Qt::gray, 2.0));
    setBrush(Qt::red);
}

Brick::~Brick()
{
}

std::list<Brick*> Brick::createBrickSet(double x, double y, int rows, int columns)
{
    std::list<Brick*> brickList;
    double ix;
    double iy = y;
    int xCounter;
    int yCounter = 0;
    while (yCounter < rows)
    {
        xCounter = 0;
        ix = x + 10.0;
        while (xCounter < columns)
        {
            Brick *newBrick = new Brick;
            newBrick->setPos(ix, iy);
            brickList.push_back(newBrick);
            ix += 10.0;
            xCounter++;
        }
        iy += 5.0;
        yCounter++;
    }
    return brickList;
}
