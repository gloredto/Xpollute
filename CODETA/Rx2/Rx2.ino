#include <SPI.h>
#include <Ethernet.h>

// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>

//Ethernet
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
 
// Enter the IP address for Arduino, as mentioned we will use 192.168.0.16
// Be careful to use , insetead of . when you enter the address here
IPAddress ip(192,168,100,109);

//int photocellPin = 0;  // Analog input pin on Arduino we connected the SIG pin from sensor
//int photocellReading;  // Here we will place our reading

int humidityRouter1, temperatureRouter1, mq2Router1, mq7Router1;

char server[] = "192.168.100.108"; // IMPORTANT: If you are using XAMPP you will have to find out the IP address of your computer and put it here (it is explained in previous article). If you have a web page, enter its address (ie. "www.yourwebpage.com")

// Initialize the Ethernet server library
EthernetClient client;
//Ethernet

// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial XBee(2, 3); // RX, TX

extern "C"{
    #include "src/Xpollute/Xpollute.h"
}

uint8_t testArray[8];
uint8_t bufferInput;

humidityType extractedHumidity = 0;
uint8_t state = 0;
int i = 0;

void setup() {
  // put your setup code here, to run once:
  XBee.begin(57600);
  Serial.begin(57600);

  // start the Ethernet connection
  Ethernet.begin(mac, ip);
}

void loop() {

  //humidityRouter1 = 66; // Fill the sensorReading with the information from sensor
  temperatureRouter1 = 67;
  mq2Router1 = 68;
  mq7Router1 = 69;
  
  // put your main code here, to run repeatedly:
  if (XBee.available()){
    for (i=0 ; i <8 ; i++){
      bufferInput = XBee.read();
      testArray[i] = bufferInput;
      Serial.write(testArray[i]);
    }

  
  Serial.println();
  Serial.println("Message Retrieved");
  xpollute_message_t deconstructedMessage;
  reconstruct_xpollute(&deconstructedMessage, testArray);  
  extractedHumidity = extract_humidity(deconstructedMessage.payload);
  Serial.print("Message = ");
  Serial.println(extractedHumidity);
  humidityRouter1 = extractedHumidity;

  

  //Ethernet Open

  // Connect to the server (your computer or web page)  
  if (client.connect(server, 80)) {
    //humidity parsing
    client.print("GET /write_data.php"); // This
    client.print("?humidity-1="); // This
    client.print(humidityRouter1); // And this is what we did in the testing section above. We are making a GET request just like we would from our browser but now with live data from the sensor

    //temperature parsing
    client.print(";temperature-1="); 
    client.print(temperatureRouter1);

    //mq2 parsing
    client.print(";mq2-1=");
    client.print(mq2Router1);

    //mq7 parsing
    client.print(";mq7-1"); // This
    client.print(mq7Router1);
    
    client.println(" HTTP/1.1"); // Part of the GET request
    client.println("Host: 192.168.100.108"); // IMPORTANT: If you are using XAMPP you will have to find out the IP address of your computer and put it here (it is explained in previous article). If you have a web page, enter its address (ie.Host: "www.yourwebpage.com")
    client.println("Connection: close"); // Part of the GET request telling the server that we are over transmitting the message
    client.println(); // Empty line
    client.println(); // Empty line
    client.stop();    // Closing connection to server

  }

  else {
    // If Arduino can't connect to the server (your computer or web page)
    Serial.println("--> connecting ... ");
  }
 
  // Give the server some time to recieve the data and store it. I used 10 seconds here. Be advised when delaying. If u use a short delay, the server might not capture data because of Arduino transmitting new data too soon.
  delay(10000);

  //Ethernet Close
    
  }
}
