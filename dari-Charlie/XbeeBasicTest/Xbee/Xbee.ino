// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>

// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial XBee(2, 3); // RX, TX

extern "C"{
    #include "src/RoketLink/RoketLink.h"
}

uint8_t testArray[8];
uint8_t bufferInput;

altType extractedAltitude = 0;
uint8_t state = 0;
int i = 0;

void setup() {
  // put your setup code here, to run once:
  XBee.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (XBee.available())
  { // If data comes in from XBee, send it out to serial monitor
    bufferInput = XBee.read();
    Serial.write(bufferInput);
    Serial.println("");

    switch (state) {
      case 0:
        {
          if (bufferInput == 0x0D) {
            testArray[0] = bufferInput;
          }
          state++;
          i = 1;
          break;
        }
      case 1:
        {
          if (bufferInput != 0x0D) {
            testArray[i] = bufferInput;
            state++;
            i++;
          } else {
            state = 0;
          }
          break;
        }
      default:
        state = 0;
        break;
    }

    if (i > 7) {
      Serial.println("Message Retrieved");
      rocketlink_message_t deconstructedMessage;
      reconstruct_rocketlink(&deconstructedMessage, testArray);  
      extractedAltitude = extract_altitude(deconstructedMessage.payload);
      Serial.println(extractedAltitude);
      i = 0;
    }
  }

  
}
