#pragma once
#include "ESPAsyncWebServer.h"
#include "handlers/wifiHandler.h"
#include "server/serverEvent.h"
#include "server/serverRequest.h"


/**
 * Setup g_events and request handlers to the web g_webServer.
 */
extern bool setupWebServer();