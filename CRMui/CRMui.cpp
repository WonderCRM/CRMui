#include "CRMui.h"
#define CRMui_VER "2.0.0611a"


#include "web/page.html.h"
#include "web/update.html.h"
#include "web/maker.js.h"
#include "web/ui.js.h"
#include "web/chkbx.css.h"
#include "web/main.css.h"
#include "web/pure-min.css.h"
#include "web/favicon.ico.h"

AsyncWebServer server(80);
uint32_t timer_handle;


void CRMui::var(String key, String value) {
  cfg[key] = value;
#ifdef DBG
  Serial.println(String(F("WRITE: ")) + key + F(" = ") + value);
#endif
}


String CRMui::param(String key) {
  String value = cfg[key];
#ifdef DBG
  Serial.println(String(F("READ: ")) + key + F(" = ") + value);
#endif
  if (value == F("null")) {
    var(key, "");
    return "";
  } else return value;
}


String CRMui::param_get(String key) {
  StaticJsonDocument<535> InComingData;
  deserializeJson(InComingData, JsonGetRequest);
  return InComingData[key];
}

void CRMui::getResponse(String resp) {
  _getResponse = resp;
}
void CRMui::getResponse(String resp, bool torus) {
  if(torus) _getResponse = utf_to_rus(resp);
  else _getResponse = resp;
}


void CRMui::aliveData_tabl (String id, String value) {
  if (buf_alive == "") buf_alive = F(" {\"");
  else buf_alive.replace(F("}"), F(",\""));
  buf_alive += id;
  buf_alive += F("\":[\"");
  buf_alive += value;
  buf_alive += F("\", \"fff\"]}");
}
void CRMui::aliveData_tabl (String id, String value, String rgb) {
  if (buf_alive == "") buf_alive = F(" {\"");
  else buf_alive.replace(F("}"), F(",\""));
  buf_alive += id;
  buf_alive += F("\":[\"");
  buf_alive += value;
  buf_alive += F("\", \"");
  rgb.replace(F("#"), F(""));
  buf_alive += rgb;
  buf_alive += F("\"]}");
}


String CRMui::time_work() {
  String time_w;
  if (UpTime / 86400 % 365 != 0) time_w = String(F("Дней: ")) + String(UpTime / 86400 % 365) + F(",  ");
  time_w += String(UpTime / 3600 % 24) + F(":");
  if ((UpTime / 60 % 60) < 10) time_w += F("0");
  time_w += String(UpTime / 60 % 60) + F(":");
  if ((UpTime % 60) < 10) time_w += F("0");
  time_w += String(UpTime % 60);
  return time_w;
}


