// CajitaAbierta v.0.46
// UDP OSC MIDi Sensor board
// * mdns discovery for negociating UDP sending port
// * configuration through captive portal 
// * OTA upload of new binary image
// * Accelerometer / air pressure / analog sensors implemented
// * See License file

// HARDWARE REQUIREMENTS
// ==================
// ESP32 board (Tested on Node32s)
// The sensors you want, the accelerometer is based on a ADXL345 

// LIBRAIRIES TO INSTALL : 
// Polyfill analogWrite By ERROPiX v.0.1.0
// Seeed Studio's ADXL345 v 1.0.0
// Adafruit's GFX v. 1.10.12
// Adafruit's SSD1306 v. 2.4.6
// Tof's MicroOSCUDP (distributed with this archive)
// LittleFS_esp32 by lorol 1.0.6
// ElegantOTA 2.2.9

// Used Library
// Preferences (built in, you don't need to insall it)
