#ifndef MAPPARAMS_H
#define MAPPARAMS_H

// Описание (фрагмента) карты.

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
    MapParams(const PointLonLat &center, const SizeWorldPixel &size, int zoom, MapLayers::Enum layers);
    MapParams(const PointWorldPixel &topLeft, const SizeWorldPixel &size, int zoom, MapLayers::Enum layers);

    PointLonLat getCenter() const;
    void setCenter(const PointLonLat &center);

    PointWorldPixel getTopLeft() const;
    void setTopLeft(const PointWorldPixel &topLeft);

    PointWorldPixel getBottomRight() const;
    void setBottomRight(const PointWorldPixel &bottomRight);

    SizeWorldPixel getSize() const { return size; }
    void setSize(const SizeWorldPixel &_size);

    int getZoom() const { return zoom; }
    void setZoom(int _zoom);

    MapLayers::Enum getLayers() const { return layers; }

    // Изменить координаты центра карты на delta (в экранной декартовой системе координат) с учётом текущего масштаба.
    void movePixels(const SizeWorldPixel &delta);

    // Получить URL запроса к Static API, по которому можно загрузить изображение карты по текущим параметрам.
    QString toUrl() const;

    // Специальное "пустое" значение.
    // Сейчас инициализируется нулями, но всё можно изменить.
    static const MapParams empty();

private:
    PointWorldPixel topLeftPoint;
    SizeWorldPixel size;
    int zoom;
    MapLayers::Enum layers;

};

#endif // MAPPARAMS_H
