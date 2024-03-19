#pragma once
#include "settings.h"
#include "ESPAsyncWebServer.h"


extern AsyncEventSource g_events;

/**
 * Invoke whenever a client has connected to the g_webServer.
 * @flags VERBOSE_MODE
 * @param client client data
 */
extern void onClientConnect(AsyncEventSourceClient* client);

extern void onUpdateEvent();