#include "TriggerHelper.h"

unsigned long markerOffsetMs = 16;
unsigned long markerDurationMs = 2;


void initCamera() {
    pinMode(LT_FOCUS, OUTPUT);
    pinMode(LT_SHUTTER, OUTPUT);
    digitalWrite(LT_FOCUS, 0);
    digitalWrite(LT_SHUTTER, 0);
}


void focusBegin() {
  digitalWrite(LT_FOCUS, 1);
}

void focusEnd() {
  digitalWrite(LT_FOCUS, 0);
}

void shutterBegin() {
  digitalWrite(LT_SHUTTER, 1);
}

void shutterEnd() {
  digitalWrite(LT_SHUTTER, 0);
}
