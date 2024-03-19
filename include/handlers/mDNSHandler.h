#pragma once
#include "ESPmDNS.h"
#include "settings.h"


/**
 * Setup LLMNR.
 * @attention the name of LLMNR is device_name (in settings.h)
 * @retval True - the LLMNR is initialized
 * @retval False - the LLMNR isn't initialized
 */
extern bool setupmDNS();
