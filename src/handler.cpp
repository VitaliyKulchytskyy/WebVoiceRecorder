#include "handler.h"


const handler_t handlers[] = {
        handler_t{.pSetup     = setupWifi,
                  .successMsg = "The WiFi is initialized",
                  .errorMsg   = "The WiFi isn't initialized!"},

#ifdef USE_LLMNR
        handler_t{.pSetup     = setupmDNS,
                  .successMsg = "mDNS: http://" + device_name + "/",
                .  errorMsg   = "Error setting up mDNS responder!"},
#endif

        handler_t{.pSetup     = setupWebServer,
                  .successMsg = "The Web Server is initialized.",
                  .errorMsg   = "The Web Server isn't initialized!"},

        handler_t{.pSetup     = setupFS,
                  .successMsg = "The FS is initialized.",
                  .errorMsg   = "The FS isn't initialized!"},
};

void handler_t::setup() const {
    bool status = this->pSetup();

    #ifdef VERBOSE_MODE
        Serial.println(status ? successMsg : errorMsg);
    #endif
}

void setupHandlers() {
    for (const auto& handler : handlers)
        handler.setup();
}