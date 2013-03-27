#include "MapParams.h"

#include <QUrlQuery>

MapParams::MapParams(double _lat, double _lon, int _sizeX, int _sizeY, int _zoom,
        MapLayers::Enum _layers) :
    lat(_lat),
    lon(_lon),
    sizeX(_sizeX),
    sizeY(_sizeY),
    zoom(_zoom),
    layers(_layers)
{
}

QString MapParams::toUrl() const
{
    QUrlQuery result("http://static-maps.yandex.ru/1.x/?");
    result.addQueryItem( "ll", QString("%1,%2").arg(lat).arg(lon) );
    result.addQueryItem( "size", QString("%1,%2").arg(sizeX).arg(sizeY) );
    result.addQueryItem( "z", QString("%1").arg(zoom) );
    result.addQueryItem( "l", "map" );
    return result.query();
}
