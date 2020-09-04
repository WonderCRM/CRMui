#include "CRMui.h"

// ********************* C A L L B A C K  *********************
void CRMui::btnCallback(String name, buttonCallback response) {
  if (btnui == name) {
    btnui = "";
    response();
  }
}

void CRMui::ui(void (*uiFunction) ()) {
  InterfaceElem = uiFunction;
}

void CRMui::update(void (*updateFunction) ()) {
  updateVol = updateFunction;
}

void CRMui::aliveArray(void (*aliveArrayFunction) ()) {
  update_alive = aliveArrayFunction;
}

void CRMui::getRequest(void (*getFunction) ()) {
  getPayload = getFunction;
}


// ********************* U I  *********************
void CRMui::app_name(String name) {
  mn = pg = 0;
  buf = String(F("{\"app_name\":\"")) + name + F("\",");
}

void CRMui::text(String id, String label) {
  buf += F("{\"html\":\"input\",");
  buf += String(F("\"id\":\"")) + id + F("\",");
  buf += F("\"type\":\"text\",");
  buf += String(F("\"value\":\"")) + param(id) + F("\",");
  buf += String(F("\"label\":\"")) + label + F("\"");
  buf += F("},");
}

void CRMui::number(String id, String label) {
  buf += F("{\"html\":\"input\",");
  buf += String(F("\"id\":\"")) + id + F("\",");
  buf += F("\"type\":\"number\",");
  buf += String(F("\"value\":\"")) + param(id) + F("\",");
  buf += String(F("\"label\":\"")) + label + F("\"");
  buf += F("},");
}

void CRMui::time(String id, String label) {
  buf += F("{\"html\":\"input\",");
  buf += String(F("\"id\":\"")) + id + F("\",");
  buf += F("\"type\":\"time\",");
  buf += String(F("\"value\":\"")) + param(id) + F("\",");
  buf += String(F("\"label\":\"")) + label + F("\"");
  buf += F("},");
}


void CRMui::date(String id, String label) {
  buf += F("{\"html\":\"input\",");
  buf += String(F("\"id\":\"")) + id + F("\",");
  buf += F("\"type\":\"date\",");
  buf += String(F("\"value\":\"")) + param(id) + F("\",");
  buf += String(F("\"label\":\"")) + label + F("\"");
  buf += F("},");
}

void CRMui::datetime(String id, String label) {
  buf += F("{\"html\":\"input\",");
  buf += String(F("\"id\":\"")) + id + F("\",");
  buf += F("\"type\":\"datetime-local\",");
  buf += String(F("\"value\":\"")) + param(id) + F("\",");
  buf += String(F("\"label\":\"")) + label + F("\"");
  buf += F("},");
}

void CRMui::range(String id, int min, int max, float step, String label, String units) {
  buf += F("{\"html\":\"input\",");
  buf += String(F("\"id\":\"")) + id + F("\",");
  buf += String(F("\"min\":\"")) + String(min) + F("\",");
  buf += String(F("\"max\":\"")) + String(max) + F("\",");
  buf += String(F("\"step\":\"")) + String(step) + F("\",");
  buf += F("\"type\":\"range\",");
  buf += String(F("\"value\":\"")) + param(id) + F("\",");
  buf += String(F("\"label\":\"")) + label + F("\",");
  buf += String(F("\"units\":\"")) + units + F("\"");
  buf += F("},");
}

void CRMui::email(String id, String label) {
  buf += F("{\"html\":\"input\",");
  buf += String(F("\"id\":\"")) + id + F("\",");
  buf += F("\"type\":\"email\",");
  buf += String(F("\"value\":\"")) + param(id) + F("\",");
  buf += String(F("\"label\":\"")) + label + F("\"");
  buf += F("},");
}

void CRMui::password(String id, String label) {
  buf += F("{\"html\":\"input\",");
  buf += String(F("\"id\":\"")) + id + F("\",");
  buf += F("\"type\":\"password\",");
  buf += String(F("\"value\":\"")) + param(id) + F("\",");
  buf += String(F("\"label\":\"")) + label + F("\"");
  buf += F("},");
}

void CRMui::option(String label, String value) {
  op += String(F("{\"label\":\"")) + label + F("\",\"value\":\"") + value + F("\"},");
}

void CRMui::select(String id, String label) {
  int lastIndex = op.length() - 1;
  op.remove(lastIndex);
  buf += F("{\"html\":\"select\",");
  buf += String(F("\"id\":\"")) + id + F("\",");
  buf += String(F("\"value\":\"")) + param(id) + F("\",");
  buf += String(F("\"label\":\"")) + label + F("\",");
  buf += String(F("\"options\":[")) + op + F("]");
  buf += F("},");
  op = F("");
}

void CRMui::checkbox(String id, String label) {
  buf += F("{\"html\":\"checkbox\",");
  buf += F("\"type\":\"checkbox\",");
  buf += String(F("\"id\":\"")) + id + F("\",");
  buf += String(F("\"value\":\"")) + param(id) + F("\",");
  buf += String(F("\"label\":\"")) + label + F("\"");
  buf += F("},");
}

void CRMui::color(String id, String label) {
  buf += F("{\"html\":\"input\",");
  buf += String(F("\"id\":\"")) + id + F("\",");
  buf += F("\"type\":\"color\",");
  buf += String(F("\"value\":\"")) + param(id) + F("\",");
  buf += String(F("\"label\":\"")) + label + F("\"");
  buf += F("},");
}

void CRMui::button(String id, String label, bool newline) {
  buf += F("{\"html\":\"button\",");
  buf += String(F("\"id\":\"")) + id + F("\",");
  buf += String(F("\"label\":\"")) + label + F("\",");
  buf += String(F("\"newline\":\"")) + String(newline) + F("\"");
  buf += F("},");
}

void CRMui::textarea(String id, String label) {
  buf += F("{\"html\":\"textarea\",");
  buf += String(F("\"id\":\"")) + id + F("\",");
  buf += String(F("\"value\":\"")) + param(id) + F("\",");
  buf += String(F("\"label\":\"")) + label + F("\"");
  buf += F("},");
}

void CRMui::alive_tabl(String id, String label, String value) {
  buf += F("{\"html\":\"alive_tabl\",");
  buf += String(F("\"id\":\"")) + id + F("\",");
  buf += String(F("\"value\":\"")) + value + F("\",");
  buf += String(F("\"label\":\"")) + label + F("\"");
  buf += F("},");
}

void CRMui::br(String size) {
  buf += F("{\"html\":\"br\",");
  buf += F("\"size\":\"");
  if (size == "") buf += F("0");
  else buf += size + F("px");
  buf += F("\"},");
}

void CRMui::hr() {
  buf += F("{\"html\":\"hr\"},");
}

void CRMui::menu(String name) {
  if (mn == 0) buf += F("\"menu\":[");
  else {
    int lastIndex = buf.length() - 1;
    buf.remove(lastIndex);
    buf.remove(lastIndex - 1);
    buf += F(",");
  }
  buf += String(F("\"")) + name + F("\"],");
  mn++;
}

void CRMui::page() {
  if (pg == 0) buf += F("\"content\":[[");
  else {
    int lastIndex = buf.length() - 1;
    buf.remove(lastIndex);
    buf += F("],[");
  }
  if (pg == mn) {
    int lastIndex = buf.length() - 1;
    buf.remove(lastIndex);
    buf.remove(lastIndex - 1);
    buf.remove(lastIndex - 2);
    buf += F("]]}");
  } else pg++;
}
