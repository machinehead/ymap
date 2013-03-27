#include "MapImageLoader.h"

#include <QtNetwork>

MapImageLoader::MapImageLoader(QObject *parent) :
    QObject(parent)
{
}

void MapImageLoader::startRequest(QUrl url)
{
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
        emit imageRetrieved(imageData);
    }

    httpReply->deleteLater();
    httpReply = 0;
}
