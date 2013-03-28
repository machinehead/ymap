#include "TileStorage.h"

TileStorage::TileStorage(QObject *parent) :
    QObject(parent),
    currentRequest(MapParams::empty())
{
}

void TileStorage::mapImageRequest(const MapParams &params)
{
    currentRequest = params;
    currentResult = QPixmap( currentRequest.getSize() );
}
