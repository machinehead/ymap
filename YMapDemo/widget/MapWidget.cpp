#include "MapWidget.h"

#include <QtNetwork>
#include <QPainter>
#include <QMessageBox>

MapWidget::MapWidget(QWidget *parent) :
    QWidget(parent)
{
    QUrl url("http://static-maps.yandex.ru/1.x/?ll=37.620070,55.753630&"
            "size=450,450&z=13&l=map&pt=37.620070,55.753630,pmwtm1~37.64,55.76363,"
            "pmwtm99");
    startRequest(url);
}

void MapWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(0, 0, mapImage);
    painter.end();
}

void MapWidget::startRequest(QUrl url)
{
    httpReply = qnam.get(QNetworkRequest(url));
    connect(httpReply, SIGNAL(finished()),
            this, SLOT(httpFinished()));
}

void MapWidget::httpFinished()
{
    if (httpReply->error()) {
        QMessageBox::information(this, tr("HTTP"),
                                 tr("Download failed: %1.")
                                 .arg(httpReply->errorString()));
    } else {
        QByteArray imageData = httpReply->readAll();
        mapImage.loadFromData(imageData);
        update();
    }

    httpReply->deleteLater();
    httpReply = 0;
}
