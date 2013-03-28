#ifndef MAPPARAMS_H
#define MAPPARAMS_H

#include <QString>
#include "MapCoords.h"

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

    SizeWorldPixel getSize() const { return size; }
    void setSize(const SizeWorldPixel &_size);

    int getZoom() const { return zoom; }
    void setZoom(int _zoom);

    // Изменить координаты центра карты на delta (в экранной декартовой системе координат) с учётом текущего масштаба.
    void movePixels(const SizeWorldPixel &delta);

    // Получить URL запроса к Static API, по которому можно загрузить изображение карты по текущим параметрам.
    QString toUrl() const;

    // Специальное "пустое" значение.
    // Сейчас инициализируется нулями, но всё можно изменить.
    static const MapParams empty();

private:
    PointLonLat centerPoint;
    SizeWorldPixel size;
    int zoom;
    MapLayers::Enum layers;

};

#endif // MAPPARAMS_H
