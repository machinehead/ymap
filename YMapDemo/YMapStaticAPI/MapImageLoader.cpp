#include "MapImageLoader.h"

#include <QtNetwork>
#include "MapParams.h"
#include <QPixmap>

MapImageLoader::MapImageLoader(const MapParams &_params, QNetworkAccessManager *_qnam, QObject *parent) :
    QObject(parent),
    params(_params),
    qnam(_qnam),
    httpReply(0)
{
    Q_ASSERT( qnam != 0 );
}

void MapImageLoader::run()
{
    QString url = params.toUrl();
    qDebug() << url;
    httpReply = qnam->get(QNetworkRequest(url));

    connect(httpReply, SIGNAL(finished()), this, SLOT(httpFinished()));
}

QPixmap MapImageLoader::getResult() const
{
    return resultImage;
}

void MapImageLoader::httpFinished()
{
    if (httpReply->error()) {
        errorMessage = tr("Download failed: %1.").arg(httpReply->errorString());
        emit error(this);
    } else {
        QByteArray imageData = httpReply->readAll();
        resultImage.loadFromData(imageData);
        emit finished(this);
    }

    httpReply->deleteLater();
    httpReply = 0;
}


