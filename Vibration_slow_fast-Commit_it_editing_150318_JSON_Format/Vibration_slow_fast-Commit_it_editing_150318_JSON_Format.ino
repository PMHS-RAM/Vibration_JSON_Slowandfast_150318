//1.Check out Callback Topic ---> "Slow/STPCP-NEW_F"
//2.check reconnect function for connect(clientid,Username,passwd)


#include "I2Cdev.h"
#include "MPU6050.h"

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
//Make sure that Pubsub library is IMROY library

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

//****************************
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager


#include <PubSubClient.h>        //Imroy Library
#include <WiFiUdp.h>

//**********************UDP
IPAddress timeServerIP;                            // time.nist.gov NTP server address
const char* ntpServerName = "data1.neewee.io";    //In my case it is NEEWEE's
unsigned int localPort = 2390;
const int NTP_PACKET_SIZE = 48;                   // NTP time stamp is in the first 48 bytes of the message

byte packetBuffer[ NTP_PACKET_SIZE];              //buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;
unsigned long epoch;                            // global value for timestamp

//*************************

//***********MQTT Confihuration****************

//This is Old Server we moved to Rishi
//const char* mqttServer = "data1.neewee.io";
//const int mqttPort = 1992;

//Rishi Configuration
IPAddress mqttServer(13, 127, 135, 37);
const int mqttPort = 4538;
String topicName = "SSTP/STPCP-NEW";
//*********************************************
//const char* ssid = "Bhaskara";
//const char* password =  "complicated#$*";


WiFiClient espClient;
PubSubClient client(espClient, mqttServer, mqttPort);

MPU6050 accelgyro;

uint8_t devAddr = 0x68; // AD0 low =0x68 or AD0 high =0x69
//uint8_t devAddr=0x69; // <-- use for AD0 high
uint8_t FIFO_regAddr = MPU6050_RA_FIFO_R_W;

//*********** POINTER TO RING BYTES BUFFER *******************************/
// Create a RinBuf object designed to hold a desired number of BYTES


#include <ByteBuffer.h>                  // Circular BYTES Buffer Library
//#include <TimerOne.h>                 // Timer Library for sampling for ATMEGA only
#include <SPI.h>                       // SPI for SD Card
#include <SD.h>
ByteBuffer ringBuffer;
//uint8_t count=1;

const int chipSelect = 16;          // Standard CS PIN in ESP8266 is 16.
File root;                         //Object for File operations
File testfile;                    //Object for File operations

char buf[80];




int16_t ax, ay, az;
#define OUTPUT_READABLE_ACCELGYRO

long interval1 = 10000;
int n = 0, x;
int axminX, axmaxX, ayminX, aymaxX, azminX, azmaxX;
float axavgX, ayavgX, azavgX;
int16_t rawTemp;
float temp1,temperature;
long int axsumX, aysumX, azsumX = 0;



#define BUFFER_SIZE 100
char JSONmessageBuffer[600];

void setup() {

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif

  Serial.begin(115200);

  // Reset the device
  Serial.println(F("Reset the device..."));
  accelgyro.reset(); accelgyro.reset(); // accelgyro.reset();  accelgyro.reset();  accelgyro.reset();delay(1000);

  // initialize device
  Serial.println(F("Initializing I2C devices..."));
  accelgyro.initialize(); // Sets 3 parameters viz, Acceleration range (default 2G),Gyro Range,Clock source,Sleep functionality
  //accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_2); // Set Acceleration (G) to desired range
  //Serial.println(accelgyro.getFullScaleAccelRange());   // Print and check the G value

  // verify connection
  Serial.println(F("Testing device connections..."));
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful\n" : "MPU6050 connection failed\n");


  setup_wifi();  //goto setup_wifi tab


  //  client.setServer(mqttServer, mqttPort);
  //  client.setCallback(callback);

  Serial.println("Starting UDP");
  udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(udp.localPort());
  // Configure SD Card Initialising
  Serial.println("Initializing SD Card");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("Card Initialized.");

}

void loop() {
  get_timestamp(); //Goto get_timestamp tab
  slow_data();   //Goto slow_data tab

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  send_Smsg();   //Goto send_msg tab

}












