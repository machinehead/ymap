#include "TileStorage.h"
#include "MapImageLoader.h"
#include "ApiConf.h"
#include <QPixmapCache>
#include <QPainter>

#include <QDebug>

TileStorage::TileStorage(QObject *parent) :
    QObject(parent),
    currentMapParams(MapParams::empty())
{
}

void TileStorage::drawTile(int x, int y, const QPixmap &tile)
{
    PointWorldPixel mapTopLeft( currentMapParams.getTopLeft() );
    QPainter painter(&currentResult);
    painter.drawPixmap(x - mapTopLeft.x(), y - mapTopLeft.y(), tile);
}

void TileStorage::changeMapParams(const MapParams &params)
{
    currentMapParams = params;
    // Здесь можно реализовать масштабирование и сдвиг currentResult, чтобы сгладить переходы карты.
    currentResult = QPixmap( currentMapParams.getSize().asQSize() );
}

void TileStorage::requestTile(int x, int y)
{
    PointWorldPixel tileOrigin(x, y);
    if(!pendingRequests.contains(tileOrigin)) {
        MapParams tileParams(tileOrigin, SizeWorldPixel(APICONF_TILE_SIZE_PX, APICONF_TILE_SIZE_PX),
                             currentMapParams.getZoom(), currentMapParams.getLayers());

        MapImageLoader *loader = new MapImageLoader(tileParams, &qnam, this);
        connect(loader, SIGNAL(finished(MapImageLoader*)),
                this, SLOT(tileRequestCompleted(MapImageLoader*)));
        pendingRequests.insert(tileOrigin, loader);
        loader->run();
    }
}

void TileStorage::mapImageRequest(const MapParams &params)
{
    changeMapParams(params);

    PointWorldPixel topLeftTile(enclosingTileTopLeft( currentMapParams.getTopLeft() )),
            bottomRightTile(enclosingTileTopLeft( currentMapParams.getBottomRight() ));

    // Обновляем изображение карты тайлами из кэша, а где нет кэша - формируем запрос к API.
    for(int x = topLeftTile.x(); x <= bottomRightTile.x(); x += APICONF_TILE_SIZE_PX) {
        for(int y = topLeftTile.y(); y <= bottomRightTile.y(); y += APICONF_TILE_SIZE_PX) {
            QPixmap tile;
            if(QPixmapCache::find(cacheKey(currentMapParams.getZoom(), x, y), tile)) {
                drawTile(x, y, tile);
            } else {
                requestTile(x, y);
            }
        }
    }

    emit imageRetrieved(currentResult);
}

void TileStorage::tileRequestCompleted(MapImageLoader *loader)
{
    MapParams params = loader->getParams();
    QPixmap tile = loader->getResult();
    QPixmapCache::insert(cacheKey(params.getZoom(), params.getTopLeft().x(), params.getTopLeft().y()),
                         tile);

    drawTile(params.getTopLeft().x(), params.getTopLeft().y(), tile);

    PointWorldPixel tileOrigin(params.getTopLeft());
    pendingRequests.remove(tileOrigin);
    loader->deleteLater();

    emit imageRetrieved(currentResult);
}

PointWorldPixel TileStorage::enclosingTileTopLeft(const PointWorldPixel &point) const
{
    return PointWorldPixel( (point.x() / APICONF_TILE_SIZE_PX) * APICONF_TILE_SIZE_PX,
                            (point.y() / APICONF_TILE_SIZE_PX) * APICONF_TILE_SIZE_PX );
}

QString TileStorage::cacheKey(int zoom, int topLeftX, int topLeftY)
{
    return QString("tile&z=%1&x=%2&y=%3").arg(zoom).arg(topLeftX).arg(topLeftY);
}
