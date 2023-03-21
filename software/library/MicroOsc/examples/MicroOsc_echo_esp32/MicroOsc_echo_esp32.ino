// HARDWARE REQUIREMENTS
// ==================
// Example for ESP32

// REQUIRED LIBRARIES
// ==================
// WiFiConnect (lite) library and required WifiClient and HTTPClient
// https://github.com/mrfaptastic/WiFiConnectLite
//
// Chrono
// https://github.com/SofaPirate/Chrono

// REQUIRED CONFIGURATION
// ======================
// Change sendPort to target port
// Change sendIp to ip of target device
// Set Serial baud for monitoring to 115200

// Load Wi-Fi library
#include <WiFi.h>


#include "WiFiConnect.h"
WiFiConnect wifiConnect;

// Access to mDNS related functionalities
#include <ESPmDNS.h>


#include <WiFiUdp.h>
WiFiUDP udp;

unsigned int receivePort = 8888;

IPAddress broadcastIp(255, 255, 255, 255);
IPAddress sendIp(192, 168, 1, 225);
unsigned int sendPort = 7777;


#include <MicroOscUdp.h>
// The number 1024 between the < > below  is the maximum number of bytes reserved for incomming messages.
// Outgoing messages are written directly to the output and do not need more reserved bytes.
MicroOscUdp<1024> oscUdp(&udp, sendIp, sendPort);


#include <Chrono.h>
Chrono printIPChrono;


/* We could also use button etc. to trigger the portal on demand within main loop */
void startWiFi() {

  //wifiConnect.resetSettings(); //helper to remove the stored wifi connection, comment out after first upload and re upload

  // Wifi Dies? Start Portal Again
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("DEBUG Trying to autoconnect...");
    // try to connect to wifi
    if (wifiConnect.autoConnect()) {
      Serial.println("DEBUG Autoconnected successfully!");
    } else {
      Serial.println("DEBUG Could not autoconnect. Starting configuration portal");
      /*
        AP_NONE = Continue executing code
        AP_LOOP = Trap in a continuous loop - Device is useless
        AP_RESET = Restart the chip
        AP_WAIT  = Trap in a continuous loop with captive portal until we have a working WiFi connection
      */
      wifiConnect.startConfigurationPortal(AP_WAIT);//if not connected show the configuration portal
    }
  } else {
    Serial.println("DEBUG WiFi already connected!");
  }

}

void setup() {

  // INITIATE SERIAL COMMUNICATION
  Serial.begin(115200);
  delay(1000);
  Serial.println("DEBUG Starting WiFi");
  startWiFi();

  if (!MDNS.begin("esp32")) {
    Serial.println("DEBUG Error starting mDNS esp32");
  }

  udp.begin(receivePort);

  Serial.print("DEBUG ESP32 IP is :");
  Serial.println(WiFi.localIP());

}

// FUNCTION THAT IS CALLED FOR EVERY RECEIVED MESSAGE.

void receivedOscMessage( MicroOscMessage& message) {

  // WHEN A MESSAGE IS MATCHED IT ECHOS IT THROUGH SERIAL(ASCII) AND UDP

  if ( message.fullMatch("/test/i", "i") ) {
    int32_t firstArgument = message.getNextInt32();

//    oscUdp.sendMessage( "/test/i",  "i",  firstArgument);
    Serial.print("DEBUG /test/i ");
    Serial.println(firstArgument);

  } else if ( message.fullMatch("/test/f",  "f")) {
    float firstArgument = message.getNextFloat();
    oscUdp.sendMessage( "/test/f",  "f",  firstArgument);
    Serial.print("DEBUG /test/f ");
    Serial.println(firstArgument);

  } else if ( message.fullMatch("/test/b",  "b")) {
    const uint8_t* blob;
    size_t length;
    message.getNextBlob(&blob, &length);
    if ( blob != NULL && length != 0) {
      oscUdp.sendMessage( "/test/b", "b", length, blob);
      Serial.print("DEBUG /test/b ");
      for ( int i = 0; i < length; i++ ) {
        Serial.print(blob[i]);
      }
      Serial.println();
    }

  } else if ( message.fullMatch("/test/s",  "s")) {
    const char * s = message.getNextString();
    oscUdp.sendMessage( "/test/s",  "s",  s);
    Serial.print("DEBUG /test/s ");
    Serial.println(s);

  } else if ( message.fullMatch("/test/m", "m")) {
    const uint8_t* midi;
    message.getNextMidi(&midi);
    if ( midi != NULL ) {
      oscUdp.sendMessage( "/test/m",  "m", midi);
      Serial.print("DEBUG /test/m ");
      for ( int i = 0; i < 4; i++ ) {
        Serial.print(midi[i]);
      }
      Serial.println();
    }

  }

}



void loop() {

  if ( printIPChrono.hasPassed(5000) ) {
    printIPChrono.restart();

    Serial.print("DEBUG ESP32 IP is :");
    Serial.println(WiFi.localIP());
  }

  oscUdp.receiveMessages( receivedOscMessage );
  /*
    oscUdp.sendMessage("/test/i",  "i",   (uint32_t) millis());
    delay(1000);

    oscUdp.sendMessage("/test/f",  "f",   ((float)millis()) *0.001);
    delay(1000);

    uint8_t blob[3];
    blob[0] = millis() % 256;
    blob[1] = (millis()+1) % 256;
    blob[2] = (millis()+2) % 256;
    oscUdp.sendMessage("/test/b",  "b",   3 , blob);
    delay(1000);

    const char * hello = "hello";
    oscUdp.sendMessage("/test/s",  "s",  hello);
    delay(1000);

    uint8_t midi[4];
    midi[0] = millis() % 128;
    midi[1] = (millis()+1) % 128;
    midi[2] = (millis()+2) % 128;
    midi[3] = (millis()+3) % 128;
    oscUdp.sendMessage("/test/m",  "m",  midi);
    delay(1000);


    oscUdp.sendMessage("/test/t",  "t",  (uint64_t)(millis()));
    delay(1000);
  */

}