void CRMui::begin() {
  Serial.println(String(F("\nCRMui WebFramework ver:")) + String(CRMui_VER));
  SPIFFS.begin();
  nonWifiVar();
  load_cfg();

  String config;
  serializeJson(cfg, config);
  Serial.println(String(F("CONFIG: ")) + config);

  wifi_start();

  server.on("/post", HTTP_POST, [this](AsyncWebServerRequest * request) {
    uint8_t params = request->params();
    AsyncWebParameter *p;
    for (uint8_t i = 0; i < params; i++) {
      p = request->getParam(i);
      if (p->name().indexOf(F("BTN_")) != -1) btnui = p->name().substring(4);
      else {
        var(p->name(), p->value());
        updateVol();
        AutoSaveSt = true;
        AutoSaveTimer = millis();
      }
    }
    request->send(200);
  });

  server.on("/data", HTTP_GET, [this](AsyncWebServerRequest * request) {
    uint32_t LeadTime = micros();
    uint8_t params = request->params();
    if (params) {
      AsyncWebParameter *p;
      JsonGetRequest = F("{\"");
      for (uint8_t i = 0; i < params; i++) {
        p = request->getParam(i);
        JsonGetRequest += (p->name() + F("\":\"") + p->value());
        i < params - 1 ? JsonGetRequest += F("\",\"") : JsonGetRequest += F("\"}");
      }
      getPayload();
      JsonGetRequest = "";
    }
    request->send(200, F("text/plain"), _getResponse != "" ? _getResponse : (String(F("Request: ")) + (params ? F("OK") : F("is empty!")) + F("\nLead time: ") + String(micros() - LeadTime) + F(" mks")));
    _getResponse = "";
  });

  server.on("/echo", HTTP_GET, [this](AsyncWebServerRequest * request) {
    InterfaceElem();
    request->send_P(200, F("text/plain"), buf.c_str());
    buf = "";
#ifdef DBG
    Serial.println(String(F("RAM ECHO: ")) + String(ESP.getFreeHeap()));
#endif
  });

  server.on("/alive", HTTP_GET, [this](AsyncWebServerRequest * request) {
    update_alive();
    request->send_P(200, F("text/plain"), buf_alive.c_str());
    buf_alive = "";
  });


  server.on("/", HTTP_ANY, [](AsyncWebServerRequest * request) {
    AsyncWebServerResponse *response = request->beginResponse_P(200, F("text/html"), page_html, page_html_size);
    response->addHeader(F("Content-Encoding"), F("gzip"));
    request->send(response);
  });

  server.on("/update", HTTP_GET, [](AsyncWebServerRequest * request) {
    AsyncWebServerResponse *response = request->beginResponse_P(200, F("text/html"), update_html, update_html_size);
    response->addHeader(F("Content-Encoding"), F("gzip"));
    request->send(response);
  });

  server.on("/js/maker.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    AsyncWebServerResponse *response = request->beginResponse_P(200, F("application/javascript"), maker_js, maker_js_size);
    response->addHeader(F("Content-Encoding"), F("gzip"));
    request->send(response);
  });

  server.on("/js/ui.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    AsyncWebServerResponse *response = request->beginResponse_P(200, F("application/javascript"), ui_js, ui_js_size);
    response->addHeader(F("Content-Encoding"), F("gzip"));
    request->send(response);
  });

  server.on("/css/chkbx.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    AsyncWebServerResponse *response = request->beginResponse_P(200, F("text/css"), chkbx_css, chkbx_css_size);
    response->addHeader(F("Content-Encoding"), F("gzip"));
    request->send(response);
  });

  server.on("/css/main.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    AsyncWebServerResponse *response = request->beginResponse_P(200, F("text/css"), main_css, main_css_size);
    response->addHeader(F("Content-Encoding"), F("gzip"));
    request->send(response);
  });

  server.on("/css/pure-min.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    AsyncWebServerResponse *response = request->beginResponse_P(200, F("text/css"), puremin_css, puremin_css_size);
    response->addHeader(F("Content-Encoding"), F("gzip"));
    request->send(response);
  });

  server.on("/update", HTTP_POST, [](AsyncWebServerRequest * request) {
    AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", !Update.hasError() ? "OK" : "FAIL");
    response->addHeader(F("Connection"), F("close"));
    request->send(response);
  }, [](AsyncWebServerRequest * request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
    if (!index) {
      Serial.println(String(F("Обновление запущено. Ожидайте завершения около минуты.\nФайл прошивки: ")) + filename);
      #ifndef ESP32
      Update.runAsync(true);
      #endif
      if (!Update.begin((ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000)) Update.printError(Serial);
    }
    if (!Update.hasError() && Update.write(data, len) != len) Update.printError(Serial);
    if (final) {
      if (Update.end(true)) {
        Serial.println(F("Обновление завершено удачно, ESP перезагружается!"));
        delay(200);
        ESP.restart();
      } else Update.printError(Serial);
    }
  });

  server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest * request) {
    AsyncWebServerResponse *response = request->beginResponse_P(200, F("image/x-icon"), favicon_ico, favicon_ico_size);
    request->send(response);
  });

  server.begin();

  ArduinoOTA.setHostname(param(F("AP_SSID")).c_str());
  ArduinoOTA.begin();

  Serial.println(String(F("CRMui RUNING\tFree RAM: ")) + String(ESP.getFreeHeap()));

  UpTime = millis() / 1000;
}


void CRMui::handle() {
  ArduinoOTA.handle();

  led(50);

  if (millis() - UpTime_Timer >= 1000) {
    UpTime_Timer = millis();
    UpTime++;
    autosave();
  }
}


void CRMui::nonWifiVar() {
  if (param(F("WTCon")) == "") var(F("WTCon"), F("120"));
  if (param(F("mWiFi")) == "") var(F("mWiFi"), F("AP"));
  if (param(F("AP_SSID")) == "") var(F("AP_SSID"), F("CRMui"));
  if (param(F("AP_Pass")) == "") var(F("AP_Pass"), "");
}


void CRMui::reboot() {
  if (AutoSaveSt) save_cfg();
  ESP.restart();
}
