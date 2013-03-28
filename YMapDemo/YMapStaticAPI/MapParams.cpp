#include "MapParams.h"

#include <QUrlQuery>
#include "ApiConf.h"

MapParams::MapParams(double _lon, double _lat, const QSize &_size, int _zoom,
        MapLayers::Enum _layers) :
    centerPoint(_lon, _lat),
    size(_size),
    zoom(_zoom),
    layers(_layers)
{
}

void MapParams::setSize(const SizeWorldPixel &_size)
{
    size.setWidth( std::min(_size.width(), APICONF_SIZE_X_MAX) );
    size.setHeight( std::min(_size.height(), APICONF_SIZE_Y_MAX) );
}

void MapParams::setZoom(int _zoom)
{
    Q_ASSERT_X(_zoom >= APICONF_ZOOM_MIN, "setZoom", "zoom min constraint");
    Q_ASSERT_X(_zoom <= APICONF_ZOOM_MAX, "setZoom", "zoom max constraint");
    zoom = _zoom;
}

void MapParams::movePixels(const SizeWorldPixel &delta)
{
    centerPoint = centerPoint + delta.toLonLat(zoom);
}

QString MapParams::toUrl() const
{
    QUrlQuery query;
    query.addQueryItem( "ll", QString("%1,%2").arg(centerPoint.x()).arg(centerPoint.y()) );
    query.addQueryItem( "size", QString("%1,%2").arg(size.width()).arg(size.height()) );
    query.addQueryItem( "z", QString("%1").arg(zoom) );
    query.addQueryItem( "l", "map" );
    return QString(APICONF_URL_BASE).arg(query.query());
}

const MapParams MapParams::empty()
{
    return MapParams(0, 0, QSize(0, 0), APICONF_ZOOM_MIN, MapLayers::Map);
}


