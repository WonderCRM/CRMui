#include "CRMui.h"

#ifdef ESP8266
ESP8266WiFiMulti wifiMulti;
#else
WiFiMulti wifiMulti;
#endif


void CRMui::wifi_ap() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(param(F("AP_SSID")).c_str(), param(F("AP_Pass")).c_str());
  wifiAPmode = true;
  Serial.println(String(F("\nЗапуск Wi-Fi в режиме AP: ")) + param(F("AP_SSID")));
}


void CRMui::wifi_start() {
  String wfm = param(F("mWiFi"));
  String ssid_array = param(F("SSID"));
  String pass_array = param(F("Pass"));
  WiFi.persistent(false);

  if (wfm == F("STA") || wfm == F("AP_STA")) {
    if (wfm == F("AP_STA")) {
      WiFi.softAP(param(F("AP_SSID")).c_str(), param(F("AP_Pass")).c_str());
      WiFi.mode(WIFI_AP_STA);
      Serial.println(String(F("\nЗапуск WiFi в режиме AP: ")) + param(F("AP_SSID")) + F("\nIP адрес AP: ") + WiFi.softAPIP().toString());
    } else WiFi.mode(WIFI_STA);

    Serial.print(F("\nПодключение к WiFi: "));
    int fromSSID = 0, toSSID = 0, fromPASS = 0, toPASS = 0;
    while (toSSID != -1) {
      String ssid_vol = "", pass_vol = "";

      toSSID = ssid_array.indexOf(F(","), fromSSID);
      if (toSSID != -1) {
        ssid_vol = ssid_array.substring(fromSSID, toSSID);
        fromSSID = toSSID + 1;
      } else ssid_vol = ssid_array.substring(fromSSID);

      toPASS = pass_array.indexOf(F(","), fromPASS);
      if (toPASS > 0 || fromPASS <= pass_array.length() - 1) {
        pass_vol = pass_array.substring(fromPASS, toPASS);
        if (toPASS > 0) fromPASS = toPASS + 1;
        else fromPASS = pass_array.length();
      }

      Serial.print(F("\t")); Serial.print(ssid_vol);
      if (ssid_vol != "") wifiMulti.addAP(ssid_vol.c_str(), pass_vol.c_str());
    }
    Serial.println();
    uint32_t connTimer, WTCon = millis() + param(F("WTCon")).toInt() * 1000UL;
    while (true) {
      if (useled) {
        digitalWrite(PIN_LED, !digitalRead(PIN_LED));
        delay(100);
        digitalWrite(PIN_LED, !digitalRead(PIN_LED));
      }
      if (millis() - connTimer >= 1000) {
        connTimer = millis();
        Serial.print(F("."));
        if (wifiMulti.run() == WL_CONNECTED) {
          Serial.println(String(F("\nПодключение к WiFi сети ")) + WiFi.SSID().c_str() + F(" выполнено!\nIP адрес устройства: ") + WiFi.localIP().toString());
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
  } else wifi_ap();
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
