// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>

// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial XBee(2, 3); // RX, TX

extern "C"{
    #include "src/Xpollute/Xpollute.h"
}

// variable global
  humidityType testPayloadHumidity = 65;
  uint8_t startBit = 0x0D;
  uint8_t id[] = { 0x0C, 0xF2 };
  xpollute_message_t testMessageHumidity;
  uint8_t *containerMsgHumidity;
  uint8_t testArray[8]; // Input simulation

void setup(){
  // Set up both ports at 9600 baud. This value is most important
  // for the XBee. Make sure the baud rate matches the config
  // setting of your XBee.
  XBee.begin(57600);
  Serial.begin(57600);
}

void loop(){
  // put your main code here, to run repeatedly:

  construct_xpollute_humidity(&testMessageHumidity, startBit, id, testPayloadHumidity);
  deconstruct_message(&containerMsgHumidity, &testMessageHumidity);
  free(testMessageHumidity.payload);

  Serial.println("Mengirimkan Array");

  for (int i = 0; i<8; i++) {
    testArray[i] = containerMsgHumidity[i];
    Serial.write(testArray[i]);
    XBee.write(testArray[i]);
  }
  
  Serial.println();
  
  free(containerMsgHumidity);

delay (1000);

}
