#include "server/serverEvent.h"


AsyncEventSource g_events("/events");
uint64_t m_timerEvent = 0;

void onClientConnect(AsyncEventSourceClient* client) {
    if(client->lastId()) {
        #ifdef VERBOSE_MODE
            Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
        #endif
    }
}

void onUpdateEvent() {
    const uint64_t thisMillis = millis();

    if(thisMillis - m_timerEvent > UPDATE) {
//        g_events.send(String(g_tempIn.tempC).c_str(), "temp_inside", thisMillis);

        m_timerEvent = thisMillis;
    }
}