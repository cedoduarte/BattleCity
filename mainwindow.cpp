#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "scene.h"

#include <QResizeEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRectF sceneRect;
    sceneRect.setX(0.0);
    sceneRect.setY(0.0);
    sceneRect.setWidth(800);
    sceneRect.setHeight(600);
    m_scene = new Scene(sceneRect, this);
    Scene::setScene(m_scene);
    m_scene->loadHUDs();
    m_scene->startTimer(50);
    ui->graphicsView->setScene(m_scene);
    ui->graphicsView->setMouseTracking(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
