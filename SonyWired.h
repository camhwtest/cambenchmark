#include "TriggerHelper.h"

unsigned long markerOffsetMs = 16;
unsigned long markerDurationMs = 2;

// SONY
#define SHUTTER TIP_RED
#define FOCUS RING_WHITE

void initCamera() {
    pinMode(FOCUS, OUTPUT);
    pinMode(SHUTTER, OUTPUT);
    digitalWrite(FOCUS, 1);
    digitalWrite(SHUTTER, 1);
}


void focusBegin() {
  digitalWrite(FOCUS, 0);
}

void focusEnd() {
  digitalWrite(FOCUS, 1);
}

void shutterBegin() {
  digitalWrite(SHUTTER, 0);
}

void shutterEnd() {
  digitalWrite(SHUTTER, 1);
}
