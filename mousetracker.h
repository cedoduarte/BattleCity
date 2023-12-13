#ifndef MOUSETRACKER_H
#define MOUSETRACKER_H

#include <QWidget>

namespace Ui
{
class MouseTracker;
}

class MouseTracker : public QWidget
{
    Q_OBJECT
public:
    explicit MouseTracker(QWidget *parent = nullptr);
    virtual ~MouseTracker();
    void display(const QPointF &point);
private:
    Ui::MouseTracker *ui;
};

#endif // MOUSETRACKER_H
