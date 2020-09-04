#include "CRMui.h"


void CRMui::save_cfg() {
  String pre_config;
  serializeJson(cfg, pre_config);
#ifdef ESP8266
  SPIFFS.open(F("/config.json"), "w").print(pre_config);
#else
  SPIFFS.open(F("/config.json"), FILE_WRITE).print(pre_config);
#endif
  Serial.println(F("Конфиг сохранен."));
}


void CRMui::autosave() {
  if (AutoSaveSt && millis() - AutoSaveTimer >= 30000) {
    save_cfg();
    AutoSaveSt = false;
  }
}


void CRMui::load_cfg() {
#ifdef ESP8266
  String pre_config = SPIFFS.open(F("/config.json"), "r").readString();
  if (pre_config == "") {
    Serial.println(F("Конфиг пуст, настройки сброшены по умолчанию."));
    save_cfg();
  } else {
    deserializeJson(cfg, pre_config);
    Serial.println(F("Конфиг загружен."));
  }
#else
  File file = SPIFFS.open(F("/config.json"));
  if (!file || file.isDirectory()) {
    Serial.println(F("Конфиг пуст, настройки сброшены по умолчанию."));
    save_cfg();
  } else {
    deserializeJson(cfg, file);
    file.close();
    Serial.println(F("Конфиг загружен."));
  }
#endif
}


void CRMui::reset_cfg() {
  SPIFFS.remove(F("/config.json"));
  ESP.restart();
}
