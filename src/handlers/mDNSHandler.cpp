#include "handlers/mDNSHandler.h"


bool setupmDNS() {
    return MDNS.begin(device_name.c_str());
}
