// CajitaAbierta v.0.48
// UDP OSC MIDi Sensor board
// * Mdns discovery for negociating UDP sending port
// * Configuration through captive portal 
// * OTA upload of new binary image
// * Accelerometer / air pressure / analog sensors implemented
// * Select where to send the data (TDLF, OSCServer, touchOSCBridge)
// * See License file

// HARDWARE REQUIREMENTS
// =====================
// ESP32 board (Tested on Node32s)
// The sensors you want, the accelerometer is based on a ADXL345 
// Edit the "config.h" file to enable the various sensors

// LIBRAIRIES TO INSTALL 
// ===================== 
// Polyfill analogWrite By ERROPiX v.0.1.0
// Seeed Studio's ADXL345 v 1.0.0
// Adafruit's GFX v. 1.10.12
// Adafruit's SSD1306 v. 2.4.6
// LittleFS_esp32 by lorol 1.0.6
// AsyncElegantOTA 2.2.7
// Microsmooth
// Tof's MicroOSCUDP (distributed with this archive)
// ESPAsyncWebServer (distributed with this archive) Not! the one named ESPAsyncWebSrvr

// Used Library
// Preferences (built in, you don't need to install it)

// TODO
// ====
// (done) * add a way to identify individually a cajita (ex 'CajitaAbierta42')
// (done) * improve .bin upload interface
// (done) * fix bug Sensor1 preferences saving
// (done) * actually select udp destination (tdlf, chataigne, touchoscbridge) sending based on the user's choice
// (done) * switch to asynchronous mode for the captive portal
// (done) * add graph to the sensor config page
// (done) * produce guide for how to use with hydra
// * add choice for data format or osc
// * run performances check (how many readings per second make it to the instruments)
// * have a ranging routine for mapping of the sensor data 
// * update webpage with Maria Paula Lonegro's example
