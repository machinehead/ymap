#include "MapWidget.h"

#include <QPainter>
#include <QMessageBox>

MapWidget::MapWidget(QWidget *parent) :
    QWidget(parent)
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

void MapWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(0, 0, mapImage);
    painter.end();
}

