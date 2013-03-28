#ifndef TILESTORAGE_H
#define TILESTORAGE_H

#include <QObject>
#include "MapParams.h"
#include <QPixmap>

class TileStorage : public QObject
{
    Q_OBJECT
public:
    explicit TileStorage(QObject *parent = 0);
    
signals:
    void imageRetrieved(const QPixmap &image);

public slots:
    void mapImageRequest(const MapParams &params);

private:
    MapParams currentRequest;
    QPixmap currentResult;
};

#endif // TILESTORAGE_H
