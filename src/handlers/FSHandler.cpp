#include "handlers/FSHandler.h"


bool setupFS() {
    return LittleFS.begin(true);
}

void fs_do(const char* filename, uint8_t* buffer, size_t bufferSize, const char* mode) {
    File file = LittleFS.open(filename, mode);
    file.write(buffer, bufferSize);
    file.close();

#ifdef VERBOSE_MODE
    Serial.printf("-> \'%s\' on SD file \"%s\":\n", mode, filename);
//    for(size_t i = 0; i < bufferSize; i++) {
//        Serial.print(*buffer[i], HEX);
//        Serial.print(" ");
//    }
//    Serial.println();
#endif
}

void fs_append(const char* filename, uint8_t* buffer, size_t bufferSize) {
    fs_do(filename, buffer, bufferSize, "a");

}

void fs_write(const char* filename, uint8_t* buffer, size_t bufferSize) {
    fs_do(filename, buffer, bufferSize, "w");
}