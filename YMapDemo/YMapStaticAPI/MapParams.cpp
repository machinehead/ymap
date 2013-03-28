#include "MapParams.h"

#include <QUrlQuery>
#include <cmath>

MapParams::MapParams(double _lon, double _lat, const QSize &_size, int _zoom,
        MapLayers::Enum _layers) :
    lon(_lon),
    lat(_lat),
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

void MapParams::movePixels(QPoint delta)
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
    lon += 360. * delta.x() / pow(2.,zoom + 8);
    lat -= 180. * delta.y() / pow(2.,zoom + 8);
}

QString MapParams::toUrl() const
{
    QUrlQuery query;
    query.addQueryItem( "ll", QString("%1,%2").arg(lon).arg(lat) );
    query.addQueryItem( "size", QString("%1,%2").arg(size.width()).arg(size.height()) );
    query.addQueryItem( "z", QString("%1").arg(zoom) );
    query.addQueryItem( "l", "map" );
    return QString("http://static-maps.yandex.ru/1.x/?%1").arg(query.query());
}
