#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <MapParams.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&mapLoader, SIGNAL(error(const QString&)),
            ui->mapWidget, SLOT(imageDownloadError(const QString&)));
    connect(&mapLoader, SIGNAL(imageRetrieved(const QByteArray&)),
            ui->mapWidget, SLOT(imageDownloadSuccess(const QByteArray&)));
    connect(ui->mapWidget, SIGNAL(mapImageRequest(const MapParams &)),
            &mapLoader, SLOT(mapImageRequest(const MapParams &)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
