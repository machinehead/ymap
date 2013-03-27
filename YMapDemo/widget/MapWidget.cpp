#include "MapWidget.h"

#include <QPainter>
#include <QMessageBox>

MapWidget::MapWidget(QWidget *parent) :
    QWidget(parent),
    mapParams(37.620070, 55.753630, QSize(450, 450), 13, MapLayers::Map)
{
}

void MapWidget::imageDownloadError(const QString &description)
{
    QMessageBox::information(this, tr("HTTP"), description);
}

void MapWidget::imageDownloadSuccess(const QByteArray &imageData)
{
    mapImage.loadFromData(imageData);
    update();
}

void MapWidget::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(0, 0, mapImage);
    painter.end();
}

void MapWidget::resizeEvent(QResizeEvent *)
{
    mapParams.setSize(size());
    emit mapImageRequest(mapParams);
}

