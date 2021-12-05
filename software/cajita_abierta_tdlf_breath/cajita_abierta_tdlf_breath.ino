/*
 *
 *  This sketch sends sensor data to a UDP socket on the tdlf server.
 *
 */

#include <WiFi.h>
#include <WiFiUdp.h>

// WiFi network name and password:
const char * networkName = "link";
const char * networkPswd = "nidieunimaitre";

//IP address to send UDP data to:
// either use the ip address of the server or 
// a network broadcast address
const char * udpAddress = "192.168.0.255";
const int udpPort = 3333;

//Are we currently connected?
boolean connected = false;

int sensorValue = 42;
int sensorValue1 = 43;
int sensorValue2 = 44;
int sensorValue3 = 45;
String myDataType = "souffle ";
String msg = "the medium is...";

//The udp library class
WiFiUDP udp;

// variables for lighting onboard LED on heartbeat without delays
int LED = 2;       // onboard LED

////////////// TFT SCREEN //////////
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
/////////////////////////////

void setup() {
  Serial.begin(9600);  // works best in testing with 9600 or lower
 
  //Connect to the WiFi network
  connectToWiFi(networkName, networkPswd);

  //optional LED for displaying heartbeat
  pinMode(LED, OUTPUT);

  ///////////// TFT DISPLAY /////////////
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(1000); // Pause for 1 second
  // Clear the buffer
  display.clearDisplay();
  ////////////////////////////////
}

void loop() {
  // Serial.println("testing");

  sensorValue = analogRead(23);
  sensorValue1 = analogRead(34);
  sensorValue2 = analogRead(33);
  sensorValue3 = analogRead(32);
  Serial.println(sensorValue1);
  Serial.println(sensorValue2);
  Serial.println(sensorValue3);
  

    msg = myDataType+String(sensorValue);
    Serial.println(msg);
  
    //only send data when connected
    if(connected){
      //Send a packet
      udp.beginPacket(udpAddress,udpPort);
      udp.print(msg); // "breath 42"
      udp.endPacket();
    }
 
    // Display values on the screen
    display.clearDisplay();
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(WHITE);        // Draw white text
    display.setCursor(0, 0);
    //display.println(myIP);// Start at top-left corner
    //display.println(F("Client connected ?"));
    display.setCursor(5, 16);
    display.setTextSize(2);             // Draw 2X-scale text
    display.setTextColor(WHITE);
    // display.invertDisplay(true);
    display.println(F("Breath"));
    display.setCursor(15, 35);
    display.println(sensorValue);////////////////////////////
    display.display();

    delay(50);
    
  } //  Fin del loop

void connectToWiFi(const char * ssid, const char * pwd){
  Serial.println("Connecting to WiFi network: " + String(ssid));

  // delete old config
  WiFi.disconnect(true);
  //register event handler
  WiFi.onEvent(WiFiEvent);
  
  //Initiate connection
  WiFi.begin(ssid, pwd);

  Serial.println("Waiting for WIFI connection...");
}

//wifi event handler
void WiFiEvent(WiFiEvent_t event){
    switch(event) {
      case ARDUINO_EVENT_WIFI_STA_GOT_IP:
          //When connected set 
          Serial.print("WiFi connected! IP address: ");
          Serial.println(WiFi.localIP());  
          //initializes the UDP state
          //This initializes the transfer buffer
          udp.begin(WiFi.localIP(),udpPort);
          connected = true;
          break;
      case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
          Serial.println("WiFi lost connection");
          connected = false;
          break;
      default: break;
    }
}
