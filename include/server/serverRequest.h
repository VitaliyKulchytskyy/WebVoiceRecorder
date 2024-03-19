#pragma once
#include "ESPAsyncWebServer.h"
#include "frontend.h"
#include "handler.h"
#include "record.h"
#include "freertos/task.h"

/**
 * Send frontend to the client.
 * @param request request
 */
extern void frontRequest(AsyncWebServerRequest* request);

/**
 * Download a file with monitoring data from the g_webServer to a client.
 * @param request request
 */
extern void downloadRequest(AsyncWebServerRequest* request);

extern void recordingStartRequest(AsyncWebServerRequest* request);

extern void recordingStopRequest(AsyncWebServerRequest* request);