#include "MapImageLoader.h"

#include <QtNetwork>
#include "MapParams.h"
#include <QPixmap>

MapImageLoader::MapImageLoader(QObject *parent) :
    QObject(parent),
    httpReply(0)
{
}

void MapImageLoader::mapImageRequest(const MapParams &params)
{
    startRequest(params.toUrl());
}

void MapImageLoader::startRequest(QUrl url)
{
    if(httpReply != 0) {
        disconnect(httpReply, SIGNAL(finished()), this, SLOT(httpFinished()));
        httpReply->deleteLater();
        httpReply = 0;
    }

    httpReply = qnam.get(QNetworkRequest(url));
    connect(httpReply, SIGNAL(finished()),
            this, SLOT(httpFinished()));
}

void MapImageLoader::httpFinished()
{
    if (httpReply->error()) {
        emit error(tr("Download failed: %1.")
                       .arg(httpReply->errorString()));
    } else {
        QByteArray imageData = httpReply->readAll();
        QPixmap image;
        image.loadFromData(imageData);
        emit imageRetrieved(image);
    }

    httpReply->deleteLater();
    httpReply = 0;
}


