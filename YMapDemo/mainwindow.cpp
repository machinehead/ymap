#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QUrl>
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

    mapLoader.startRequest(MapParams(37.620070, 55.753630, 450, 450, 13, MapLayers::Map).toUrl());

}

MainWindow::~MainWindow()
{
    delete ui;
}
