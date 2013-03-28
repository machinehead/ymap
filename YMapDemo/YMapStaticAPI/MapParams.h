#ifndef MAPPARAMS_H
#define MAPPARAMS_H

#include <QString>
#include <QSize>
#include <QPoint>

namespace MapLayers {
    enum Enum {
        Map,
        Satellite,
        Hybrid
    };
} // namespace MapLayers

class MapParams
{
public:
    MapParams(double lon, double lat, const QSize &size, int zoom, MapLayers::Enum layers);

    QSize getSize() const { return size; }
    void setSize(const QSize &_size);

    int getZoom() const { return zoom; }
    void setZoom(int _zoom);

    // Изменить координаты центра карты на delta (в экранной декартовой системе координат) с учётом текущего масштаба.
    void movePixels(const QSize &delta);

    // Получить URL запроса к Static API, по которому можно загрузить изображение карты по текущим параметрам.
    QString toUrl() const;

    // Специальное "пустое" значение.
    // Сейчас инициализируется нулями, но всё можно изменить.
    static const MapParams empty();

private:
    QPointF centerLonLat;
    QSize size;
    int zoom;
    MapLayers::Enum layers;

    double lonPixelFactor() const;
    double latPixelFactor() const;

    QPoint toWorldPixel(const QPointF &lonLat) const;
    QPointF toWorldLonLat(const QPoint &pixel) const;

    QSize toWorldPixel(const QSizeF &lonLat) const;
    QSizeF toWorldLonLat(const QSize &pixel) const;

};

#endif // MAPPARAMS_H
