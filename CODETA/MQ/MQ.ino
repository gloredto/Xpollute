//Library yang digunakan pada proyek LTKA
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <dht.h>

dht DHT; // deklarasi variabel dht yang ada di lib dht.h

//Access point ID dan Password
const char* ssid = "my42love"; 
const char* pwd = "my42love";

//Deklarasi PIN pada Node MCU
#define trigPin1 D8 //Pin pada Trigger Ultrasonik 1
#define trigPin2 D4 //Pin pada Trigger Ultrasonik 2
#define echoPin1 D6 //Pin pada Echo Ultrasonik 1
#define echoPin2 D2 //Pin pada Echo Ultrasonik 2
#define dhtPin D3 //Pin pada DHT11

#define         MQ_PIN                       A0     //define which analog input channel you are going to use
#define         RL_VALUE                     (8)     //define the load resistance on the board, in kilo ohms
#define         RO_CLEAN_AIR_FACTOR          (9.83)  //RO_CLEAR_AIR_FACTOR=(Sensor resistance in clean air)/RO,
                                                     //which is derived from the chart in datasheet

/***********************Software Related Macros************************************/
#define         CALIBARAION_SAMPLE_TIMES     (50)    //define how many samples you are going to take in the calibration phase
#define         CALIBRATION_SAMPLE_INTERVAL  (500)   //define the time interal(in milisecond) between each samples in the
                                                     //cablibration phase
#define         READ_SAMPLE_INTERVAL         (50)    //define how many samples you are going to take in normal operation
#define         READ_SAMPLE_TIMES            (5)     //define the time interal(in milisecond) between each samples in 
                                                     //normal operation

/**********************Application Related Macros**********************************/
#define         GAS_Metana                   (0)

float           MetanaCurve[3]  =  {2.301,0.477,-0.369};   //two points are taken from the curve. 
                                                    //with these two points, a line is formed which is "approximately equivalent"
                                                    //to the original curve. 
                                                    //data format:{ x, y, slope}; point1: (lg200, 0.21), point2: (lg10000, -0.59) 
float           Ro           =  10;                 //Ro is initialized to 10 kilo ohms

int humid0, temp0;
int metana0;
int distance, distance01, distance02, distance1, distance2;
int a,x,y;
void pakan1 (int, int, int);
void pakan2 (int, int, int);//Fungsi menghitung sisa pakan
void metana ();
void dht(int);

int sensor;
float temperature, refvoltage, temp;

int ledPin = 13; //connected to pin 7 in nodemcu 1.0 esp-12e module
WiFiServer server(80);  // open port 80 for server connection

void setup() 
{
  Serial.begin(9600); //initialise the serial communication
  delay(10);
  Serial.print("Calibrating...\n");                
  Ro = MQCalibration(MQ_PIN);                       //Calibrating the sensor. Please make sure the sensor is in clean air 
                                                    //when you perform the calibration                    
  Serial.print("Calibration is done...\n"); 
  Serial.print("Ro=");
  Serial.print(Ro);
  Serial.print("kohm");
  Serial.print("\n");
  delay(10);

  pinMode(trigPin1, OUTPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  //defining the pins, i/p and o/p
  pinMode(ledPin, OUTPUT);
  pinMode(A0, INPUT);
  digitalWrite(ledPin, LOW);

  refvoltage = 2.25;   //reference voltage for temperature calculation
        
  //connecting to wifi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to wifi ");
  Serial.println(ssid);

  WiFi.begin(ssid, pwd);
  
  //attempt to connect to wifi
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print("."); //progress with dots until the wifi is connected
  }
    Serial.println("");

    //while connected print this
    Serial.println("Wifi connected");

    //starting the server
    server.begin();
    Serial.println("Server started.");

    //get the ip address and print it
    Serial.print("This is your ip address: ");
    Serial.print("http://");
    Serial.print(WiFi.localIP());
    Serial.println("/");  
}

