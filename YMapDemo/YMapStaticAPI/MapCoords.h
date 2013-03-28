#ifndef MAPCOORDS_H
#define MAPCOORDS_H

// Классы представления точек и размеров в двух системах координат.

#include <QSizeF>
#include <QSize>
#include <QPointF>
#include <QPoint>

class SizeLonLat;
class SizeWorldPixel;
class PointLonLat;
class PointWorldPixel;

///////////////////////////////////////////////////////////////////
// Размер, заданный в мировых координатах долготой и широтой.

class SizeLonLat : private QSizeF
{
public:
    explicit SizeLonLat();
    SizeLonLat(qreal w, qreal h);

    using QSizeF::width;
    using QSizeF::setWidth;

    using QSizeF::height;
    using QSizeF::setHeight;

    SizeWorldPixel toWorldPixel(int zoom) const;

};

///////////////////////////////////////////////////////////////////
// Размер, заданный в "мировых пикселях".

class SizeWorldPixel : private QSize
{
public:
    explicit SizeWorldPixel(const QSize &size);
    SizeWorldPixel(int w, int h);

    using QSize::width;
    using QSize::setWidth;

    using QSize::height;
    using QSize::setHeight;

    // Преобразование к SizeLonLat с учётом масштаба.
    SizeLonLat toLonLat(int zoom) const;

    QSize asQSize() const;

};

///////////////////////////////////////////////////////////////////
// Точка, заданная в мировых координатах долготой и широтой.

class PointLonLat : private QPointF
{
public:
    explicit PointLonLat(qreal lon, qreal lat);

    using QPointF::x;
    using QPointF::y;

    // Преобразование координат в мировые пиксельные.
    PointWorldPixel toWorldPixel(int zoom) const;

    PointLonLat operator+(const SizeLonLat &s) const;
    SizeLonLat operator-(const PointLonLat &other) const;

};

///////////////////////////////////////////////////////////////////
// Точка, заданная координатами в "мировых пикселях".

class PointWorldPixel : private QPoint
{
public:
    explicit PointWorldPixel();
    PointWorldPixel(int x, int y);

    using QPoint::x;
    using QPoint::y;

    PointLonLat toLonLat(int zoom) const;

    PointWorldPixel operator+(const SizeWorldPixel &s) const;
    SizeWorldPixel operator-(const PointWorldPixel &other) const;

};

///////////////////////////////////////////////////////////////////

#endif // MAPCOORDS_H
