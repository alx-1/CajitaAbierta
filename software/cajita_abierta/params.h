//#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
//WiFiManager wm;
//#include <EEPROM.h>

///////Preferences /////////
#include <Preferences.h>
Preferences preferences;
#include <Arduino_JSON.h>


IPAddress monIP(192, 168, 8, 1);

  String apNameString = "Cajita";
  char apName[21] = "CajitaAbierta";

  
  // WiFI
  String ssid = "yep";
  String password;
  String OSCServer;
  String checkedTOSCB; // TouchOSCBridge
  String checkedTDLF;
  String checkedOSC;

  // Mode
  String myMode;
  String checkedLive;
  String checkedPlay;
  String checkedRecord;
  String checkedFormatFS;
  String monDelai;
  String monArrayLength;
  int countDownFrom;

  // For recording
  int blowValue = 0;
  int suckValue = 0;
  byte sensorData[75500] = {0}; // Array to store the values, intialize with 0s, initialize at tested max
  // byte sensorData[42] = {0}; 
  long sensorIndex = 0; // Keep track of the values in the array
  String calibratingSensors = "none"; // A true value and a long press will call the sensor calibration
  
  // Json Variable to Hold Sensor Readings
  JSONVar myData;

#if defined Accelerometer
  String accelX;
  String accelXChan;
  String accelXCC;
  String accelY;
  String accelYChan;
  String accelYCC;
  String accelZ;
  String accelZChan;
  String accelZCC;

  String pan_;
  String tilt_;
  String roll_;
  String panChan;
  String panCC;
  String tiltChan;
  String tiltCC;
  String rollChan;
  String rollCC;
  
  // bool doubleTap;
#endif
    
#if defined PressureSensor
  String expire;
  String blowChan;
  String blowCC;
  String inspire;
  String suckChan;
  String suckCC;
#endif
    
#if defined useAnalogSensors
  String sensor1;
  String s1EMAFilter;
  String sensor1Min;
  String sensor1Max;
  String sensor1Midi;
  String sensor1Chan;
  String sensor1CC;
  String sensor1Cal;
  
  String sensor2;
  String s2EMAFilter;
  String sensor2Min;
  String sensor2Max;
  String sensor2Midi;
  String sensor2Chan;
  String sensor2CC;
  String sensor3;
  String sensor3Chan;
  String sensor3CC;
  String sensor4;
  String sensor4Chan;
  String sensor4CC;
#endif

String mesKeys[44] = {
  "dummy","dummy","dummy","dummy", // so we have a main screen with all the values showing when buttonCounter is at '0'
  "accelX", "accelXChan","accelXCC","aIntX",
  "accelY", "accelYChan","accelYCC","aIntY",
  "accelZ", "accelZChan","accelZCC","aIntZ",
  "pan_", "panChan","panCC","x",
  "tilt_", "tiltChan","tiltCC","y",
  "roll_", "rollChan","rollCC","z",
  "expire","blowChan","blowCC","blowValue",
  "inspire","suckChan","suckCC","suckValue",
  "sensor1","sensor1Chan","sensor1CC","sensor1Value",
  "sensor2","sensor2Chan","sensor2CC","sensor2Value",
};

///////End Preferences//////

/// Save params
//#include "FS.h"
#include "LITTLEFS.h" 
//#define FORMAT_LITTLEFS_IF_FAILED true
File fileToAppend;

//// Recording ////
//const int arrayLength = 10000; // 65535

