#include "CRMui.h"


void CRMui::wifi_ap() {
  Serial.println(String(F("\nЗапуск Wi-Fi в режиме AP: ")) + param(F("AP_SSID")));
  WiFi.softAP(param(F("AP_SSID")).c_str(), param(F("AP_Pass")).c_str());
  wifimode = true;
 }


void CRMui::wifi_start() {
  if (param(F("mWiFi")) == F("STA")) {
#ifdef ESP8266
    if (WiFi.getPersistent() == true) WiFi.persistent(false);
#else
	WiFi.persistent(false);
#endif
    WiFi.mode(WIFI_STA);
    WiFi.persistent(true);
    Serial.println(String(F("\nПодключение к WiFi: ")) + param(F("SSID")));
    WiFi.begin(param(F("SSID")).c_str(), param(F("Pass")).c_str());

    uint32_t connTimer, WTCon = millis() + param(F("WTCon")).toInt() * 1000;
    while (true) {
      if (useled) {
        digitalWrite(PIN_LED, !digitalRead(PIN_LED));
        delay(100);
        digitalWrite(PIN_LED, !digitalRead(PIN_LED));
      }
      if (millis() - connTimer >= 1000) {
        connTimer = millis();
        Serial.print(F("."));
        if (WiFi.status() == WL_CONNECTED) {
          Serial.println(String(F("\nПодключение к WiFi сети выполнено!\nIP адрес устройства: ")) + WiFi.localIP().toString());
          break;
        }
        if (millis() > WTCon) {
          WiFi.persistent(false);
          WiFi.mode(WIFI_OFF);
          delay(100);
          WiFi.persistent(true);
          wifi_ap();
          break;
        }
      }
      delay(100);
    }

  } else  {
#ifdef ESP8266
    if (WiFi.getPersistent() == true) WiFi.persistent(false);
#else
	WiFi.persistent(false);
#endif
    WiFi.mode(WIFI_AP);
    WiFi.persistent(true);
    wifi_ap();
  }
}


void CRMui::wifi_page() {
  option(F("Клиент"), F("STA"));
  option(F("Точка доступа"), F("AP"));
  select(F("mWiFi"), F("Режим работы WiFi"));
  range(F("WTCon"), 10, 600, 1, F("Ожидать подключения не более"), F("сек."));
  text(F("SSID"), F("Название сети"));
  password(F("Pass"), F("Пароль сети"));
  text(F("AP_SSID"), F("Название точки доступа"));
  password(F("AP_Pass"), F("Пароль точки доступа"));
}
