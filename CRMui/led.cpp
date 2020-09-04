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


void CRMui::led(int wmode) {
  if (useled) {

    if (wmode < 0) {
      if (millis() - LongIntTimer >= 10000) {
        if (millis() - ShortIntTimer >= 100) {
          ShortIntTimer = millis();
          digitalWrite(PIN_LED, !digitalRead(PIN_LED));
          LedFlashNum++;
          if (LedFlashNum > (wifiAPmode ? 7 : 3)) {
            LongIntTimer = millis();
            LedFlashNum = 0;
          }
        }
      }
    } else {
      if (wmode == 0) digitalWrite(PIN_LED, (inv ? HIGH : LOW));
      else if (wmode == 1) digitalWrite(PIN_LED, (inv ? LOW : HIGH));
      else if (wmode > 1) {
        if (millis() - BlinkTimer >= wmode) {
          BlinkTimer = millis();
          digitalWrite(PIN_LED, !digitalRead(PIN_LED));
        }
      }
    }

  }
}
