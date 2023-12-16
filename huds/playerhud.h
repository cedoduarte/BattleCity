#ifndef PLAYERHUD_H
#define PLAYERHUD_H

#include <QWidget>

namespace Ui
{
class PlayerHUD;
}

class PlayerHUD : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerHUD(QWidget *parent = nullptr);
    virtual ~PlayerHUD();
    void loadData();
private slots:
    void on_tank_lessSpeedButton_clicked();
    void on_tank_moreSpeedButton_clicked();
    void on_missile_lessSpeedButton_clicked();
    void on_missile_moreSpeedButton_clicked();
private:
    Ui::PlayerHUD *ui;
};

#endif // PLAYERHUD_H
