#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>

class MapWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MapWidget(QWidget *parent = 0);
    
signals:
    
public slots:
    void imageDownloadError(const QString &description);
    void imageDownloadSuccess(const QByteArray &imageData);

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    QPixmap mapImage;

};

#endif // MAPWIDGET_H
