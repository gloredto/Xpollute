// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>

// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial XBee(2, 3); // RX, TX

extern "C"{
    #include "src/Xpollute/Xpollute.h"
}

uint8_t testArray[8];
uint8_t bufferInput;

humidityType extractedHumidity = 0;
tempType extractedTemperature = 0;
mq2Type extractedMq2 = 0;
mq7Type extractedMq7 = 0;
int humidityRouter1, temperatureRouter1, mq2Router1, mq7Router1;
uint8_t state = 0;
int i = 0;
int sensor;

void setup() {
  // put your setup code here, to run once:
  XBee.begin(57600);
  Serial.begin(57600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensor = 4;
  if (XBee.available()){
      for (i=0 ; i <8 ; i++){
      bufferInput = XBee.read();
      testArray[i] = bufferInput;
      }
      Serial.write(testArray[i]);
      sensor = testArray[3];
      //Serial.println(sensor);
         
      switch (sensor){
        case 0:
          Serial.println("Sensor Humidity = ");
          //Serial.write(testArray[i]);      // statement
          xpollute_message_t deconstructedMessageHumidity;
          reconstruct_xpollute(&deconstructedMessageHumidity, testArray);  
          extractedHumidity = extract_humidity(deconstructedMessageHumidity.payload);
          Serial.print("Message = ");
          Serial.println(extractedHumidity);
          //humidityRouter1 = extractedHumidity;

          
          Serial.println();
          
          break;
        case 1:
          Serial.println("Sensor Temperature = ");
          //Serial.write(testArray[i]);      // statement
          xpollute_message_t deconstructedMessageTemp;
          reconstruct_xpollute(&deconstructedMessageTemp, testArray);  
          extractedTemperature = extract_humidity(deconstructedMessageTemp.payload);
          Serial.print("Message = ");
          Serial.println(extractedTemperature);
          
          
          Serial.println();
          break;
        case 2:
          Serial.println("Sensor MQ2 = ");
          //Serial.write(testArray[i]);      // statement
          xpollute_message_t deconstructedMessageMq2;
          reconstruct_xpollute(&deconstructedMessageMq2, testArray);  
          extractedMq2 = extract_humidity(deconstructedMessageMq2.payload);
          Serial.print("Message = ");
          Serial.println(extractedMq2);
          
          
          Serial.println();
          break;
        case 3:
          Serial.println("Sensor MQ7 = ");
          //Serial.write(testArray[i]);      // statement
          xpollute_message_t deconstructedMessageMq7;
          reconstruct_xpollute(&deconstructedMessageMq7, testArray);  
          extractedMq7 = extract_humidity(deconstructedMessageMq7.payload);
          Serial.print("Message = ");
          Serial.println(extractedMq7);
          
          
          Serial.println();
          break;
        default:
          Serial.print("tidak ada input");
          Serial.println();
                // statement
          break;
      }
  } 
  
  delay(5000);
}
