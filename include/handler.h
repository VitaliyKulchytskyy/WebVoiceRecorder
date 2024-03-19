#pragma once
#include "handlers/mDNSHandler.h"
#include "handlers/webServerHandler.h"
#include "handlers/wifiHandler.h"
#include "handlers/FSHandler.h"
#include "settings.h"


using setup_t = bool(*)();

struct handler_t {
public:
    setup_t pSetup;
    String successMsg;
    String errorMsg;

public:
    /**
     * Setup handler, and log down the output status (system log).
     * @flags VERBOSE_MODE
     */
    void setup() const;
};

/**
 * The table of handlers setup and their log messages.
 * @attention ORDER SENSITIVE!!!
 * @flags USE_LLMNR
 * @example Starts with hardware initialization, and ends up with software parts.
 */
extern const handler_t handlers[];
// constexpr size_t handlerSize = sizeof(handlers) / sizeof(handlers[0]);


/**
 * Setup all handlers in the handler folder
 * @flags VERBOSE_MODE
 */
extern void setupHandlers();

/// needs to be called in the loop to process handlers
extern void loopHandlers();