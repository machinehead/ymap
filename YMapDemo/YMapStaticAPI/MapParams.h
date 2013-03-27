#ifndef MAPPARAMS_H
#define MAPPARAMS_H

#include <QString>

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
    MapParams(double lat, double lon, int sizeX, int sizeY, int zoom, MapLayers::Enum layers);

    QString toUrl() const;

private:
    double lat;
    double lon;
    int sizeX;
    int sizeY;
    int zoom;
    MapLayers::Enum layers;

};

#endif // MAPPARAMS_H
