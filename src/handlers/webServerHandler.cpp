#include "handlers/webServerHandler.h"


bool setupWebServer() {
    g_events.onConnect(onClientConnect);
    g_webServer.on("/", HTTP_GET, frontRequest);
    g_webServer.on("/download", HTTP_GET, downloadRequest);
    g_webServer.on("/recordingStart", HTTP_GET, recordingStartRequest);
    g_webServer.on("/recordingStop", HTTP_GET, recordingStopRequest);
    g_webServer.addHandler(&g_events);
    g_webServer.begin();
    return true;
}