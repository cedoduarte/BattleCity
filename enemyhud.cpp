#include "enemyhud.h"
#include "ui_enemyhud.h"
#include "enemy.h"

EnemyHUD::EnemyHUD(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EnemyHUD)
{
    ui->setupUi(this);
}

EnemyHUD::~EnemyHUD()
{
    delete ui;
}

void EnemyHUD::loadData()
{
    const double speed = Enemy::tankSpeed();
    ui->tankSpeed_lcdNumber->display(QString::number(speed));

    const double missileSpeed = Enemy::tankMissileSpeed();
    ui->missileSpeed_lcdNumber->display(QString::number(missileSpeed));
}

void EnemyHUD::on_tank_lessSpeedButton_clicked()
{
    double speed = Enemy::tankSpeed() - 1;
    if (speed == 0)
    {
        speed = 1;
    }
    Enemy::setTankSpeed(speed);
    ui->tankSpeed_lcdNumber->display(QString::number(speed));
}

void EnemyHUD::on_tank_moreSpeedButton_clicked()
{
    const double speed = Enemy::tankSpeed() + 1;
    Enemy::setTankSpeed(speed);
    ui->tankSpeed_lcdNumber->display(QString::number(speed));
}

void EnemyHUD::on_missile_lessSpeedButton_clicked()
{
    double speed = Enemy::tankMissileSpeed() - 1;
    if (speed == 0)
    {
        speed = 1;
    }
    Enemy::setTankMissileSpeed(speed);
    ui->missileSpeed_lcdNumber->display(QString::number(speed));
}

void EnemyHUD::on_missile_moreSpeedButton_clicked()
{
    const double speed = Enemy::tankMissileSpeed() + 1;
    Enemy::setTankMissileSpeed(speed);
    ui->missileSpeed_lcdNumber->display(QString::number(speed));
}

