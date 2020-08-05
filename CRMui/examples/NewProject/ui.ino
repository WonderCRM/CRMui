void interface() {
  crm.app_name("___");          //Название устройства, отображается в меню.

  //Разделы меню
  crm.menu(F("Монитор"));
  //crm.menu(F("Опции"));
  crm.menu(F("WiFi"));
  crm.page();

  //Соответствует 1 пунку меню
  crm.alive_tabl(F("TW"), F("Время работы"));
  crm.alive_tabl(F("WFP"), F("Мощность WiFi"));
  crm.alive_tabl(F("RAM"), F("Свободно ОЗУ"));
  crm.alive_tabl(F("Ver"), F("FW"), String(VER));
  crm.page();

  //Опции

  //crm.page();

  //WiFi
  crm.wifi_page();
  crm.hr();
  crm.button(F("RBT"), F("&#8634; Перезагрузить"));
  crm.page();
}


void adata() {
  crm.aliveData_tabl (F("TW"), crm.time_work());
  int wfrssi = WiFi.RSSI();
  if (wfrssi < 0) crm.aliveData_tabl (F("WFP"), String(wfrssi) + F(" dBm   (") + String(map(constrain(wfrssi, -100, -40), -100, -40, 0, 100)) + F(" %)"));
  else crm.aliveData_tabl (F("WFP"), String(wfrssi) + F(" dBm"));
  crm.aliveData_tabl (F("RAM"), String(ESP.getFreeHeap()) + F(" Бт"));

}


void dataReq() {
  //Serial.println(crm.param_get("text"));  //Вывод в терминал значения переменной "text", для запроса: http://IP/data?text=Тестовое сообщение
  //crm.getResponse(String(millis()));          //Возврат ответа в
}
