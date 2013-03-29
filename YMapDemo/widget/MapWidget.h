#ifndef MAPWIDGET_H
#define MAPWIDGET_H

// Виджет, отображающий карту.

#include <QWidget>
#include "MapParams.h"

class MapWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MapWidget(QWidget *parent = 0);
    
    // Запуск отображения карты в виджете.
    void requestImage();
signals:
    // Виджет отправляет этот сигнал, когда изменились параметры изображения и нужно получить новое.
    void mapImageRequest(const MapParams &params);

public slots:
    // Сюда можно сообщать об ошибках при загрузке изображений. Сейчас это отключено в связи с переходом на кеш тайлов.
    void imageDownloadError(const QString &description);
    // Уведомление виджета о том, что получен новый вариант изображения. Имеет смысл добавить сюда прямоугольник,
    // который нужно обновить, и обновлять отображение только его.
    void mapImageUpdate(const QPixmap &image);

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent * event);
    virtual void wheelEvent(QWheelEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    QPixmap mapImage;
    MapParams mapParams;

    bool isDragging;
    QPoint dragStartPos;

    void dragMap(const QPoint &pos);

};

#endif // MAPWIDGET_H
