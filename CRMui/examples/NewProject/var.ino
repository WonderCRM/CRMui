//ПАРАМЕТРЫ ПО УМОЛЧАНИЮ
void var() {
  crm.led_conf(LED, LOW, true);              //LED индикация (GPIO, Начальное значение, Инверсия значения)

  //СИСТЕМНЫЕ, ID - CONST
  crm.var(F("mWiFi"), F("AP"));              //Режим по умолчанию, (STA, AP, AP_STA).
  crm.var(F("WTCon"), F("120"));             //Время ожидания подключения к WiFi, сек.
  crm.var(F("SSID"), "___");                 //Имя сети к которой подключаемся. Если не задан запускается режим AP.
  crm.var(F("Pass"), "___");                 //Пароль от подключаемой сети.
  crm.var(F("AP_SSID"), F("CRMui"));         //Имя точки доступа, она же идентификатор для OTA.
  crm.var(F("AP_Pass"), F("0000-0000"));     //Пароль точки доступа.


  //ПОЛЬЗОВАТЕЛЬСКИЕ
  crm.var(WEB_AUTH_LOGIN, F(""));
  crm.var(WEB_AUTH_PASS, F(""));


  //ОБЯЗАТЕЛЬНЫЕ МЕТОДЫ
  crm.ui(interface);                         //Интерфейс UI. Обязательно
  crm.update(update_vol);                    //Вызывается при обновлении параметров через Web
  crm.getRequest(dataReq);                   //GET запросы. Вида:   http://IP/data?ПАРАМЕТР=ЗНАЧЕНИЕ&иТ.Д.
  crm.aliveArray(adata);                     //Динамические данные на странице. Обязательно
  crm.begin();                               //Старт Фреймворка
}
