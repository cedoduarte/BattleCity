#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "scene.h"

#include <QResizeEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_scene = new Scene(ui->graphicsView->size(), this);
    ui->graphicsView->setScene(m_scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QRectF rect = m_scene->sceneRect();
    rect.setSize(ui->graphicsView->size());
    m_scene->setSceneRect(rect);
}

