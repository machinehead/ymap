#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <MapParams.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->mapWidget, SIGNAL(mapImageRequest(const MapParams &)),
            &tileStorage, SLOT(mapImageRequest(const MapParams &)));

    connect(&tileStorage, SIGNAL(imageRetrieved(const QPixmap&)),
            ui->mapWidget, SLOT(mapImageUpdate(const QPixmap&)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
