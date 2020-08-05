#include "CRMui.h"


void CRMui::led_conf(byte pin, bool vol, bool inversion) {
  PIN_LED = pin;
  inv = inversion;
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, (inv ? !vol : vol));
  useled = true;
}


void CRMui::led_use(bool use) {
  useled = use;
}


void CRMui::led(byte wmode) {
  if (useled) {

    switch (wmode) {
      case 0:
        digitalWrite(PIN_LED, (inv ? HIGH : LOW));
        break;
        
      case 1:
        digitalWrite(PIN_LED, (inv ? LOW : HIGH));
        break;
        
      case 10: {
          if (millis() - BlinkTimer >= 300) {
            BlinkTimer = millis();
            digitalWrite(PIN_LED, !digitalRead(PIN_LED));
          }
        }
        break;
        
      default: {
          if (millis() - LongIntTimer >= 10000) {
            if (millis() - ShortIntTimer >= 70) {
              ShortIntTimer = millis();
              digitalWrite(PIN_LED, !digitalRead(PIN_LED));
              LedFlashNum++;
              if (LedFlashNum > (wifimode ? 7 : 3)) {
                LongIntTimer = millis();
                LedFlashNum = 0;
              }
            }
          }
        }
    }

  }
}
