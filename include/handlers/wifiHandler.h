#pragma once
#include "settings.h"
#include "ESPAsyncWebServer.h"


/// Async Web Server
extern AsyncWebServer g_webServer;
/// The IP of WiFi
extern String g_ip;
extern String* pg_ip;

/**
 * Setup WiFi.
 * @flags AP_MODE
 * @return IP address
 */
extern bool setupWifi();