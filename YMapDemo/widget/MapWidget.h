#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QNetworkAccessManager>
#include <QWidget>
#include <QUrl>

class MapWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MapWidget(QWidget *parent = 0);
    
signals:
    
public slots:

protected:
    virtual void paintEvent(QPaintEvent *event);

private slots:
    void httpFinished();

private:
    QPixmap mapImage;

    QNetworkAccessManager qnam;
    QNetworkReply *httpReply;

    void startRequest(QUrl url);

};

#endif // MAPWIDGET_H
