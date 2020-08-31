#include <CRMui.h>

#define LED 2     //Светодиод на плате, муляж устройства.

CRMui crm;

long cnt;         //тестовая переменная
bool checkbox_1;

void setup() {
  Serial.begin(115200);

  crm.led_conf(LED, LOW, true);               //LED индикация (GPIO, Начальное значение, Инверсия значения)

  //СИСТЕМНЫЕ ПЕРЕМЕННЫЕ, ID - CONST. При отсутствии создаются автоматом с дефолтными параметрами.
  crm.var(F("mWiFi"), F("STA"));             //Режим по умолчанию, (STA, AP, AP_STA).
  crm.var(F("SSID"), F("___"));              //Имя сети к которой подключаемся. Если не задан запускается режим AP.
  crm.var(F("Pass"), F("___"));              //Пароль от подключаемой сети.
  crm.var(F("WTCon"), F("120"));             //Время ожидания подключения к WiFi, сек.
  crm.var(F("AP_SSID"), F("CRMui"));         //Имя точки доступа, она же идентификатор для OTA.
  crm.var(F("AP_Pass"), F(""));              //Пароль точки доступа.

  //ПОЛЬЗОВАТЕЛЬСКИЕ ПЕРЕМЕННЫЕ
  crm.var(F("TEXT"), F("Текст текст текст"));
  crm.var(F("password_input"), F("Pass-1234"));
  crm.var(F("number_input"), F("5645454"));
  crm.var(F("time_input"), F("13:45"));
  crm.var(F("dt"), F("2019-09-20"));
  crm.var(F("dtat"), F("2019-09-20T00:01"));
  crm.var(F("email_input"), F("my-email@bk.ru"));
  crm.var(F("range_input"), F("45"));
  crm.var(F("select_input"), F("1"));
  crm.var(F("checkbox_1"), F("true"));
  crm.var(F("color_input"), F("#ff00ff"));
  crm.var(F("textarea_input"), F("Просто не учи физику в школе и вся твоя жизнь будет наполнена чудесами, и волшебством."));


  //ОБЯЗАТЕЛЬНЫЕ МЕТОДЫ
  crm.ui(interface);          //Интерфейс UI.
  crm.update(update_vol);     //Вызывается при обновлении параметров через Web
  crm.getRequest(dataReq);    //GET запросы. Вида:   http://IP/data?text=Тестовое сообщение
  crm.aliveArray(adata);      //Динамические данные на странице. Обязательно
  crm.begin();                //Старт Фреймворка
  update_vol();
}


void update_vol() {
  checkbox_1 = crm.param(F("checkbox_1")) == F("true") ? true : false;
  Serial.println(String(F("Использовать подсветку: ")) + (checkbox_1 ? F("ДА") : F("НЕТ")));
  Serial.println(F("Параметры обновлены"));
}


void loop() {
  crm.handle();
  crm.btnCallback(F("btn_print"), test_print);
  crm.btnCallback(F("btn_invert"), test_invert);
  crm.btnCallback(F("btn_reboot"), rbt);
}


//Обработка GET запроса
void dataReq() {
  Serial.println(crm.param_get("text"));  //Вывод в терминал значения переменной "text", для запроса: http://IP/data?text=Тестовое сообщение
  crm.getResponse(String(millis()));      //Возврат ответа в Web
}


void interface() {
  crm.app_name("Проект-15");          //Название устройства, отображается в меню.

  //Разделы меню
  crm.menu(F("Главная"));             //Пункт 1
  crm.menu(F("Настройки"));           //Пункт 2
  crm.menu(F("WiFi"));                //Пункт 3
  crm.page();

  //Соответствует 1 пунку меню
  crm.alive_tabl(F("TimeWork"), F("Время работы"));
  crm.alive_tabl(F("Dev_IP"), F("IP адрес"), WiFi.localIP().toString());
  crm.alive_tabl(F("Dev_MAC"), F("MAC адрес"), String(WiFi.macAddress()));
  crm.alive_tabl(F("WFP"), F("Мощность WiFi"));
  crm.alive_tabl(F("RAM"), F("Свободно ОЗУ"));
  crm.alive_tabl(F("ledst"), F("Состояние LED"));
  crm.alive_tabl(F("PrintTerm"), F("Количество нажатий"));
  crm.hr();
  crm.button(F("btn_print"), F("Печать в терминал"), false);
  crm.button(F("btn_invert"), F("Переключить LED"));
  crm.button(F("btn_reboot"), F("&#8634; Перезагрузить"));
  crm.page();

  //Соответствует 2 пунку меню
  crm.text(F("TEXT"), F("Какой то текст"));
  crm.password(F("password_input"), F("Пароль от всего"));
  crm.number(F("number_input"), F("Только числа"));
  crm.time(F("time_input"), F("Будильник"));
  crm.date(F("dt"), F("Дата мероприятия"));
  crm.datetime(F("dtat"), F("Дата и время включения"));
  crm.email(F("email_input"), F("Адрес электронки"));
  crm.range(F("range_input"), 0, 100, 0.1, F("Ползунок с шагом"), F("°C"));
  crm.option(F("Комедии"), F("0"));
  crm.option(F("Боевики"), F("1"));
  crm.option(F("Ужасы"), F("2"));
  crm.select(F("select_input"), F("Что любишь?"));
  crm.color(F("color_input"), F("Цвет подсветки ОЗУ"));
  crm.checkbox(F("checkbox_1"), F("Использовать подсветку"));
  crm.checkbox(F("checkbox_2"), F("Авто режим"));
  crm.checkbox(F("checkbox_3"), F("Использовать LED индикацию"));
  crm.br();     //Строчный интервал, размер в пикселях. По умолчанию = 10
  crm.textarea(F("textarea_input"), F("Текстовое поле для большого ввода текста прямо в него"));
  crm.page();

  //Соответствует 3 пунку меню
  crm.wifi_page();
  crm.hr();
  crm.button(F("btn_reboot"), F("&#8634; Перезагрузить"));
  crm.page();

  //И т.д.
}


//Выполняется по запросу обрадного вызова.
void adata() {
  crm.aliveData_tabl (F("TimeWork"), crm.time_work(), F("0f0"));    //Вставка данных по ID для crm.alive_tabl (ID, ДАННЫЕ, ЦВЕТ)
  int wfrssi = WiFi.RSSI();
  crm.aliveData_tabl (F("WFP"), String(wfrssi) + F(" dBm   (") + String(map(wfrssi, -100, -40, 0, 100)) + F(" %)"));
  crm.aliveData_tabl (F("RAM"), String(ESP.getFreeHeap()) + F(" Бт"), crm.param(F("color_input")));
  !digitalRead(LED) ? crm.aliveData_tabl (F("ledst"), F("ВКЛ"), F("f00")) : crm.aliveData_tabl (F("ledst"), F("ВЫКЛ"), F("0f0"));
  crm.aliveData_tabl (F("PrintTerm"), String(cnt));
}


void rbt() {
  crm.reboot();       // Перезагрузка ESP
}


//************************************ Т Е С Т   Ф У Н К Ц И И ************************************
void test_print() {
  Serial.println(String(F("Количество нажатий: ")) + String(++cnt));
}

void test_invert() {
  crm.led_use((crm.param(F("checkbox_3")) == F("true") ? true : false));
  digitalWrite(LED, !digitalRead(LED));
  Serial.println(String(F("LED: ")) + String(digitalRead(LED) ? F("ВЫКЛ") : F("ВКЛ")));
}
