﻿# CRMui WebFramework для esp8266
![PROJECT_PHOTO](https://github.com/WonderCRM/CRMui/blob/master/screen.png)


## Описание проекта
Данный CRMui WebFramework построен на [JeeUI2](https://github.com/jeecrypt/JeeUI2), проект изначально почти полностью переписан, исправлены ошибки, добавлены новые возможности.

P.S. я не программист, это моё хобби, поэтому изящность кода и правильность написания того или иного участка не гарантирую.
Конструктивная критика, а также предложения по улучшению приветствуется.

* [Моя Телега](https://t.me/User624)
* [Мой Mail](mailto:crm.dev@bk.ru)
* [Донат (Благодарность)](https://donatepay.ru/don/crmdev)

## Железо
Совместим с микроконтроллерами на ESP8266. В идеале лучше использовать с модулем ESP-12F (Wemos D1 mini).

## Папки
- **libraries** - библиотеки, используемые в данном проекте (распаковать);
- **CRMui** - сам CRMui WebFramework.

## Как установить CRMui WebFramework
* [Первые шаги с Arduino](http://alexgyver.ru/arduino-first/) - ультра подробная статья по началу работы с Arduino, ознакомиться первым делом!
* Скачать архив с проектом
> На главной странице проекта (где ты читаешь этот текст) вверху справа зелёная кнопка **Clone or download**, вот её жми, там будет **Download ZIP**
* Установить (скопировать) библиотеки из скаченного архива папки libraries в
```C:\Program Files (x86)\Arduino\libraries\``` (Windows x64)  
```C:\Program Files\Arduino\libraries\``` (Windows x86)
* **Подключить внешнее питание 5 Вольт**
* Подключить плату к компьютеру
* Файл/Настройки, вставить ссылку http://arduino.esp8266.com/stable/package_esp8266com_index.json в текст-бокс для дополнительных ссылок для менеджера плат
* Открыть Инструменты/Плата/Менеджер плат…, найти esp8266 by ESP8266 Community, установить последнюю версию (корректность работы проверялась на 2.7.4)
* Открыть Инструменты, настроить Плату, Порт и другие параметры как на скриншоте
* Загрузить прошивку
![PROJECT_PHOTO](https://github.com/WonderCRM/CRMui/blob/master/sett.png)


## Программная часть (Methods)
Использование CRMui можно посмотреть в примере, идущем с библиотекой.

### Setup()
* Настройка индикации подключенного или встроенного светодиода\n
```
led_conf(byte pin, bool vol, bool inversion); pin - порт подключения, vol - начальное состояние (LOW / HIHG), inversion - инверсия порта (true / false);
``` 
если не используется, LED индикатор не активен

* Записывает в параметр нужное значение
```
var(String key, String value); key - имя параметра, value - значение
```
при изменении через WEB, авто сохранение в энергонезависимую память через 30 сек, во время работы конфиг находится в ОЗУ

* Название функции, формирующей WEB интерфейсе
```
ui(interface); interface - название функции
```
может быть любым

* Название функции, которая вызывается при обновлении параметров через Web
```
update(update_vol); update_vol - название функции
```
может быть любым

* Название функции, которая вызывается при входящем GET запросе
```
getRequest(dataReq); dataReq - название функции
```
может быть любым (вид запроса:   http://IP/data?text=какойто текст)

* Название функции, которая вызывается при запросе обновления динамических данных в WEB
```
aliveArray(adata); adata - название функции
```
может быть любым

* Инициализация остальных параметров и функций CRMui WebFramework
```begin();```

### loop()
```handle();```
необходимо для нормального функционирования WebFramework
```btnCallback(String name , String response);``` name - ID кнопки, response - имя вызываемой функции
имя вызываемой функции любое

### interface()
* Название устройства
```app_name(String name);``` name - название
также отображается в меню
 
* Пункты меню и разделы
```menu(String name);``` name - название пункта меню
```page();``` - отделение разделов друг от друга

* Поле для динамических данных
```alive_tabl(String id, String label);``` id - ID элемента, label - название
```alive_tabl(String id, String label, String value);``` id - ID элемента, label - название, value - значение по умолчанию
поля элементов в виде таблицы

* Поле для ввода текста
```text(String id, String label);``` id - ID элемента, label - название

* Поле ввода пароля
```password(String id, String label);``` id - ID элемента, label - название
значение скрыто точками

* Поле ввода цифр
```number(String id, String label);``` id - ID элемента, label - название

* Поля ввода времени и даты
```time(String id, String label);``` id - ID элемента, label - название
```date(String id, String label);``` id - ID элемента, label - название
```datetime(String id, String label);``` id - ID элемента, label - название

* Поле ввода email адреса
```email(String id, String label);``` id - ID элемента, label - название

* Элемент ползунок
```range(String id, int min, int max, float step, String label);```  - тип значений String, int, int, float, String
id - ID элемента, min - значение от, max - значение до, step - шаг (десятичные) ,label - название
```range(String id, int min, int max, float step, String label, String units);``` id - ID элемента, min - значение от, max - значение до, step - шаг ,label - название, units - размерность
шаг может быть десятичным, размерность - указывается размерность значения, не обязательный параметр

* Элемент список
```option(String label, String value);``` label - название, value - значение
массив списка, закрывается select
```select(String id, String label);``` id - ID элемента, label - название
элементы закрывающий список, находится после всех option

* Элемент переключатель
```checkbox(String id, String label);``` id - ID элемента, label - название
возвращает строку true или false


* Элемент выбора цвета
```color(String id, String label);``` id - ID элемента, label - название
возвращает строку  формата #XXXXXX

* Кнопка
```button(String id, String label);``` id - ID элемента, label - название
```button(String id, String label, bool newline);``` id - ID элемента, label - название, newline - перевод на новую строку
перевод на новую строку, если не задано, то true

* Поле ввода многострочного текста
```textarea(String id, String label);``` id - ID элемента, label - название
много лучше не вводить, его значение, как и значение остальных элементов хранится в ОЗУ

* Элементы разделения
```hr();```
горизонтальная полоса
```br();```
строчный интервал
```br(String size);```
интервал с размером в пикселях, но не менее строки

*Страница настроек WiFi 
```wifi_page();```

### Динамические данные (aliveArray)

* Обновление динамических данных в WEB 
```aliveData_tabl (id, value);``` - тип значений String, String
```aliveData_tabl (id, value, rgb);``` - тип значений String, String, String
id - ID элемента alive_tabl, value - название элемента, rgb - цвет, если не указан, то белый (формат: XXXXXX или XXX)

### Остальные методы
Следующие методы используются в любой функции

* Режим работы LED индикатора
```led(wmode);``` - находится в loop();
wmode - режим работы, 0 - ВЫКЛ, 1 - ВКЛ, 10 - быстро мигать (300 мс), любое другое значение отображает режим работы (2е мигание - STA, 3е мигание - AP)

* Использовать LED индикатор (совместно с led_conf)
```led_use(bool use);```
use - что то вроде ВКЛ / ВЫКЛ, тип bool (true / false)

* Метод возвращает строку со временем работы устройства
```time_work();``` - тип возвращаемого значения String

* Получить значение параметра по его ключу
```param(key);``` - тип возвращаемого значения String

* Получить значение параметра GET запроса по его ключу
 ```param_get(String key);``` - тип возвращаемого значения String
 
 * Сообщение ответа в WEB на GET запрос
```getResponse(resp);``` - тип возвращаемого значения String
resp - строка ответа

* Системные методы
```reboot();``` - перезагрузка модуля
```reset_cfg();``` - сброс настроек и удаление файла с конфигурацией из энергонезависимой памяти

## FAQ
### Основные вопросы
В: Как скачать с этого грёбаного сайта? 
О: На главной странице проекта (где ты читаешь этот текст) вверху справа зелёная кнопка **Clone or download**, вот её жми, там будет **Download ZIP**

В: Скачался какой-то файл .zip, куда его теперь? 
О: Это архив. Можно открыть стандартными средствами Windows, но думаю у всех на компьютере установлен WinRAR, архив нужно правой кнопкой и извлечь.

В: Я совсем новичок! Что мне делать с Ардуиной, где взять все программы? 
О: Читай и смотри видос http://alexgyver.ru/arduino-first/

В: Сколько стоит? 
О: Бесплатно, но если ходите отблагодарить, ссылка на Донат в самом начале.
