#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include "MapParams.h"

class MapWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MapWidget(QWidget *parent = 0);
    
    void requestImage();
signals:
    void mapImageRequest(const MapParams &params);

public slots:
    void imageDownloadError(const QString &description);
    void mapImageUpdate(const QPixmap &image);

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent * event);
    virtual void wheelEvent(QWheelEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    QPixmap mapImage;
    MapParams mapParams;

    bool isDragging;
    QPoint dragStartPos;

    void dragMap(const QPoint &pos);

};

#endif // MAPWIDGET_H
