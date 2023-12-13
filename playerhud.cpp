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
    ui->speed_lcdNumber->display(QString::number(speed));

    const int lifeCount = Player::player()->lifeCount();
    ui->lifes_lcdNumber->display(QString::number(lifeCount));
}

void PlayerHUD::on_lessSpeedButton_clicked()
{
    double speed = Player::player()->xSpeed() - 1;
    if (speed == 0)
    {
        speed = 1;
    }
    Player::player()->setSpeedX(speed);
    ui->speed_lcdNumber->display(QString::number(speed));
}

void PlayerHUD::on_moreSpeedButton_clicked()
{
    const double speed = Player::player()->xSpeed() + 1;
    Player::player()->setSpeedX(speed);
    ui->speed_lcdNumber->display(QString::number(speed));
}

