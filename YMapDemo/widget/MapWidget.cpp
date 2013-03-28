#include "MapWidget.h"

#include <QPainter>
#include <QMessageBox>
#include <QWheelEvent>

#include <QDebug>

MapWidget::MapWidget(QWidget *parent) :
    QWidget(parent),
    mapParams(37.620070, 55.753630, QSize(450, 450), 13, MapLayers::Map),
    isDragging(false)
{
}

void MapWidget::imageDownloadError(const QString &description)
{
    QMessageBox::information(this, tr("HTTP"), description);
}

void MapWidget::mapImageUpdate(const QPixmap &image)
{
    mapImage = image;
    update();
}

void MapWidget::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(0, 0, mapImage);
    painter.end();
}

void MapWidget::requestImage()
{
    emit mapImageRequest(mapParams);
}

void MapWidget::resizeEvent(QResizeEvent *)
{
    mapParams.setSize(SizeWorldPixel(size()));
    requestImage();
}

void MapWidget::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->angleDelta().y() / 8;

    int numSteps = numDegrees / 15;
    mapParams.setZoom( std::max( std::min( mapParams.getZoom() + numSteps, 17 ), 0 ) );
    requestImage();

    event->accept();
}

void MapWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        isDragging = true;
        dragStartPos = event->pos();
    }
}

// Подвинуть карту следом за перемещением мыши из dragStartPos в pos.
void MapWidget::dragMap(const QPoint &pos)
{
    Q_ASSERT_X(isDragging, "dragMap", "must be dragging");

    // Вектор перемещения из начальной точки в конечную противоположен необходимому перемещению
    // центра карты.
    QPoint delta(dragStartPos - pos);
    mapParams.movePixels(SizeWorldPixel(delta.x(), delta.y()));
    dragStartPos = pos;
    requestImage();
}

void MapWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(isDragging) {
        dragMap(event->pos());
    }
}

void MapWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        if(isDragging) {
            dragMap(event->pos());
        }
        isDragging = false;
    }
}
