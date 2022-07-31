#include "BLEHelper.h"

unsigned long markerOffsetMs = 100;
unsigned long markerDurationMs = 5;


// Olympus OM-1 Camera Service
static BLEUUID OM1ServiceUUID("adc505f9-4e58-4b71-b8ca-983bb8c73e4f");
BLERemoteService* pOM1Service;

// Olympus OM-1 Main Command Characteristic
static BLEUUID OM1CommandCharacteristicUUID("82f949b4-f5dc-4cf3-ab3c-fd9fd4017b68");
BLERemoteCharacteristic* pOM1CommandCharacteristic;


unsigned char counter = 1;

unsigned char initializeCommand[] = {
  0x01,
  0x00, // counter
  0x09, // payload length + 3
  0x0C, // command_identifier_1
  0x01,
  0x02, // command_identifier_2
  // Begin Payload
  0x38,0x30,0x30,0x32,0x38,0x36,
  // End Payload
  0x00, // checksum
  0x00
};
void sendInitializeCommand() {
  initializeCommand[1] = counter;
  counter = counter + 1;
  initializeCommand[12] = 0;
  for(int i=3; i<12; i++) {
    initializeCommand[12] = initializeCommand[12] + initializeCommand[i];
  }
  pOM1CommandCharacteristic->writeValue(initializeCommand, sizeof(initializeCommand));
}

unsigned char shutterCommand[] = {
  0x01,
  0x00, // counter
  0x04, // payload length + 3
  0x04, // command_identifier_1
  0x01,
  0x0F, // command_identifier_2
  // Begin Payload
  0x00,
  // End Payload
  0x00, // checksum
  0x00
};
const unsigned char SHUTTER_DOWN = 0x05;
const unsigned char SHUTTER_UP = 0x06;
void sendShutterCommand(unsigned char operation) {
  shutterCommand[1] = counter;
  counter = counter + 1;
  shutterCommand[6] = operation;
  shutterCommand[7] = 0;
  for(int i=3; i<7; i++) {
    shutterCommand[7] = shutterCommand[7] + shutterCommand[i];
  }
  pOM1CommandCharacteristic->writeValue(shutterCommand, sizeof(shutterCommand));
}




void initCamera() {
  Serial.println("Starting Arduino BLE Client application...");
  BLEDevice::init("");
  pOM1Service = scanAndConnect(OM1ServiceUUID);
  pOM1CommandCharacteristic = pOM1Service->getCharacteristic(OM1CommandCharacteristicUUID);
  delay(500);
  sendInitializeCommand();
  delay(500);
}


void focusBegin() {

}

void focusEnd() {

}

void shutterBegin() {
  sendShutterCommand(SHUTTER_DOWN);
}

void shutterEnd() {
  sendShutterCommand(SHUTTER_UP);
}
