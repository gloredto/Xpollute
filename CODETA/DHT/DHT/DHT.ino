#include "dht.h"

dht DHT; // Variabel DHT yang ada di dht.h

#define dht11Pin A0 //Pin5 untuk DHT11

//Deklarasi Variabel
double humidity1, temperature1;

//Deklarasi Fungsi
double humidity(int);
double temperature(int);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  humidity1 = humidity(dht11Pin);
  temperature1 = temperature(dht11Pin);
  Serial.println(humidity1);
  Serial.println(temperature1);
  delay(10000);
   
}

double humidity(int dhtPin){
  double humidity;
  DHT.read11(dhtPin);
  humidity = DHT.humidity;
  return humidity;
}

double temperature(int dhtPin){
  double temperature;
  DHT.read11(dhtPin);
  temperature = DHT.temperature;
  return temperature;
}
