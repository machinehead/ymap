#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include "MapParams.h"

class MapWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MapWidget(QWidget *parent = 0);
    
signals:
    void mapImageRequest(const MapParams &params);

public slots:
    void imageDownloadError(const QString &description);
    void imageDownloadSuccess(const QByteArray &imageData);

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent * event);

private:
    QPixmap mapImage;
    MapParams mapParams;

};

#endif // MAPWIDGET_H
