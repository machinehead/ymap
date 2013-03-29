#include "MapCoords.h"
#include <cmath>
#include "ApiConf.h"

///////////////////////////////////////////////////////////////////
// Общие методы и константы для реализации классов

// Коррекция направлений осей: экранная ось широты направлена противоположно мировой.
const int AXIS_DIRECTION[] = { 1, -1 };
#define LON_AXIS (0)
#define LAT_AXIS (1)

static double lonPixelFactor(int zoom)
{
    double result = 360. / pow(2.,zoom + APICONF_TILE_SIZE_PWR);
    return result;
}

static double latPixelFactor(int zoom)
{
    double result = 180. / pow(2.,zoom + APICONF_TILE_SIZE_PWR);
    return result;
}

///////////////////////////////////////////////////////////////////
// SizeLonLat

SizeLonLat::SizeLonLat() :
    QSizeF()
{
}

SizeLonLat::SizeLonLat(qreal w, qreal h) :
    QSizeF( w, h )
{
}

SizeWorldPixel SizeLonLat::toWorldPixel(int zoom) const
{
    return SizeWorldPixel(AXIS_DIRECTION[LON_AXIS] * width() / lonPixelFactor(zoom),
                          AXIS_DIRECTION[LAT_AXIS] * height() / latPixelFactor(zoom));
}

///////////////////////////////////////////////////////////////////
// SizeWorldPixel

SizeWorldPixel::SizeWorldPixel(const QSize &size) :
    QSize(size)
{
}

SizeWorldPixel::SizeWorldPixel(int w, int h) :
    QSize(w, h)
{
}

SizeLonLat SizeWorldPixel::toLonLat(int zoom) const
{
    return SizeLonLat(
        AXIS_DIRECTION[LON_AXIS] * width() * lonPixelFactor(zoom),
        AXIS_DIRECTION[LAT_AXIS] * height() * latPixelFactor(zoom)
    );
}

QSize SizeWorldPixel::asQSize() const
{
    return *this;
}

SizeWorldPixel SizeWorldPixel::operator/(int div) const
{
    return SizeWorldPixel(*(QSize*)this / div);
}

bool SizeWorldPixel::operator ==(const SizeWorldPixel &other) const
{
    return *(QSize*)this == (const QSize &) other;
}

///////////////////////////////////////////////////////////////////
// PointLonLat

PointLonLat::PointLonLat(qreal lon, qreal lat) :
    QPointF(lon, lat)
{
}

PointWorldPixel PointLonLat::toWorldPixel(int zoom) const
{
    return PointWorldPixel(0, 0)
            + (*this - PointLonLat(APICONF_WORLD_ORIGIN_LON, APICONF_WORLD_ORIGIN_LAT))
              .toWorldPixel(zoom);
}

PointLonLat PointLonLat::operator+(const SizeLonLat &s) const
{
    return PointLonLat( x() + s.width(), y() + s.height() );
}

SizeLonLat PointLonLat::operator-(const PointLonLat &other) const
{
    return SizeLonLat( x() - other.x(), y() - other.y() );
}

///////////////////////////////////////////////////////////////////
// PointWorldPixel

PointWorldPixel::PointWorldPixel() :
    QPoint()
{
}

PointWorldPixel::PointWorldPixel(int x, int y) :
    QPoint(x, y)
{
}

PointLonLat PointWorldPixel::toLonLat(int zoom) const
{
    return PointLonLat(APICONF_WORLD_ORIGIN_LON, APICONF_WORLD_ORIGIN_LAT)
            + (*this - PointWorldPixel(0, 0)).toLonLat(zoom);
}

PointWorldPixel PointWorldPixel::operator+(const SizeWorldPixel &s) const
{
    return PointWorldPixel( x() + s.width(), y() + s.height() );
}

PointWorldPixel PointWorldPixel::operator-(const SizeWorldPixel &s) const
{
    return PointWorldPixel( x() - s.width(), y() - s.height() );
}

SizeWorldPixel PointWorldPixel::operator-(const PointWorldPixel &other) const
{
    return SizeWorldPixel( x() - other.x(), y() - other.y() );
}

bool PointWorldPixel::operator==(const PointWorldPixel &other) const
{
    return x() == other.x() && y() == other.y();
}

uint qHash(const PointWorldPixel &key)
{
    return key.x() ^ (key.y() << 5);
}

///////////////////////////////////////////////////////////////////
