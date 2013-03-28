#ifndef TILESTORAGE_H
#define TILESTORAGE_H

#include <QObject>
#include "MapParams.h"
#include <QPixmap>
#include <QSet>
#include <QNetworkAccessManager>

class MapImageLoader;

class TileStorage : public QObject
{
    Q_OBJECT
public:
    explicit TileStorage(QObject *parent = 0);
    
signals:
    void imageRetrieved(const QPixmap &image);

public slots:
    void mapImageRequest(const MapParams &params);

    void tileRequestCompleted(const MapImageLoader *loader);

private:
    MapParams currentMapParams;
    QPixmap currentResult;

    QNetworkAccessManager qnam;
    QSet<MapImageLoader*> pendingRequests;

};

#endif // TILESTORAGE_H
