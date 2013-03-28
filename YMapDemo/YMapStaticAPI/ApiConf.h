#ifndef APICONF_H
#define APICONF_H

// Настройки Static API Яндекс.Карт

// "Левый верхний угол мира"
// http://api.yandex.ru/maps/doc/theory/concepts/coordinates.xml
#define APICONF_WORLD_ORIGIN_LON (-180)
#define APICONF_WORLD_ORIGIN_LAT (90)

// Степень двойки, определяющая размер тайла в пикселях.
#define APICONF_TILE_SIZE_PWR (8)

#define APICONF_URL_BASE ("http://static-maps.yandex.ru/1.x/?%1")

// Нижний и верхний пределы масштаба.
#define APICONF_ZOOM_MIN (0)
#define APICONF_ZOOM_MAX (17)

// Ограничения на размер изображения, получаемого от Static API
#define APICONF_SIZE_X_MAX (650)
#define APICONF_SIZE_Y_MAX (450)

#endif // APICONF_H
