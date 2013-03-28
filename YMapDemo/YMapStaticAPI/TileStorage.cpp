#include "TileStorage.h"
#include "MapImageLoader.h"

TileStorage::TileStorage(QObject *parent) :
    QObject(parent),
    currentMapParams(MapParams::empty())
{
}

void TileStorage::mapImageRequest(const MapParams &params)
{
    currentMapParams = params;
    currentResult = QPixmap( currentMapParams.getSize().asQSize() );

    MapImageLoader *loader = new MapImageLoader(params, &qnam, this);
    connect(loader, SIGNAL(finished(const MapImageLoader*)),
            this, SLOT(tileRequestCompleted(const MapImageLoader*)));
    loader->run();
}

void TileStorage::tileRequestCompleted(const MapImageLoader *loader)
{
    emit imageRetrieved(loader->getResult());
}
