#include "record.h"

hw_timer_t *timer;
record_t gRecord;

void newSlice() {
    gRecord.addSlice();
}

void setupTimer() {
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &newSlice, true);
    timerAlarmWrite(timer, SLICING_PERIOD, true);
}

void startRecording(void *pvParameter) {
    gRecord = record_t();
    timerAlarmEnable(timer);
    while(1) {
        const int value = analogReadFiltered(34, 680);

        if(value == 0)
            continue;

        gRecord.addValue(value);
        Serial.println(value);
    }
}

void stopRecording() {
    timerAlarmDisable(timer);
}

void serialize(const record_t& record,
               uint8_t** buf,
               size_t& sizeOut,
               uint64_t slicingT,
               unsigned long duration)
{
    const size_t shift = sizeof(slicingT) + sizeof(duration);
    sizeOut = record.size() + shift;
    *buf = new uint8_t[sizeOut];
    memcpy(*buf, &slicingT, sizeof(slicingT));
    memcpy(&(*buf)[sizeof(slicingT)], &duration, sizeof(duration));
    record.serialize(&(*buf)[shift]);
}

void deserialize(record_t& record,
                 const uint8_t* buf,
                 uint64_t& slicingT,
                 unsigned long& duration)
{
    slicingT = ptov<uint64_t>(buf);
    duration = ptov<unsigned long>(&buf[sizeof(slicingT)]);
    const size_t shift = sizeof(slicingT) + sizeof(duration);
    record.deserialize(&buf[shift]);
}