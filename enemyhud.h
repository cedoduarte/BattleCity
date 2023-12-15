#ifndef ENEMYHUD_H
#define ENEMYHUD_H

#include <QWidget>

namespace Ui
{
class EnemyHUD;
}

class EnemyHUD : public QWidget
{
    Q_OBJECT
public:
    explicit EnemyHUD(QWidget *parent = nullptr);
    virtual ~EnemyHUD();
    void loadData();
private slots:
    void on_tank_lessSpeedButton_clicked();
    void on_tank_moreSpeedButton_clicked();
    void on_missile_lessSpeedButton_clicked();
    void on_missile_moreSpeedButton_clicked();
private:
    void updateTankSpeed(double speed);
    void updateShootSpeed(double speed);

    Ui::EnemyHUD *ui;
};

#endif // ENEMYHUD_H
