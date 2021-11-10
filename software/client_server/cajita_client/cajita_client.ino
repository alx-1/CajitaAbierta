//
//SENSOR PECHO
//
//  ______     ______     __   __     ______     ______     ______
///\  ___\   /\  ___\   /\ "-.\ \   /\  ___\   /\  __ \   /\  == \      
//  \ \___  \  \ \  __\   \ \ \-.  \  \ \___  \  \ \ \/\ \  \ \  __<
//   \/\_____\  \ \_____\  \ \_\\"\_\  \/\_____\  \ \_____\  \ \_\ \_\    
//    \/_____/   \/_____/   \/_/ \/_/   \/_____/   \/_____/   \/_/ /_/    V6
//

//
//
// CADENA DE SENSORES:

// (((SENSOR PULSO)))---\
// (((SENSOR PANZA)))--->(((RECEPTOR))--->[[[unity]]]
// (((SENSOR PECHO)))---/
//

/*
    This sketch connects via WiFI + websockets to a ESP32S AP and sends sensor data as UDP packets
    Alexandre Castonguay acastonguay@artengine.ca For Yesica Duarte. Thank you to EWMA library creator Arsen Torbarina.
*/
/**
   Smooth

   Demonstrates analog input smoothing.

   The circuit:
   - Potentiometer attached to analog input 0 center pin of the potentiometer
     to the analog pin: one side pin (either one) to ground the other side pin to +5V

   Created in 2016 by Sofian Audry

   This example code is in the public domain.

   Inspired from the following code:
   http://www.arduino.cc/en/Tutorial/AnalogInput
*/

#include <Plaquette.h>
#include <Thresholder.h>

// The analog input.
AnalogIn in(35); // First input on the Cajita Abierta Break out board

// The serial output.
StreamOut serialOut;

AdaptiveNormalizer norm;

Thresholder peakDetector(0.7, THRESHOLD_RISING, 0.5);
//Thresholder peakDetector(0.7, THRESHOLD_FALLING, 0.5);

//// WiFi UDP connection ////
#include <WiFi.h>
#include <WiFiUdp.h>
const char* ssid     = "ESPdatos";
const char* password = "respiracion";
IPAddress ip(192, 168, 4, 1);
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
WiFiUDP Udp;
IPAddress myIP;                    // the IP address of your shield

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

int datoL2 = 0; // Indicates state of breathing "1" or "2"

unsigned long leTemps = 0;
unsigned long elViejoTiempo = 0;
unsigned long intervalleEntreResp = 0;

void begin() {

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

  digitalWrite (LED_BUILTIN, HIGH);//apago led por las dudas reverse para los ESP8266

  // Smooth over a window of 100ms (ie. one tenth of a second).
  // NOTE: Try changing the smoothing value to see how it affects the outputs.
  in.smooth(0.2);

  norm.time(10);

}


void step() {
  
  in >> norm >> peakDetector;
  //Serial.print(6 * norm);
  //Serial.println(" ");
  
  //Udp.beginPacket(ip, 8888);
  //String msg = String(localData.temp);
  
  if (peakDetector == 1) {
    leTemps = millis();
    intervalleEntreResp = millis()-elViejoTiempo;
    datoL2 == 1; // peak detected
    digitalWrite (LED_BUILTIN, LOW);
    Udp.beginPacket(ip, 8888);
    Udp.print("belly,2");
    Udp.endPacket();
    
    Serial.println("peak detected, data one sent");
    Serial.print("intervalle entre respiration : ");
    Serial.println(intervalleEntreResp);

    elViejoTiempo = leTemps;
    
  }
  else if ( (millis() - elViejoTiempo) < intervalleEntreResp/2) {  // si nous sommes à l'intérieur du tiers de l'ijntervalle de respiration
    digitalWrite (LED_BUILTIN, LOW);
    Udp.beginPacket(ip, 8888);
    Udp.print("belly,2");
    Udp.endPacket();
    Serial.println("belly, 2");
    
  }
  else {
    datoL2 == 2; // nope
    digitalWrite (LED_BUILTIN, HIGH);
    Udp.beginPacket(ip, 8888);
    Udp.print("belly,1");
    Udp.endPacket();
    Serial.println("belly, 1");
  }

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
  display.println(in);
  
  display.display();
  delay(50); 
} // fin step
