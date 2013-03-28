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

    void setSize(const QSize &_size);

    int getZoom() const { return zoom; }
    void setZoom(int _zoom);

    // Изменить координаты центра карты на delta (в экранной декартовой системе координат) с учётом текущего масштаба.
    void movePixels(QPoint delta);

    // Получить URL запроса к Static API, по которому можно загрузить изображение карты по текущим параметрам.
    QString toUrl() const;

private:
    double lon;
    double lat;
    QSize size;
    int zoom;
    MapLayers::Enum layers;

};

#endif // MAPPARAMS_H
