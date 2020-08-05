#include "CRMui.h"
#define VER "___"

#define LED 2


CRMui crm;


void setup() {
  Serial.begin(115200);
  var();
  update_vol();

}


void update_vol() {

}


void loop() {
  crm.handle();
  crm.btnCallback(F("RBT"), Reboot_ESP);

}


// Перезагрузка ESP
void Reboot_ESP() {
  crm.reboot();
}
