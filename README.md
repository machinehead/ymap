ymap
====

Демонстрация отображения карты, получаемой через Static API Яндекс.Карт.
Написано под Qt 5.0.1, собиралось под Win32 на MinGW.

В процессе разработки обнаружено подозрение на ошибку в Static API: кажется, что слой с 
изображением карты смещён по вертикали относительно запрашиваемых координат, причём смещение зависит от высоты 
информации о копирайтах. Из-за этого не работает совмещение частей карты по вертикали.

По горизонтали совмещение тайлов выглядит идеально.

Решение нуждается в ряде довольно очевидных доработок (если решить проблему, описанную выше):
* Загрузку и отрисовку тайлов стоит вынести в отдельный поток.
* При скроллировании карты имеет смысл масштабировать текущее изображение карты, а потом уже дополнять его новыми 
тайлами.

