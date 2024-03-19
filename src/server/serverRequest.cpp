#include "server/serverRequest.h"


void frontRequest(AsyncWebServerRequest* request) {
    request->send(200, "text/html", index_html);
}

void downloadRequest(AsyncWebServerRequest* request) {
    if (request->hasParam("filename")) {
        String full_filename = "/" + request->getParam("filename")->value();

        if (LittleFS.exists(full_filename)) {
            File file = LittleFS.open(full_filename, "r");
            AsyncWebServerResponse *response = request->beginResponse(LittleFS, full_filename, "application/octet-stream");
            request->send(response);

        #ifdef VERBOSE_MODE
            Serial.print("Download file: " );
            Serial.println(full_filename);
        #endif
            file.close();
        } else {
            request->send(404, "text/plain",
                          "404: the file \"" + full_filename + "\" doesn't exist on the device.");

        #ifdef VERBOSE_MODE
            Serial.println("The file doesn't exist");
        #endif
        }
    }
}

/*
void recordingRequest(AsyncWebServerRequest* request) {
    if (request->hasParam("rec")) {
        String inputMessage = request->getParam("rec")->value();
        if(inputMessage == "true") {
            startRecording();
        } else if(inputMessage == "false") {
            const record_t& out = stopRecording();
            request->send(200, "text/html", out.toString());
        }
    }
}*/

TaskHandle_t Task2_Handle;
String currFilename = "";
unsigned long duration = 0;

void recordingStartRequest(AsyncWebServerRequest* request) {
    if (request->hasParam("filename")) {
        currFilename = "/" + request->getParam("filename")->value();
        Serial.println(currFilename);
    } else {
        return;
    }

    duration = millis();
    xTaskCreatePinnedToCore(startRecording, "startRecording", 48000, NULL, tskIDLE_PRIORITY, &Task2_Handle, 0);
}

void test(void *pvParameter) {
    stopRecording();
    gRecord.toString();
    uint8_t* buf = nullptr;
    size_t bufSize = 0;
    serialize(gRecord, &buf, bufSize, SLICING_PERIOD, duration);
    fs_write(currFilename.c_str(), buf, bufSize);
    vTaskDelete(NULL);
}

void recordingStopRequest(AsyncWebServerRequest* request) {
    duration = millis() - duration;
    vTaskDelete(Task2_Handle);
    xTaskCreatePinnedToCore(test, "test", 24000, NULL, tskIDLE_PRIORITY, NULL, 0);
//    stopRecording();
//    vTaskEndScheduler();
//    gRecord.toString();
//    const record_t& out = stopRecording();
//    request->send(200, "text/html", out.toString());
}