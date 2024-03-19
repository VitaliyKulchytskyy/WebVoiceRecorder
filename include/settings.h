#pragma once
#include "Arduino.h"
#include "password.h"


/* --- General Settings --- */
/// The name of the device
extern String device_name;

/* --- WiFi & FTP Settings --- */
/// Enable using of LLMNR (it only works on the Windows (Phone & Desktop), Linux-based OS?)
#define USE_LLMNR
/// Web g_webServer port
#define SERVER_PORT     80
#define UPDATE          1000

/* --- Record Settings --- */
#define SLICING_PERIOD  1000000

/* --- Serial Setup --- */
#define SERIAL_BAUD     9600

/* --- Debug --- */
/// For unit tests. Disable VERBOSE_MODE.
//#define UNIT_TEST_MODE
/// If AP_MODE is defined the device will be working
/// as access point otherwise it will connect to the wifi
#ifndef UNIT_TEST_MODE
    /// Print verbose debug information into the console
    #define VERBOSE_MODE
#endif