#include "keyhud.h"
#include "ui_keyhud.h"
#include "scene.h"

KeyHUD::KeyHUD(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::KeyHUD)
{
    ui->setupUi(this);
}

KeyHUD::~KeyHUD()
{
    delete ui;
}

void KeyHUD::loadData()
{
    ui->up_comboBox->setCurrentKey(Scene::scene()->upKey().code());
    ui->down_comboBox->setCurrentKey(Scene::scene()->downKey().code());
    ui->right_comboBox->setCurrentKey(Scene::scene()->rightKey().code());
    ui->left_comboBox->setCurrentKey(Scene::scene()->leftKey().code());
    ui->shoot_comboBox->setCurrentKey(Scene::scene()->shootKey().code());
}

void KeyHUD::on_up_comboBox_currentIndexChanged(int index)
{
    Scene::scene()->setUpKey(NameKey::getNameKey(ui->up_comboBox->itemData(index).toInt()));
}

void KeyHUD::on_down_comboBox_currentIndexChanged(int index)
{
    Scene::scene()->setDownKey(NameKey::getNameKey(ui->down_comboBox->itemData(index).toInt()));
}

void KeyHUD::on_left_comboBox_currentIndexChanged(int index)
{
    Scene::scene()->setLeftKey(NameKey::getNameKey(ui->left_comboBox->itemData(index).toInt()));
}

void KeyHUD::on_right_comboBox_currentIndexChanged(int index)
{
    Scene::scene()->setRightKey(NameKey::getNameKey(ui->right_comboBox->itemData(index).toInt()));
}

void KeyHUD::on_shoot_comboBox_currentIndexChanged(int index)
{
    Scene::scene()->setShootKey(NameKey::getNameKey(ui->shoot_comboBox->itemData(index).toInt()));
}

