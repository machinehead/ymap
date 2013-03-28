#ifndef MAPIMAGELOADER_H
#define MAPIMAGELOADER_H

#include <QNetworkAccessManager>

class MapParams;

class MapImageLoader : public QObject
{
    Q_OBJECT
public:
    explicit MapImageLoader(QObject *parent = 0);

signals:
    void error(const QString &description);
    void imageRetrieved(const QPixmap &image);

public slots:
    void mapImageRequest(const MapParams &params);

private:
    QNetworkAccessManager qnam;
    QNetworkReply *httpReply;

    void startRequest(QUrl url);

private slots:
    void httpFinished();

};

#endif // MAPIMAGELOADER_H
