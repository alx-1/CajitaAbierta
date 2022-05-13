int maDonne;

//#include <OSCMessage.h>


//// WiFi UDP connection ////
#include <WiFi.h>
#include <WiFiUdp.h>
const char* ssid     = "link";
const char* password = "nidieunimaitre";
IPAddress ip(192, 168, 0, 100);
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
WiFiUDP Udp;
IPAddress myIP;                    // the IP address of your shield


/////////// OSC /////////
#include <MicroOscUdp.h>
#include "microsmooth.h"

IPAddress sendIp(192, 168, 0, 100); // <- default not really use, we are using Bonjour (mDNS) to find IP and PORT of touchoscbridge
unsigned int sendPort = 3333; // <- touchosc port

MicroOscUdp<1024> oscUdp(&Udp, sendIp, sendPort);

////////////////////////


//// Fin WiFi UDP connection ////

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

  Serial.begin(9600);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  myIP = WiFi.localIP();

  pinMode (LED_BUILTIN, OUTPUT); // LED del ESP8266
  pinMode (35, INPUT); // 

  for ( int i = 0 ; i < 5 ; i++ ) { //el led parpadea 5 veces para saludar!
    digitalWrite(LED_BUILTIN, 1 ) ;
    delay ( 100 ) ;
    digitalWrite (LED_BUILTIN, 0 ) ;
    delay ( 100 ) ;

      ///////////// TFT DISPLAY /////////////  

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(1000); // Pause for 1 second

  // Clear the buffer
  display.clearDisplay();
  ////////////////////////////////
  }

  digitalWrite (LED_BUILTIN, HIGH); //apago led por las dudas reverse para los ESP8266
}

void loop(){

  maDonne = analogRead(35);
  Serial.println(maDonne);
  
  // display /////
 // Display values on the screen 
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,0); 
  display.println(myIP);// Start at top-left corner
  //display.println(F("Client connected ?"));
  display.setCursor(5,16);             
  display.setTextSize(2);             // Draw 2X-scale text
  display.setTextColor(WHITE);
  // display.invertDisplay(true);
  
  display.println(F("Sensor")); 
  display.setCursor(15,35); 
  display.println(maDonne);
  
  display.display();
  
  ////////////////



  uint8_t midi[4];
  midi[0] = 0;
  midi[1] = 64; // changer à "midi[1] = maDonne;"
  midi[2] = 11;  // expression
  midi[3] = 176;

  oscUdp.sendMessage("/midi",  "m",  midi); // send to Udp server

  ////////////////
  
  delay(2000);
  
}