void loop()
{
    WiFiClient client = server.available();
    if (!client)
    {
      return;
    }
    
    //wait for the data to be sent from client
    Serial.println("New client connection");
    while(!client.available())
    {
      delay(1);
    }

    //Read the first line of the request
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();
    
   int value = LOW; // set the thermometer off initially
   
   pakan1 (1,trigPin1, echoPin1);
   distance1 = distance01;
   pakan2 (2,trigPin2, echoPin2);
   distance2 = distance02;
   metana();
   dht (dhtPin);
   
    //check the index of the browser and act accordingly 
    if (request.indexOf("/System=ON") != -1) 
    {
        //Menyimpan data ke server dengan perintah pada add.php
        HTTPClient http;
        String url = "http://10.0.32.220/nodemcu/add.php?pakan1="+String(distance1)+"&pakan2="+String(distance2)+"&temp="+String(temp0)+"&humidity="+String(humid0)+"&metana="+String(metana0);
        Serial.println(url);
        http.begin(url);

        //GET method
        int httpCode = http.GET();
        if(httpCode > 0)
        {
          Serial.printf("[HTTP] GET...code: %d\n", httpCode);
          if(httpCode == HTTP_CODE_OK)
          {
              String payload = http.getString();
              Serial.println(payload);
          }
       }
       else
       {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
       }
          http.end();
          delay(3000);
   }

    if (request.indexOf("/System=OFF") != -1)
    {
    } 
     
      //Return the response
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");

     if (request.indexOf("/AlwaysOn") != -1) 
     {
        
     client.println("Refresh: 5");
     }

      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("<body style=background-color:green>");

      client.println("<div id='chartContainer' style='height: 370px; width: 100%;'></div>");
      client.println("<script src='https://canvasjs.com/assets/script/canvasjs.min.js'></script>");
      
      client.println("</body>");
      client.println("<style> h1 {text-align: center}</style>");
      client.println("<style> h3 {text-align: center}</style>");
      client.println("<style> b {text-align: center}</style>");
      client.println("<style> p {text-align: center}</style>");
      client.println("<head><style>div.relative{position:relative; left:200px; height:20px; width:350px; border:2px solid #73AD21;}</style></head>");
      client.println();

      client.println("<div class=relative>  <b> BANDUNG INSTITUTE OF TECHNOLOGY </b> </div>");
      client.println("<div class = relative> Moh. Rizki Hidayatulloh  </div>");
      client.println("<div class = relative>  Michael Sihombing </div>");
      client.println("<div class = relative> Febbry Andika Ramadhan  </div>");
      client.println("<div class = relative>  Nyayu Fitria Romadhona </div>");
     
      //client.println("<br>");
      client.println("<br><br><h1>IOT Final Project: THERMOMETER</h1><br><br>");
      //client.println("<h3>Probable LM35 analog reading: <h3>");
      //client.print(sensor); //analog reading of the sensor
      //client.print("<br>");
      
      client.print("<h3>System's current status: </h3>");
      if(request.indexOf("/AlwaysOn") != -1)
      {
        client.print("<h3>Always On<h3>");
        client.print("(System updated every 5 seconds.)");

        client.print("<table border='1' align ='center'><th colspan='2'>PAKAN</th><th>TEMPERATUR</th><th>KELEMBAPAN</th><th>GAS METANA</th>");
        
        client.print("<tr>");

            client.print("<td>");
            
            client.println("<h3>Pakan 1: <h3>");
            client.print(distance1);
            client.print("<b> cm </b>");

            client.print("</td>");

            client.print("<td>");
            
            client.println("<h3>Pakan 2: <h3>");
            client.print(distance2);
            client.print("<b> cm </b>");

            client.print("</td>");

            client.print("<td>");
            client.print(temp0);
            client.print("<b> C </b>");
            client.print("</td>");

            client.print("<td>");
            client.print(humid0);
            client.print("<b>  </b>");
            client.print("</td>");

            client.print("<td>");
            client.print(metana0);
            client.print("<b> ppm </b>");
            client.print("</td>");
            
        client.print("</tr>");

        client.print("</table>");
        
        //save the data to mysql, with http client
      HTTPClient http;
      String url = "http://10.0.32.220/nodemcu/add.php?pakan1="+String(distance1)+"&pakan2="+String(distance2)+"&temp="+String(temp0)+"&humidity="+String(humid0)+"&metana="+String(metana0);
      Serial.println(url);     
      http.begin(url);

      //using GET method to write to sql
      int httpCode = http.GET();
      if(httpCode > 0)
      {
          Serial.printf("[HTTP] GET...code: %d\n", httpCode);
            if(httpCode == HTTP_CODE_OK)
            {
              String payload = http.getString();
              Serial.println(payload);
            }
      }
         else
         {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
         }
          http.end();
       //delay(3000);
    }
        
      else if(value == LOW)
      {
          if(request.indexOf("/System=ON") != -1)
          {
            client.println("<body>");
            client.print("<h3>On Once<h3>");
            // client.println("<br>");
            client.println("<h3>Last measured temperature: <h3>"); //print the last value of temp
            client.print(temp0);
            client.print("<b> deg C.</b>");
          }else{
            client.print("<h3>Off<h3>");
           // client.println("<br>"); 
            client.println("<h3>Last measured temperature: <h3>"); //print the last value of temp
            client.print(temp0);
            client.print("<b> deg C.</b>");
           }
      }
 
      client.println("<br><br>");
      //create buttons
      client.println("<a href=\"/System=ON\"\"><button>Turn On Once </button></a>");
      client.println("<a href=\"/AlwaysOn\"\"><button>Keep It On </button></a>");
      client.println("<a href=\"/System=OFF\"\"><button>Turn Off </button></a><br />");
      
      client.println("<h3>Check the Temperature records by following the below link: <h3>");
      client.println("<p>http://10.0.32.220/nodemcu/show.php</p>");
      
      // if there are incoming bytes available from the server, read them and print them:
     if (client.available()) 
     {
       char c = client.read();
       client.print(c);
     }
  
      client.println("</html>");
      
      client.println();
      delay(1);
      Serial.println("Client disconnected!");
      Serial.println("");
}


