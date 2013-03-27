#include "MapParams.h"

#include <QUrlQuery>

MapParams::MapParams(double _lat, double _lon, const QSize &_size, int _zoom,
        MapLayers::Enum _layers) :
    lat(_lat),
    lon(_lon),
    size(_size),
    zoom(_zoom),
    layers(_layers)
{
}

void MapParams::setSize(const QSize &newSize)
{
    size = newSize;
}

QString MapParams::toUrl() const
{
    QUrlQuery query;
    query.addQueryItem( "ll", QString("%1,%2").arg(lat).arg(lon) );
    query.addQueryItem( "size", QString("%1,%2").arg(size.width()).arg(size.height()) );
    query.addQueryItem( "z", QString("%1").arg(zoom) );
    query.addQueryItem( "l", "map" );
    return QString("http://static-maps.yandex.ru/1.x/?%1").arg(query.query());
}
