// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>

// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial XBee(2, 3); // RX, TX


extern "C"{
    #include "src/RoketLink/RoketLink.h"
}


// variable global
  altType testPayloadAltitude = 200;
  uint8_t startBit = 0x0D;
  uint8_t id[] = { 0x0C, 0xF2 };
  rocketlink_message_t testMessageAlt;
  uint8_t *containerMsgAlt;
  uint8_t testArray[8]; // Input simulation

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  XBee.begin(9600);
 
}

void loop() {
  // put your main code here, to run repeatedly:

  construct_rocketlink_altitude(&testMessageAlt, startBit, id, testPayloadAltitude);
  deconstruct_message(&containerMsgAlt, &testMessageAlt);
  free(testMessageAlt.payload);

  for (int i = 0; i<8; i++) {
    testArray[i] = containerMsgAlt[i];
    Serial.write(testArray[i]);
    XBee.write(testArray[i]);
  }
  free(containerMsgAlt);
  
  delay(500);
}

