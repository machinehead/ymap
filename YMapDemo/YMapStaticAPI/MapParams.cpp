#include "MapParams.h"

#include <QUrlQuery>
#include "ApiConf.h"

MapParams::MapParams(const PointLonLat &center, const SizeWorldPixel &_size, int _zoom,
        MapLayers::Enum _layers) :
    topLeftPoint(0, 0),
    size(_size),
    zoom(_zoom),
    layers(_layers)
{
    setCenter(center);
}

MapParams::MapParams(const PointWorldPixel &topLeft, const SizeWorldPixel &_size, int _zoom,
        MapLayers::Enum _layers) :
    topLeftPoint(topLeft),
    size(_size),
    zoom(_zoom),
    layers(_layers)
{
}

PointLonLat MapParams::getCenter() const
{
    return (topLeftPoint + size / 2).toLonLat(zoom);
}

void MapParams::setCenter(const PointLonLat &center)
{
    topLeftPoint = center.toWorldPixel(zoom) - size / 2;
}

PointWorldPixel MapParams::getTopLeft() const
{
    return topLeftPoint;
}

void MapParams::setTopLeft(const PointWorldPixel &topLeft)
{
    topLeftPoint = topLeft;
}

PointWorldPixel MapParams::getBottomRight() const
{
    return topLeftPoint + size;
}

void MapParams::setBottomRight(const PointWorldPixel &bottomRight)
{
    topLeftPoint = bottomRight - size;
}

void MapParams::setSize(const SizeWorldPixel &_size)
{
    // size.setWidth( std::min(_size.width(), APICONF_SIZE_X_MAX) );
    // size.setHeight( std::min(_size.height(), APICONF_SIZE_Y_MAX) );
    size.setWidth( _size.width() );
    size.setHeight( _size.height() );
}

void MapParams::setZoom(int _zoom)
{
    Q_ASSERT_X(_zoom >= APICONF_ZOOM_MIN, "setZoom", "zoom min constraint");
    Q_ASSERT_X(_zoom <= APICONF_ZOOM_MAX, "setZoom", "zoom max constraint");
    PointLonLat center = getCenter();
    zoom = _zoom;
    setCenter(center);
}

void MapParams::movePixels(const SizeWorldPixel &delta)
{
    topLeftPoint = topLeftPoint + delta;
}

QString MapParams::toUrl() const
{
    QUrlQuery query;
    query.addQueryItem( "ll", QString("%1,%2").arg(getCenter().x(), 0, 'f', 12).arg(getCenter().y(), 0, 'f', 12) );
    query.addQueryItem( "size", QString("%1,%2").arg(size.width()).arg(size.height()) );
    // query.addQueryItem( "spn", QString("%1,%2").arg(size.toLonLat(zoom).width()).arg(-size.toLonLat(zoom).height()) );
    query.addQueryItem( "z", QString("%1").arg(zoom) );
    query.addQueryItem( "l", "map" );
    // query.addQueryItem( "pt", QString("%1,%2,pmwtm1").arg(getBottomRight().toLonLat(zoom).x(), 0, 'f', 12).arg(getBottomRight().toLonLat(zoom).y(), 0, 'f', 12) );
    return QString(APICONF_URL_BASE).arg(query.query());
}

const MapParams MapParams::empty()
{
    return MapParams(PointLonLat(0, 0), SizeWorldPixel(0, 0), APICONF_ZOOM_MIN, MapLayers::Map);
}


