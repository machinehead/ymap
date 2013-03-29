#ifndef MAPIMAGELOADER_H
#define MAPIMAGELOADER_H

// Объект класса осуществляет загрузку одного изображения (тайла).

#include <QNetworkAccessManager>
#include "MapParams.h"
#include <QPixmap>

class MapParams;

class MapImageLoader : public QObject
{
    Q_OBJECT

public:
    // params - параметры карты, которую нужно загрузить
    // qnam - разделяемый объектами MapImageLoader объект QNetworkAccessManager
    explicit MapImageLoader(const MapParams &params, QNetworkAccessManager *qnam, QObject *parent = 0);

    // Запуск запроса специально вынесен из конструктора, дабы можно было успеть привязать сигналы.
    void run();

    // Получить параметры запроса.
    MapParams getParams() const { return params; }
    // Получить картинку. Имеет смысл вызывать только в обработчике сигнала finished().
    QPixmap getResult() const;

signals:
    // Сообщение об ошибке.
    void error(const MapImageLoader *loader);
    // Получено изображение.
    void finished(MapImageLoader *loader);

private:
    MapParams params;

    // qnam - разделяемый объектами MapImageLoader объект QNetworkAccessManager.
    // Невладеющий указатель.
    QNetworkAccessManager *qnam;
    // Http-запрос текущего объекта.
    QNetworkReply *httpReply;

    // Сообщение об ошибке, если запрос закончился ошибкой.
    QString errorMessage;
    // Результат запроса, если запрос отработал успешно.
    QPixmap resultImage;

private slots:
    void httpFinished();

};

#endif // MAPIMAGELOADER_H
