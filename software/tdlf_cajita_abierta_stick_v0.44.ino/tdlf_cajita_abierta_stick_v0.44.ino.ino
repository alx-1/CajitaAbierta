#include "config.h"

//// Sensors ////
const int arrayLength = 10000; // 65535
byte sensorData[arrayLength] = {0}; // Array to store the values, intialize with 0s
long sensorIndex = 0; // Keep track of the values in the array
const long period = 5; //time between samples in milliseconds // change from '10' to '5' when not printing to serial
long startMillis = 0;
bool playback = false;
bool portalStart = false;

#include "blowsuck.h"
#include "params.h"
#include "analogSensors.h"
#include "accelerometer.h"
#include "WiFI_.h"
#include "button.h"
#include "display.h"
#include "portal.h"
//// For a PWM to the LEDPIN on the nodeMCU ESP32
#include <analogWrite.h> // From the polyfill analogWrite library for ESP32 //
#ifndef LED_BUILTIN
#define LED_BUILTIN 2 // For the boards that do not have a LED_BUILTIN
#endif
#include "UDP_OSC_Midi.h"
//bool readCFSensor(byte sensorAddress);

void setup() {
    //WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP    
    Serial.begin(115200);
    
    #if defined Display
    displaySetup();
    #endif
    #if defined Accelerometer
    accelerometerSetup();
    #endif
    #if defined PressureSensor
    pressureSensorSetup();
    #endif
    #if defined useButton
    buttonSetup();
    #endif
    preferencesSetup();
    preferencesGet();

    Serial.println(ssid.c_str());
    Serial.println(password.c_str());
    WiFi.begin(ssid.c_str(),password.c_str());
    
    if(testWifi()==false){
      startPortal();  
    }

     if (!MDNS.begin("CajitaAbierta")) {
      Serial.println("Error setting up MDNS responder!");
      while(1){
          delay(1000);
      }
     }
    
    browseService("touchoscbridge", "udp");
    browseService("osc", "udp"); // _osc._udp
    //browseService("_osc", "_udp"); // _osc._udp
    //browseService("tdlf", "udp"); //    
}

void loop() {
    if((WiFi.status() == WL_CONNECTED)) {
      if (portalStart){
        Serial.println("Starting portal");
        startPortal();
      }
      #if defined Accelerometer
      checkAccelerometer();
      #endif
      #if defined PressureSensor
      readCFSensor(0x6D);   //start conversion and read on pressure sensor at 0x6D address
      #endif
      #if defined useButton
      getButtonState();
      
      #endif
      #if defined useSensors
      readSensors();
      #endif
      sendOSCMidi();
      #if defined Display
      // Serial.print("buttonCounter : ");Serial.println(buttonCounter); 
      if(buttonCounter == 0){
        displayMessage(2); // Overall sensors 
      }else{
        displayMessage(3); // Single sensor
      }
      #endif
      while ((millis() - startMillis) < period);      //waits until period done
    } else {
      serverListen();
    }
}
