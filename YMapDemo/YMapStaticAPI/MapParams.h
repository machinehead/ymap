#ifndef MAPPARAMS_H
#define MAPPARAMS_H

#include <QString>
#include <QSize>

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
    MapParams(double lat, double lon, const QSize &size, int zoom, MapLayers::Enum layers);

    void setSize(const QSize &newSize);

    QString toUrl() const;

private:
    double lat;
    double lon;
    QSize size;
    int zoom;
    MapLayers::Enum layers;

};

#endif // MAPPARAMS_H
