#include "aliases.h"
#include <CRMui.h>
#define VER F("___")

#define LED 2


CRMui crm;



void setup() {
  var();
  update_vol();
  crm.setWebAut(crm.param(WEB_AUTH_LOGIN), crm.param(WEB_AUTH_PASS));    //Авторизация в Web интерфейсе
}



void update_vol() {

}



void loop() {
  crm.handle();
  crm.btnCallback(BT_REBOOT, ESP_reboot);
  crm.btnCallback(BT_RESET, ESP_reset);

}



// Перезагрузка ESP
void ESP_reboot() {
  crm.reboot();
}



// Сброс настроек ESP
void ESP_reset() {
  crm.reset_cfg();
}
