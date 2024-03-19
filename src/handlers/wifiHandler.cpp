#include "handlers/wifiHandler.h"


AsyncWebServer g_webServer(SERVER_PORT);
String g_ip = "0.0.0.0";
String* pg_ip = &g_ip;

bool setupWifi() {
    WiFi.hostname(device_name);

    WiFi.begin(ssid, password);
    int i = 0;
    while (WiFi.status() != WL_CONNECTED) {
        #ifdef VERBOSE_MODE
            delay(1000);
            Serial.print('.');
        #endif
    }
    g_ip = WiFi.localIP().toString();
    g_webServer.begin();

    return true;
}
