#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&mapLoader, SIGNAL(error(const QString&)),
            ui->mapWidget, SLOT(imageDownloadError(const QString&)));
    connect(&mapLoader, SIGNAL(imageRetrieved(const QByteArray&)),
            ui->mapWidget, SLOT(imageDownloadSuccess(const QByteArray&)));

    QUrl url("http://static-maps.yandex.ru/1.x/?ll=37.620070,55.753630&"
            "size=450,450&z=13&l=map&pt=37.620070,55.753630,pmwtm1~37.64,55.76363,"
            "pmwtm99");
    mapLoader.startRequest(url);

}

MainWindow::~MainWindow()
{
    delete ui;
}
