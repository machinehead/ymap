#include "MapParams.h"

#include <QUrlQuery>
#include <cmath>
#include "ApiConf.h"

// Коррекция направлений осей: экранная ось широты направлена противоположно мировой.
const int AXIS_DIRECTION[] = { 1, -1 };
#define LON_AXIS (0)
#define LAT_AXIS (1)

/////////////////////////////
// Вспомогательные методы для операций над QPoint и QSize
static QPoint toPoint(const QSize &size)
{
    return QPoint(size.width(), size.height());
}

static QPoint operator+(const QPoint &point, const QSize &offset)
{
    return QPoint(point.x() + offset.width(), point.y() + offset.height());
}

static QPointF operator+(const QPointF &point, const QSizeF &offset)
{
    return QPointF(point.x() + offset.width(), point.y() + offset.height());
}

/////////////////////////////

MapParams::MapParams(double _lon, double _lat, const QSize &_size, int _zoom,
        MapLayers::Enum _layers) :
    centerLonLat(_lon, _lat),
    size(_size),
    zoom(_zoom),
    layers(_layers)
{
}

void MapParams::setSize(const QSize &_size)
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

void MapParams::movePixels(const QSize &delta)
{
    centerLonLat = centerLonLat + toWorldLonLat(delta);
}

QString MapParams::toUrl() const
{
    QUrlQuery query;
    query.addQueryItem( "ll", QString("%1,%2").arg(centerLonLat.x()).arg(centerLonLat.y()) );
    query.addQueryItem( "size", QString("%1,%2").arg(size.width()).arg(size.height()) );
    query.addQueryItem( "z", QString("%1").arg(zoom) );
    query.addQueryItem( "l", "map" );
    return QString(APICONF_URL_BASE).arg(query.query());
}

const MapParams MapParams::empty()
{
    return MapParams(0, 0, QSize(0, 0), APICONF_ZOOM_MIN, MapLayers::Map);
}

double MapParams::lonPixelFactor() const
{
    return 360. / pow(2.,zoom + APICONF_TILE_SIZE_PWR);
}

double MapParams::latPixelFactor() const
{
    return 180. / pow(2.,zoom + APICONF_TILE_SIZE_PWR);
}

// Преобразование мировых координат (lon, lat) в мировые пиксельные.
QPoint MapParams::toWorldPixel(const QPointF &lonLat) const
{
    return toPoint(toWorldPixel(QSizeF(
        lonLat.x() - APICONF_WORLD_ORIGIN_LON,
        lonLat.y() - APICONF_WORLD_ORIGIN_LAT
    )));
}

// Преобразование мировых пиксельных координат в мировые (lon, lat).
QPointF MapParams::toWorldLonLat(const QPoint &pixel) const
{
    return QPointF(APICONF_WORLD_ORIGIN_LON, APICONF_WORLD_ORIGIN_LAT)
        + toWorldLonLat(QSize( pixel.x(), pixel.y() ));
}

// Преобразования размеров

QSize MapParams::toWorldPixel(const QSizeF &lonLat) const
{
    return QSizeF(
        AXIS_DIRECTION[LON_AXIS] * lonLat.width() / lonPixelFactor(),
        AXIS_DIRECTION[LAT_AXIS] * lonLat.height() / latPixelFactor()
    ).toSize();
}

QSizeF MapParams::toWorldLonLat(const QSize &pixel) const
{
    return QSizeF(
        AXIS_DIRECTION[LON_AXIS] * pixel.width() * lonPixelFactor(),
        AXIS_DIRECTION[LAT_AXIS] * pixel.height() * latPixelFactor()
    );
}