void preferencesGet(){

  // WiFI
  Serial.println("*** Reading Preferences ***");
  ssid = preferences.getString("ssid", "not set yet");
  Serial.print("SSID: ");Serial.println(ssid);
  password = preferences.getString("password", "not set yet");
  Serial.print("PASS: ");Serial.println(password);
  
  checkedTDLF = preferences.getString("checkedTDLF", "not set yet");
  Serial.print("checkedTDLF: ");Serial.println(checkedTDLF);
  checkedTOSCB = preferences.getString("checkedTOSCB", "not set yet");
  Serial.print("checkedTOSCB: ");Serial.println(checkedTOSCB);
  checkedOSC = preferences.getString("checkedOSC", "not set yet");
  Serial.print("checkedOSC: ");Serial.println(checkedOSC);

  // Mode
  checkedLive = preferences.getString("checkedLive", "");
  Serial.print("checkedLive: ");Serial.println(checkedLive); 
  if (checkedLive == "checked"){
    myMode = "live";
  }
  checkedPlay = preferences.getString("checkedPlay", "");
  Serial.print("checkedPlay: ");Serial.println(checkedPlay); 
  if (checkedPlay == "checked"){
    myMode = "playback";
  } 
  checkedRecord = preferences.getString("checkedRecord", "");
  Serial.print("checkedRecord: ");Serial.println(checkedRecord); 
  if (checkedRecord == "checked"){
    myMode = "record";
  }
  checkedFormatFS = preferences.getString("checkedFormatFS", "");
  Serial.print("checkedFormatFS: ");Serial.println(checkedFormatFS); 
    if (checkedFormatFS == "checked"){
    myMode = "formatFS";
  }
  
  // myMode = preferences.getString("myMode", "");
  Serial.print("myMode: ");Serial.println(myMode);
  
  monDelai = preferences.getString("monDelai", "");
  Serial.print("monDelai: ");Serial.println(monDelai);
  
  monArrayLength = preferences.getString("monArrayLength", "");
  if ((monArrayLength.toInt()) < 1){
    monArrayLength = 5000; //
  }
  Serial.print("monArrayLength: ");Serial.println(monArrayLength);
//
//myArrayLength = arrayLength.toInt();
//sensorData[myArrayLength] = {0}; // Array to store the values, intialize with 0s
  //byte sensorData[monArrayLength.toInt()] = {0}; // Array to store the values, intialize with 0s  
//
//  long sensorIndex = 0; // Keep track of the values in the array

  // Sensors
  #if defined Accelerometer
  accelX = preferences.getString("accelX","");
  //Serial.print("accelX: ");Serial.println(accelX);
  if (accelX == "checked"){
    // add "accelX" to an array of keys
  }
  accelXChan = preferences.getString("accelXChan","0");
  //Serial.print("accelXChan : ");Serial.println(accelXChan);
  accelXCC = preferences.getString("accelXCC","0");
  //Serial.print("accelXCC : ");Serial.println(accelXCC);

  accelY = preferences.getString("accelY","");
  //Serial.print("accelY: ");Serial.println(accelY);
  accelYChan = preferences.getString("accelYChan","");
  //Serial.print("accelYChan : ");Serial.println(accelYChan);
  accelYCC = preferences.getString("accelYCC","");
  //Serial.print("accelYCC : ");Serial.println(accelYCC);

  accelZ = preferences.getString("accelZ","");
  //Serial.print("accelZ: ");Serial.println(accelZ);
  accelZChan = preferences.getString("accelZChan","");
  //Serial.print("accelZChan : ");Serial.println(accelZChan);
  accelZCC = preferences.getString("accelZCC","");
  //Serial.print("accelZCC : ");Serial.println(accelZCC);

  pan_ = preferences.getString("pan_","");
  //Serial.print("pan_ : ");Serial.println(pan_);
  panChan = preferences.getString("panChan","");
  //Serial.print("panChan : ");Serial.println(panChan);
  panCC = preferences.getString("panCC","");
  //Serial.print("panCC : ");Serial.println(panCC);

  tilt_ = preferences.getString("tilt_","");
  //Serial.print("tilt_: ");Serial.println(tilt_);
  tiltChan = preferences.getString("tiltChan","");
  //Serial.print("tiltChan : ");Serial.println(tiltChan);
  tiltCC = preferences.getString("tiltCC","");
  //Serial.print("tiltCC : ");Serial.println(tiltCC);

  roll_ = preferences.getString("roll_","");
  //Serial.print("roll_: ");Serial.println(roll_);
  rollChan = preferences.getString("rollChan","");
  //Serial.print("rollChan : ");Serial.println(rollChan);
  rollCC = preferences.getString("rollCC","");
  //Serial.print("rollCC : ");Serial.println(rollCC);
  #endif

#if defined PressureSensor
  expire = preferences.getString("expire","");
  //Serial.print("expire: ");Serial.println(expire);
  blowChan = preferences.getString("blowChan","");
  //Serial.print("blowChan : ");Serial.println(blowChan);
  blowCC = preferences.getString("blowCC","");
  //Serial.print("blowCC : ");Serial.println(blowCC);

  inspire = preferences.getString("inspire","");
  //Serial.print("inspire: ");Serial.println(inspire);
  suckChan = preferences.getString("suckChan","");
  //Serial.print("suckChan : ");Serial.println(suckChan);
  suckCC = preferences.getString("suckCC","");
  //Serial.print("suckCC : ");Serial.println(suckCC);
#endif
  sensor1 = preferences.getString("sensor1","");
  Serial.print("sensor1: ");Serial.println(sensor1);
  s1EMAFilter = preferences.getString("s1EMAFilter","not set");
  Serial.print("s1EMAFilter: ");Serial.println(s1EMAFilter);
  
  //sensor1Min = preferences.getString("sensor1Min","4095");
  //Serial.print("Get sensor1Min: ");Serial.println(sensor1Min);
  //sensor1Max = preferences.getString("sensor1Max","0");
  //Serial.print("Get sensor1Max: ");Serial.println(sensor1Max);
  
  sensor1Midi = preferences.getString("sensor1Midi","err");
  Serial.print("sensor1Midi: ");Serial.println(sensor1Midi);
  sensor1Chan = preferences.getString("sensor1Chan","not set");
  //Serial.print("sensor1Chan: ");Serial.println(sensor1Chan);
  sensor1CC= preferences.getString("sensor1CC","not set");
  //Serial.print("sensor1CC: ");Serial.println(sensor1CC);
 
  sensor2 = preferences.getString("sensor2","");
  Serial.print("sensor2: ");Serial.println(sensor2);
  sensor2Midi = preferences.getString("sensor2Midi","err");
  Serial.print("sensor2Midi: ");Serial.println(sensor2Midi);
  s2EMAFilter = preferences.getString("s2EMAFilter","not set");
  Serial.print("s2EMAFilter: ");Serial.println(s2EMAFilter);
  //sensor2Min = preferences.getString("sensor2Min","4095");
  //Serial.print("sensor2Min: ");Serial.println(sensor2Min);
  //sensor2Max = preferences.getString("sensor2Max","0");
  //Serial.print("sensor2Max: ");Serial.println(sensor2Max);
  sensor2Chan= preferences.getString("sensor2Chan","");
  //Serial.print("sensor2Chan: ");Serial.println(sensor2Chan);
  sensor2CC= preferences.getString("sensor2CC","");
  //Serial.print("sensor2CC: ");Serial.println(sensor2CC);


  sensor3 = preferences.getString("sensor3","");
  //Serial.print("sensor3: ");Serial.println(sensor3);
  sensor3Chan= preferences.getString("Sensor3Chan","");
  //Serial.print("sensor3Chan: ");Serial.println(sensor3Chan);
  sensor3CC= preferences.getString("Sensor3CC","");
  //Serial.print("sensor3CC: ");Serial.println(sensor3CC);

  sensor4 = preferences.getString("sensor4","");
  //Serial.print("sensor4: ");Serial.println(sensor4);
  sensor4Chan= preferences.getString("sensor4Chan","");
  //Serial.print("sensor4Chan: ");Serial.println(sensor4Chan);
  sensor4CC= preferences.getString("sensor4CC","");
  //Serial.print("sensor4CC: ");Serial.println(sensor4CC);  

  }

void preferencesSetup(){
    preferences.begin("Cajita", false);
    //preferences.clear(); // Remove all preferences under the opened namespace
}
