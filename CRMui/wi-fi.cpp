#include "CRMui.h"


void CRMui::wifi_ap() {
  Serial.println(String(F("\nЗапуск Wi-Fi в режиме AP: ")) + param(F("AP_SSID")));
  WiFi.softAP(param(F("AP_SSID")).c_str(), param(F("AP_Pass")).c_str());
  wifimode = true;
}


void CRMui::wifi_start() {
  WiFi.persistent(false);
  String wfm = param(F("mWiFi"));
  if (wfm == F("STA") || wfm == F("AP_STA")) {
    if (wfm == F("AP_STA")) {
      WiFi.softAP(param(F("AP_SSID")).c_str(), param(F("AP_Pass")).c_str());
      WiFi.mode(WIFI_AP_STA);
      Serial.println(String(F("\nЗапуск WiFi в режиме AP: ")) + param(F("AP_SSID")) + F("\nIP адрес AP: ") + WiFi.softAPIP().toString());
      Serial.println(String(F("\nПодключение к: ")) + param(F("SSID")));
    } else {
      WiFi.mode(WIFI_STA);
      Serial.println(String(F("\nПодключение к WiFi: ")) + param(F("SSID")));
    }
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
          WiFi.mode(WIFI_OFF);
          wifi_ap();
          break;
        }
      }
      delay(100);
    }

  } else  {
    WiFi.mode(WIFI_AP);
    wifi_ap();
  }
}


void CRMui::wifi_page() {
  option(F("Клиент"), F("STA"));
  option(F("Точка доступа"), F("AP"));
  option(F("Точка доступа + Клиент"), F("AP_STA"));
  select(F("mWiFi"), F("Режим работы WiFi"));
  range(F("WTCon"), 10, 600, 1, F("Ожидать подключения не более"), F("сек."));
  text(F("SSID"), F("Название сети"));
  password(F("Pass"), F("Пароль сети"));
  text(F("AP_SSID"), F("Название точки доступа"));
  password(F("AP_Pass"), F("Пароль точки доступа"));
}
