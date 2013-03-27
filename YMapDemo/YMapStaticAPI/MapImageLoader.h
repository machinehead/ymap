#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QNetworkAccessManager>

class MapImageLoader : public QObject
{
    Q_OBJECT
public:
    explicit MapImageLoader(QObject *parent = 0);

    void startRequest(QUrl url);
    
signals:
    void error(const QString &description);
    void imageRetrieved(const QByteArray &imageData);

public slots:

private:
    QNetworkAccessManager qnam;
    QNetworkReply *httpReply;

private slots:
    void httpFinished();

};

#endif // IMAGELOADER_H