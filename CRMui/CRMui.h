#ifndef CRMui_h
#define CRMui_h

#include "ArduinoJson.h"
#include <ESPAsyncWebServer.h>
#include "ArduinoOTA.h"

#ifdef ESP32
#include "SPIFFS.h"
#endif


class CRMui {
    typedef void (*buttonCallback) ();
    typedef void (*uiCallback) ();
    typedef void (*aliveArrayData) ();
    typedef void (*getCallback) ();
    typedef void (*updateCallback) ();

  public:
    void var(String key, String value);
    void led_conf(byte pin, bool vol, bool inversion);
    void led_use(bool use);
    void led(byte wmode);
    void wifi_start();
    void wifi_page();
    void aliveData_tabl (String id, String value);
    void aliveData_tabl (String id, String value, String rgb);
    String time_work();
    String param(String key);
    String param_get(String key);
    void getResponse(String resp);
    void reboot();
    void reset_cfg();
    void begin();
    void handle();
    void btnCallback(String name , buttonCallback response);

    void app_name(String name);
    void menu(String name);
    void page();

    void text(String id, String label);
    void password(String id, String label);
    void number(String id, String label);
    void time(String id, String label);
    void date(String id, String label);
    void datetime(String id, String label);
    void email(String id, String label);
    void range(String id, int min, int max, float step, String label);
    void range(String id, int min, int max, float step, String label, String units);
    void select(String id, String label);
    void option(String label, String value);
    void checkbox(String id, String label);
    void color(String id, String label);
    void button(String id, String label);
    void button(String id, String label, bool newline);
    void textarea(String id, String label);
    void alive_tabl(String id, String label);
    void alive_tabl(String id, String label, String value);
    void hr();
    void br();
    void br(String size);

    uiCallback InterfaceElem;
    void ui(void (*uiFunction) ());
    
    getCallback getPayload;
    void getRequest(void (*getFunction) ());

    aliveArrayData update_alive;
    void aliveArray(void (*aliveArrayFunction) ());

    updateCallback updateVol;
    void update (void (*updateFunction) ());

  private:
    void wifi_ap();
    void nonWifiVar();
    void load_cfg();
    void save_cfg();
    void autosave();

    String buf;                 //Callback ui
    String JsonGetRequest;      //Callback get
    String _getResponse;        //Response for GET
    String buf_alive;           //Callback alive

    bool wifimode = false;
    bool AutoSaveSt = false;
    uint32_t AutoSaveTimer;
    StaticJsonDocument<4096> cfg;
    String op = "";
    uint8_t mn, pg;
    String btnui = "";
    uint32_t UpTime_Timer, UpTime;

    //LED
    byte PIN_LED, LedFlashNum;
    bool inv, useled;
    uint32_t LongIntTimer, ShortIntTimer, BlinkTimer;
};

#endif
