#include "MapParams.h"

#include <QUrlQuery>
#include <cmath>

const int AXIS_DIRECTION[] = { 1, -1 };
#define LON_AXIS (0)
#define LAT_AXIS (1)

#define WORLD_ORIGIN_LON (-180)
#define WORLD_ORIGIN_LAT (90)

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
    size.setWidth( std::min(_size.width(), 650) );
    size.setHeight( std::min(_size.height(), 450) );
}

void MapParams::setZoom(int _zoom)
{
    Q_ASSERT_X(_zoom >= 0, "setZoom", "zoom min constraint");
    Q_ASSERT_X(_zoom <= 17, "setZoom", "zoom max constraint");
    zoom = _zoom;
}

void MapParams::movePixels(const QSize &delta)
{
    // Нужно транслировать перемещение по точкам в координаты с учётом zoom.
    // При zoom = 0:
    // 256 пикселям оси x соответствуют долготы (lon) от -180 до 180 (диапазон 360)
    // 256 пикселям оси y соответствуют широты (lat) от -90 до 90 (диапазон 180)
    // При zoom = 1:
    // 256 пикселям оси x соответствует диапазон долготы (lon) 180 градусов
    // 256 пикселям оси y соответствует диапазон широты (lat) 90 градусов
    // ...

    // Также учтём тот факт, что "ось" широты направлена в противоположную
    // сторону к экранной.

    // lon += AXIS_DIRECTION[LON_AXIS] * delta.x() * lonPixelFactor();
    // lat += AXIS_DIRECTION[LAT_AXIS] * delta.y() * latPixelFactor();
    centerLonLat = centerLonLat + toWorldLonLat(delta);
}

QString MapParams::toUrl() const
{
    QUrlQuery query;
    query.addQueryItem( "ll", QString("%1,%2").arg(centerLonLat.x()).arg(centerLonLat.y()) );
    query.addQueryItem( "size", QString("%1,%2").arg(size.width()).arg(size.height()) );
    query.addQueryItem( "z", QString("%1").arg(zoom) );
    query.addQueryItem( "l", "map" );
    return QString("http://static-maps.yandex.ru/1.x/?%1").arg(query.query());
}

const MapParams MapParams::empty()
{
    return MapParams(0, 0, QSize(0, 0), 0, MapLayers::Map);
}

double MapParams::lonPixelFactor() const
{
    return 360. / pow(2.,zoom + 8);
}

double MapParams::latPixelFactor() const
{
    return 180. / pow(2.,zoom + 8);
}

// Преобразование мировых координат (lon, lat) в мировые пиксельные.
// "Левый верхний угол мира" находится в координатах (lon=-180, lat=90)
QPoint MapParams::toWorldPixel(const QPointF &lonLat) const
{
    return toPoint(toWorldPixel(QSizeF(
        lonLat.x() - WORLD_ORIGIN_LON,
        lonLat.y() - WORLD_ORIGIN_LAT
    )));
}

// Преобразование мировых пиксельных координат в мировые (lon, lat).
QPointF MapParams::toWorldLonLat(const QPoint &pixel) const
{
    return QPointF(WORLD_ORIGIN_LON, WORLD_ORIGIN_LAT)
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