void pakan1 (int x,int trigPin, int echoPin){
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  Serial.print("Pakan Ayam ");
  Serial.print(x);
  Serial.print(" adalah = ");
  Serial.print(distance);
  Serial.println(" cm");

  distance01 = distance;

  delay(1000);
}

void pakan2 (int x,int trigPin, int echoPin){
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  Serial.print("Pakan Ayam ");
  Serial.print(x);
  Serial.print(" adalah = ");
  Serial.print(distance);
  Serial.println(" cm");

  distance02 = distance;

  delay(1000);
}

void dht(int dhtPin){
  DHT.read11(dhtPin);
  Serial.print("Current humidity = ");
  humid0 = DHT.humidity;
  Serial.print(humid0);
  Serial.print("%  ");
  Serial.print("temperature = ");
  temp0 = DHT.temperature;
  Serial.print(temp0); 
  Serial.println("C  ");
    
  delay(1000);
 
}

void metana (){
   Serial.print("Metana:"); 
   metana0 = MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_Metana);
   Serial.print(metana0);
   Serial.println( "ppm" );
   delay(1000);

}
  
/****************** MQResistanceCalculation ****************************************
Input:   raw_adc - raw value read from adc, which represents the voltage
Output:  the calculated sensor resistance
Remarks: The sensor and the load resistor forms a voltage divider. Given the voltage
         across the load resistor and its resistance, the resistance of the sensor
         could be derived.
************************************************************************************/ 
float MQResistanceCalculation(int raw_adc)
{
  return ( ((float)RL_VALUE*(1023-raw_adc)/raw_adc));
}
/***************************** MQCalibration ****************************************
Input:   mq_pin - analog channel
Output:  Ro of the sensor
Remarks: This function assumes that the sensor is in clean air. It use  
         MQResistanceCalculation to calculates the sensor resistance in clean air 
         and then divides it with RO_CLEAN_AIR_FACTOR. RO_CLEAN_AIR_FACTOR is about 
         10, which differs slightly between different sensors.
************************************************************************************/ 
float MQCalibration(int mq_pin)
{
  int i;
  float val=0;

  for (i=0;i<CALIBARAION_SAMPLE_TIMES;i++) {            //take multiple samples
    val += MQResistanceCalculation(analogRead(mq_pin));
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  val = val/CALIBARAION_SAMPLE_TIMES;                   //calculate the average value

  val = val/RO_CLEAN_AIR_FACTOR;                        //divided by RO_CLEAN_AIR_FACTOR yields the Ro 
                                                        //according to the chart in the datasheet 

  return val; 
}

/*****************************  MQRead *********************************************
Input:   mq_pin - analog channel
Output:  Rs of the sensor
Remarks: This function use MQResistanceCalculation to caculate the sensor resistenc (Rs).
         The Rs changes as the sensor is in the different consentration of the target
         gas. The sample times and the time interval between samples could be configured
         by changing the definition of the macros.
************************************************************************************/ 
float MQRead(int mq_pin)
{
  int i;
  float rs=0;

  for (i=0;i<READ_SAMPLE_TIMES;i++) {
    rs += MQResistanceCalculation(analogRead(mq_pin));
    delay(READ_SAMPLE_INTERVAL);
  }

  rs = rs/READ_SAMPLE_TIMES;

  return rs;  
}

/*****************************  MQGetGasPercentage **********************************
Input:   rs_ro_ratio - Rs divided by Ro
         gas_id      - target gas type
Output:  ppm of the target gas
Remarks: This function passes different curves to the MQGetPercentage function which 
         calculates the ppm (parts per million) of the target gas.
************************************************************************************/ 
int MQGetGasPercentage(float rs_ro_ratio, int gas_id)
{
  if ( gas_id == GAS_Metana ) {
     return MQGetPercentage(rs_ro_ratio,MetanaCurve);
  }    

  return 0;
}

/*****************************  MQGetPercentage **********************************
Input:   rs_ro_ratio - Rs divided by Ro
         pcurve      - pointer to the curve of the target gas
Output:  ppm of the target gas
Remarks: By using the slope and a point of the line. The x(logarithmic value of ppm) 
         of the line could be derived if y(rs_ro_ratio) is provided. As it is a 
         logarithmic coordinate, power of 10 is used to convert the result to non-logarithmic 
         value.
************************************************************************************/ 
int  MQGetPercentage(float rs_ro_ratio, float *pcurve)
{
  return (pow(10,( ((log(rs_ro_ratio)-pcurve[1])/pcurve[2]) + pcurve[0])));
}

