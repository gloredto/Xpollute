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
  }

void loop()
{
    
   metana();
   dht (dhtPin);
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

