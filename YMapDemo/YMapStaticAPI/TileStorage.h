#ifndef TILESTORAGE_H
#define TILESTORAGE_H

// Объект TileStorage организует хранение в кеше тайлов карты и формирование изображения текущей части карты.

#include <QObject>
#include "MapParams.h"
#include <QPixmap>
#include <QHash>
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

    void tileRequestCompleted(MapImageLoader *loader);

private:
    MapParams currentMapParams;
    QPixmap currentResult;

    QNetworkAccessManager qnam;
    QHash<PointWorldPixel, MapImageLoader*> pendingRequests;

    PointWorldPixel enclosingTileTopLeft(const PointWorldPixel &point) const;

    void changeMapParams(const MapParams &params);
    void requestTile(int x, int y);

    void drawTile(int x, int y, const QPixmap &tile);

    static QString cacheKey(int zoom, int topLeftX, int topLeftY);
};

#endif // TILESTORAGE_H
