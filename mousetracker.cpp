#include "mousetracker.h"
#include "ui_mousetracker.h"

MouseTracker::MouseTracker(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MouseTracker)
{
    ui->setupUi(this);
}

MouseTracker::~MouseTracker()
{
    delete ui;
}

void MouseTracker::display(const QPointF &point)
{
    ui->x_lcdNumber->display(QString::number(point.x()));
    ui->y_lcdNumber->display(QString::number(point.y()));
}
