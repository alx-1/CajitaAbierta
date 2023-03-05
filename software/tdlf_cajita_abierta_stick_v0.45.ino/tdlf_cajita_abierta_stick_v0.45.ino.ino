#include "config.h"

//// Sensors ////
const long period = 5; //time between samples in milliseconds // change from '10' to '5' when not printing to serial
long startMillis = 0;
// bool playback = false;
bool portalStart = false;

#include "blowsuck.h"
#include "params.h"
#include "analogSensors.h"
#include "accelerometer.h"
#include "WiFI_.h"
#include "button.h"
#include "display.h"
#include "portal.h"
#include "record_play.h"
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
    if(myMode == "live"){
      displayMessage(9);
      } else if (myMode == "playback"){
      displayMessage(10);
      littleFSSetup();
      readArrayFromFile(); 
      } else if (myMode == "record"){
      displayMessage(11);
      }
    
    if(myMode == "live" || myMode == "playback"){  // myMode = live, playback, record
      //    live : start wifi, start osc, check sensors, send according to the bpm  
      //    playback : start wifi, populate array from file, start osc, send according to the bpm 
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
      } else if (myMode == "record"){
        //    record : don't start wifi, check sensors, save to array , then save to file, then reboot into play mode
        Serial.println("We're recording");
    }
      
     //    erase : display ERASING FILE , don't start wifi, just erase the file and restart in live mode.
}

void loop() {

    // myMode = live, playback, record
    
    if(myMode == "live"){  

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
  
    } else if (myMode == "playback"){

      if((WiFi.status() == WL_CONNECTED)) {
        if (portalStart){
          Serial.println("Starting portal");
          startPortal();
        }
      //readArrayFromFileToFile();

      
      #if defined Accelerometer
      playbackAccelerometer();
      #endif
      #if defined PressureSensor
      playbackCFSensor(0x6D);   //start conversion and read on pressure sensor at 0x6D address
      #endif
      #if defined useButton
      getButtonState();
      #endif
      #if defined useSensors
      playbackReadSensors();
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
       sensorIndex = sensorIndex+12;
       if(sensorIndex > arrayLength){
        sensorIndex = 0; // reset
       }
       while ((millis() - startMillis) < period);      //waits until period done
       } else {
        serverListen();
        }
    } else if (myMode == "record"){

      while(sensorIndex < arrayLength){
        //  record : don't start wifi, check sensors, populate array , then save to file, then reboot into play mode
        Serial.print("Recording, ");Serial.print("sensorIndex : ");Serial.println(sensorIndex);
        #if defined Accelerometer
        checkAccelerometer();
        #endif
        #if defined PressureSensor
        checkCFSensor(0x6D);   //start conversion and read on pressure sensor at 0x6D address
        #endif
        #if defined useButton
        //getButtonState();
        #endif
        #if defined useSensors
        checkReadSensors();
        #endif
        #if defined Display
        // Serial.print("buttonCounter : ");Serial.println(buttonCounter); 
        if(buttonCounter == 0){
          displayMessage(2); // Overall sensors 
          }else{
          displayMessage(3); // Single sensor
          }
       #endif
       while ((millis() - startMillis) < period);      //waits until period done
       
       // Recording /// Get the values in an array !  Get ax, ay, az, x, y, z, blow, suck, s1, s2, s3, s4 into that thing

       for ( int i = 0; i <12; i++ ) { 
        switch(i){
        case 0: sensorData[i+sensorIndex] = aIntX; break; 
        case 1: sensorData[i+sensorIndex] = aIntY; break;
        case 2: sensorData[i+sensorIndex] = aIntZ; break;
        case 3: sensorData[i+sensorIndex] = x; break;
        case 4: sensorData[i+sensorIndex] = y; break;
        case 5: sensorData[i+sensorIndex] = z; break;
        case 6: sensorData[i+sensorIndex] = blowValue; break;
        case 7: sensorData[i+sensorIndex] = suckValue; break;
        case 8: sensorData[i+sensorIndex] = sensor1Value; break;
        case 9: sensorData[i+sensorIndex] = sensor2Value; break;
        case 10: sensorData[i+sensorIndex] = sensor3Value; break;
        case 11: sensorData[i+sensorIndex] = sensor4Value; break;
        default: break;
      } 
    }
    sensorIndex = sensorIndex+12;   
    } // end of while
     writeToFile(); // at the end of which restart in playback mode
     preferences.putString("myMode","playback");
     preferences.putString("checkedLive","unchecked");
     preferences.putString("checkedPlay","checked");
     preferences.putString("checkedRecord","unchecked");
     preferences.putString("checkedErase","unchecked");
     ESP.restart();
     }
}
