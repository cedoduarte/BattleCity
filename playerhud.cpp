#include "playerhud.h"
#include "ui_playerhud.h"
#include "player.h"

PlayerHUD::PlayerHUD(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlayerHUD)
{
    ui->setupUi(this);
}

PlayerHUD::~PlayerHUD()
{
    delete ui;
}

void PlayerHUD::loadData()
{
    const double speed = Player::player()->xSpeed();
    ui->tankSpeed_lcdNumber->display(QString::number(speed));

    const int lifeCount = Player::player()->lifeCount();
    ui->lifes_lcdNumber->display(QString::number(lifeCount));

    const double missileSpeed = Player::player()->missileSpeed();
    ui->missileSpeed_lcdNumber->display(QString::number(missileSpeed));
}

void PlayerHUD::on_tank_lessSpeedButton_clicked()
{
    double speed = Player::player()->xSpeed() - 1;
    if (speed == 0)
    {
        speed = 1;
    }
    Player::player()->setSpeedX(speed);
    Player::player()->setSpeedY(speed);
    ui->tankSpeed_lcdNumber->display(QString::number(speed));
}

void PlayerHUD::on_tank_moreSpeedButton_clicked()
{
    const double speed = Player::player()->xSpeed() + 1;
    Player::player()->setSpeedX(speed);
    Player::player()->setSpeedY(speed);
    ui->tankSpeed_lcdNumber->display(QString::number(speed));
}

void PlayerHUD::on_missile_lessSpeedButton_clicked()
{
    double speed = Player::player()->missileSpeed() - 1;
    if (speed == 0)
    {
        speed = 1;
    }
    Player::player()->setMissileSpeed(speed);
    ui->missileSpeed_lcdNumber->display(QString::number(speed));
}

void PlayerHUD::on_missile_moreSpeedButton_clicked()
{
    const double speed = Player::player()->missileSpeed() + 1;
    Player::player()->setMissileSpeed(speed);
    ui->missileSpeed_lcdNumber->display(QString::number(speed));
}
