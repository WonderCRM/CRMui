void interface() {
  crm.app_name(F("___"));          //Название устройства, отображается в меню.

  //Разделы меню
  crm.menu(F("Монитор"));
  crm.menu(F("Опции"));
  crm.menu(F("WiFi"));
  crm.page();

  //Соответствует 1 пунку меню
  crm.alive_tabl(UPTIME, F("Время работы"));
  crm.alive_tabl(WIFI_POWER, F("Мощность WiFi"));
  crm.alive_tabl(FREE_RAM, F("Свободно ОЗУ"));
  crm.alive_tabl(F("FW"), F("FW"), VER);
  crm.page();

  //Опции
  crm.text(WEB_AUTH_LOGIN, F("WEB Логин"));
  crm.password(WEB_AUTH_PASS, F("WEB пароль"));
  crm.hr();
  crm.button(BT_RESET, F("&#10007; Сброс настроек"));
  crm.page();

  //WiFi
  crm.wifi_page();
  crm.hr();
  crm.button(BT_REBOOT, F("&#8634; Перезагрузить"));
  crm.page();
}


void adata() {
  crm.aliveData_tabl (UPTIME, crm.time_work());
  int wfrssi = WiFi.RSSI();
  if (wfrssi < 0) crm.aliveData_tabl (WIFI_POWER, String(wfrssi) + F(" dBm   (") + String(map(constrain(wfrssi, -100, -40), -100, -40, 0, 100)) + F(" %)"));
  else crm.aliveData_tabl (WIFI_POWER, String(wfrssi) + F(" dBm"));
  crm.aliveData_tabl (FREE_RAM, String(ESP.getFreeHeap()) + F(" Бт"));

}


void dataReq() {
  //Serial.println(crm.param_get("text"));  //Вывод в терминал значения переменной "text", для запроса: http://IP/data?text=Тестовое сообщение
  //crm.getResponse(String(millis()));          //Возврат ответа в
}
