#include <TFT_eSPI.h>
#include <SPI.h>

#include "SonyWired.h"
//#include "OM1BLE.h"

#define BUTTON_LEFT 0
#define BUTTON_RIGHT 35

const unsigned int markers[] = {22, 21, 32, 33, 25, 26, 27};
int markerCount = sizeof(markers) / sizeof(markers[0]);

#define START_LED 2

void waitFor(unsigned int pin) {
  int c = digitalRead(pin);
  while(c == digitalRead(pin)){};  
}

TFT_eSPI tft = TFT_eSPI(135, 240); // Invoke custom library




void setup()
{
    Serial.begin(115200);
    Serial.println("ESP32 T-Display Start");

    tft.init();
    tft.fillScreen(TFT_BLACK);
    tft.setRotation(1);
    tft.setTextSize(2);
    tft.setTextColor(TFT_GREEN);
    tft.setCursor(0, 0);
    tft.setTextSize(2);


    pinMode(BUTTON_LEFT, INPUT);
    pinMode(BUTTON_RIGHT, INPUT);

    for(int i=0; i<markerCount; i++) {
      pinMode(markers[i], OUTPUT);
      digitalWrite(markers[i], 1);
    }

    initCamera();

    pinMode(START_LED, OUTPUT);
    digitalWrite(START_LED, 1);

}


void resetMarker() {
    for(int i=0; i<markerCount; i++) {
      digitalWrite(markers[i], 0);
    }
}
void updateMarker(int c) {
    digitalWrite(markers[c], 1);
}


void loop()
{  
  waitFor(BUTTON_LEFT);

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0*20); // right, down
  tft.print("Offset: ");
  tft.print(markerOffsetMs);
  tft.print("ms");
  tft.setCursor(0, 1*20); // right, down
  tft.print("Interval: ");
  tft.print(markerDurationMs);
  tft.print("ms");


  unsigned long triggerBegin = 0;
  unsigned long triggerEnd = 0;
  unsigned long nextPoint = 0;

  resetMarker();
  digitalWrite(START_LED, 0);

  // Prep trigger
  focusBegin();
  delay(5000);

  // Start trigger
  digitalWrite(START_LED, 1);
  triggerBegin = micros();
  shutterBegin();
  triggerEnd = micros();
  nextPoint = triggerBegin;

  
  nextPoint = nextPoint + (markerOffsetMs * 1000);
  while(micros() < nextPoint){}

  for(int i=0; i<markerCount; i++) {
    updateMarker(i);
    nextPoint = nextPoint + (markerDurationMs * 1000);
    while(micros() < nextPoint){}
  }

  // Finish trigger  
  delay(100);
  shutterEnd();
  delay(100);
  focusEnd();

  unsigned long triggerDuration = triggerEnd - triggerBegin;
  
  tft.setCursor(0, 2*20); // right, down
  tft.print("Trigger: ");
  tft.print(triggerDuration);
  tft.print("us");
  
}
