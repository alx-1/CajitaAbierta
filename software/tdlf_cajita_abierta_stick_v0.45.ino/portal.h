#include <WebServer.h>
#include <ESPmDNS.h>
#include <DNSServer.h>
#include "webpages.h"
const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 1, 1);
String routersList = "empty list";
String IndexHTML = contentHeadStyle+menuHome+routersList+contentHome;
String AccelHTML = contentHeadStyle+contentAccel;
String breathHTML = contentHeadStyle+contentBreath;
String sensorsHTML = contentHeadStyle+contentSensors;
String modeHTML = contentHeadStyle+contentMode;
String firmwareHTML = contentHeadStyle+contentFirmware;

DNSServer dnsServer;

WebServer server(80);


void portalScanNetworks(){
  int n = WiFi.scanNetworks();
  
    Serial.println("scan done");
  
  if (n == 0)
    
      Serial.println("no networks found");
    
    else
    {
      
        Serial.print(n);
        Serial.println(" networks found");
      
      for (int i = 0; i < 5; ++i) 
      // for (int i = 0; i < n; ++i) // changing this so only the first 5 APs get shown so we have space for other stuff.
      {
        // Print SSID and RSSI for each network found
          Serial.print(i + 1);
          Serial.print(": ");
          Serial.print(WiFi.SSID(i));
          Serial.print(" (");
          Serial.print(WiFi.RSSI(i));
          Serial.print(")");
        //Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
        delay(10);
      }
    }

  routersList = "<ol>";
  for (int i = 0; i < 5; ++i)
  // for (int i = 0; i < n; ++i)  // changing this so we only have 5 results
  {
    // Print SSID and RSSI for each network found
    routersList += "<li>";
    routersList += WiFi.SSID(i);
    routersList += " (";
    routersList += WiFi.RSSI(i);
    routersList += ")";
    //st += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*";
    routersList += "</li>";
  }
  routersList += "</ol>";

}


void startPortal(){
  displayMessage(12);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("CajitaAbierta");

  portalScanNetworks();
  preferencesGet();
  monContentHome(); // Try to update with the latest values
  monContentAccel();
  #if defined PressureSensor
  monContentBreath();
  #endif
  monContentSensors();
  monContentMode();
  // if DNSServer is started with "*" for domain name, it will reply with
  // provided IP to all DNS request
  dnsServer.start(DNS_PORT, "*", apIP);
  // replay to all requests with same HTML
  server.onNotFound([]() {
  server.send(200, "text/html", contentHeadStyle+menuHome+routersList+contentHome);
  });
  server.on("/accel.html", []() {
  server.send(200, "text/html", contentHeadStyle+contentAccel);    
  });
  server.on("/blowsuck.html", []() {
  server.send(200, "text/html", contentHeadStyle+contentBreath);    
  });
  server.on("/sensors.html", []() {
  server.send(200, "text/html", contentHeadStyle+contentSensors);    
  });
  server.on("/mode.html", []() {
  server.send(200, "text/html", contentHeadStyle+contentMode);    
  });
  server.on("/firmware.html", []() {
  server.send(200, "text/html", firmwareHTML);    
  });

  
  server.on("/accelcfg", []() {
    
    // AccelX // check // channel // CC message
    accelX = server.arg("accelX");
    if ( accelX == "on" ){ accelX = "checked"; } else { accelX = "unchecked"; }
    
    Serial.print("accelX: "); Serial.println(accelX);
    if(accelX != preferences.getString("accelX")){
    preferences.putString("accelX",accelX);
    }
    
    accelXChan = server.arg("accelXChan");
    Serial.print("accelXChan: "); Serial.println(accelXChan);
    if(accelXChan != ""){
    preferences.putString("accelXChan",accelXChan);
    }
    
    accelXCC = server.arg("accelXCC");
    Serial.print("accelXCC: "); Serial.println(accelXCC);
    if(accelXCC != ""){
    preferences.putString("accelXCC",accelXCC);
    }
    

    // AccelY // check // channel // CC message
    accelY = server.arg("accelY");
    if ( accelY == "on" ){ accelY = "checked"; } else { accelY = "unchecked"; }
    Serial.print("accelY: "); Serial.println(accelY);
    if(accelY != preferences.getString("accelY")){
    preferences.putString("accelY",accelY);
    }

    accelYChan = server.arg("accelYChan");
    Serial.print("accelYChan: "); Serial.println(accelYChan);
    if(accelYChan != ""){
    preferences.putString("accelYChan",accelYChan);
    }
    
    accelYCC = server.arg("accelYCC");
    Serial.print("accelYCC: "); Serial.println(accelYCC);
    if(accelYCC != ""){
    preferences.putString("accelYCC",accelYCC);
    }

    // AccelZ // check // channel // CC message
    accelZ = server.arg("accelZ");
    if ( accelZ == "on" ){ accelZ = "checked"; } else { accelZ = "unchecked"; }
    Serial.print("accelZ: "); Serial.println(accelZ);
    if(accelZ != preferences.getString("accelZ")){
    preferences.putString("accelZ",accelZ);
    }
    
    accelZChan = server.arg("accelZChan");
    Serial.print("accelZChan: "); Serial.println(accelZChan);
    if(accelZChan != ""){
    preferences.putString("accelZChan",accelZChan);
    }
    
    accelZCC = server.arg("accelZCC");
    Serial.print("accelZCC: "); Serial.println(accelZCC);
    if(accelZCC != ""){
    preferences.putString("accelZCC",accelZCC);
    }

    // Pan // check // channel // CC message
    pan_ = server.arg("pan_");
    if ( pan_ == "on" ){ pan_ = "checked"; } else { pan_ = "unchecked"; }
    
    Serial.print("pan_: "); Serial.println(pan_);
    if(pan_ != preferences.getString("pan_")){
    preferences.putString("pan_",pan_);
    }

    panChan = server.arg("panChan");
    Serial.print("panChan: "); Serial.println(panChan);
    if(panChan != ""){
    preferences.putString("panChan",panChan);
    }
    
    panCC = server.arg("panCC");
    Serial.print("panCC: "); Serial.println(panCC);
    if(panCC != ""){
    preferences.putString("panCC",panCC);
    }

    // Tilt // check // channel // CC message
    tilt_ = server.arg("tilt_");
    if ( tilt_ == "on" ){ tilt_ = "checked"; } else { tilt_ = "unchecked"; }
    
    Serial.print("tilt_: "); Serial.println(tilt_);
    if(tilt_ != preferences.getString("tilt_")){
    preferences.putString("tilt_",tilt_);
    }

    tiltChan = server.arg("tiltChan");
    Serial.print("tiltChan: "); Serial.println(tiltChan);
    if(tiltChan != ""){
    preferences.putString("tiltChan",tiltChan);
    }
    
    tiltCC = server.arg("tiltCC");
    Serial.print("tiltCC: "); Serial.println(tiltCC);
    if(tiltCC != ""){
    preferences.putString("tiltCC",tiltCC);
    }
    
    // Roll // check // channel // CC message
    roll_ = server.arg("roll_");
    if ( roll_ == "on" ){ roll_ = "checked"; } else { roll_ = "unchecked"; }
    
    Serial.print("roll_: "); Serial.println(roll_);
    if(roll_ != preferences.getString("roll_")){
    preferences.putString("roll_",roll_);
    }

    rollChan = server.arg("rollChan");
    Serial.print("rollChan: "); Serial.println(rollChan);
    if(rollChan != ""){
    preferences.putString("rollChan",rollChan);
    }
    
    rollCC = server.arg("rollCC");
    Serial.print("rollCC: "); Serial.println(rollCC);
    if(rollCC != ""){
    preferences.putString("rollCC",rollCC);
    }

    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/html", contentHeadStyle+contentReboot);

    // ok get this to do stg useful
   
  });

#if defined PressureSensor
server.on("/blowsuckcfg", []() {
      expire = server.arg("expire");
      if ( expire == "on" ){ expire = "checked"; } else { expire = "unchecked"; }
      if(expire!= preferences.getString("expire")){
      preferences.putString("expire",expire);
      }
      
      inspire = server.arg("inspire");
      if ( inspire == "on" ){ inspire = "checked"; } else { inspire = "unchecked"; }
      if(inspire!= preferences.getString("inspire")){
      preferences.putString("inspire",inspire);
      }

      blowChan = server.arg("blowChan");
      Serial.print("blowChan: "); Serial.println(blowChan);
      if(blowChan != ""){
      preferences.putString("blowChan",blowChan);
      }

      suckChan = server.arg("suckChan");
      Serial.print("suckChan: "); Serial.println(suckChan);
      if(suckChan != ""){
      preferences.putString("suckChan",suckChan);
      }

      blowCC = server.arg("blowCC");
      Serial.print("blowCC: "); Serial.println(blowCC);
      if(blowCC != ""){
      preferences.putString("blowCC",blowCC);
      }
      
      suckCC = server.arg("suckCC");
      Serial.print("suckCC: "); Serial.println(suckCC);
      if(suckCC != ""){
      preferences.putString("suckCC",suckCC);
      }
      
    
      server.sendHeader("Access-Control-Allow-Origin", "*");
      server.send(200, "text/html", contentHeadStyle+contentReboot);
    }); // Fin blowsuckcfg
#endif

    server.on("/sensorscfg", []() {
      
      sensor1 = server.arg("sensor1");
      if ( sensor1 == "on" ){ sensor1 = "checked"; } else { sensor1 = "unchecked"; }
      if(sensor1!= preferences.getString("sensor1")){
      preferences.putString("sensor1",sensor1);
      }
      
      sensor2 = server.arg("sensor2");
      if ( sensor2 == "on" ){ sensor2 = "checked"; } else { sensor2 = "unchecked"; }
      if(sensor2!= preferences.getString("sensor2")){
      preferences.putString("sensor2",sensor2);
      }

      sensor1CC = server.arg("sensor1CC");
      Serial.print("sensor1CC: "); Serial.println(sensor1CC);
      if(sensor1CC != ""){
      preferences.putString("sensor1CC",sensor1CC);
      }

      sensor2CC = server.arg("sensor2CC");
      Serial.print("sensor2CC: "); Serial.println(sensor2CC);
      if(sensor2CC != ""){
      preferences.putString("sensor2CC",sensor2CC);
      }

      sensor1Chan = server.arg("sensor1Chan");
      Serial.print("sensor1Chan: "); Serial.println(sensor1Chan);
      if(sensor1Chan != ""){
      preferences.putString("sensor1Chan",sensor1Chan);
      }

      sensor2Chan = server.arg("sensor2Chan");
      Serial.print("sensor2Chan: "); Serial.println(sensor2Chan);
      if(sensor2Chan != ""){
      preferences.putString("sensor2Chan",sensor2Chan);
      }
      
      server.sendHeader("Access-Control-Allow-Origin", "*");
      server.send(200, "text/html", contentHeadStyle+contentReboot);
     }); // Fin sensorscfg
  
//   server.on("/scan", []() {
//      //setupAP();
//      IPAddress ip = WiFi.softAPIP();
//      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
//      content = "<!DOCTYPE HTML>\r\n<html>go back";
//      server.send(200, "text/html", content);
//    });

  server.on("/wificfg", []() {  // Was 'settings'
    ssid = server.arg("ssid");
    if(ssid != ""){
    preferences.putString("ssid",ssid);
    }
    password = server.arg("pass");
    if(password != ""){
    preferences.putString("password",password);
    }
    OSCServer = server.arg("OSCServer");
    if (OSCServer == "checkedTDLF"){
      preferences.putString("checkedTDLF","checked");
      preferences.putString("checkedTouchOSC","unchecked");
      }else{
      preferences.putString("checkedTDLF","unchecked");
      preferences.putString("checkedTouchOSC","checked");
    }

    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/html", contentHeadStyle+contentReboot);
    });

// server.on("/OSCServer", []() {  
//    OSCServer = server.arg("OSCServer");
//    preferences.putString("OSCServer",OSCServer);
//    server.sendHeader("Access-Control-Allow-Origin", "*");
//    server.send(200, "text/html", contentHeadStyle+contentReboot);
//    });


  server.on("/reboot", []() {
    Serial.println("reboot");
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/html", contentHeadStyle+"Rebooting, let's get this party started.</body></html>");
    delay(2000);
    ESP.restart();
    });

   server.on("/modeConfig", []() {
    
    myMode = server.arg("myMode");
    Serial.print("myMode is : ");Serial.println(myMode);
    monDelai = server.arg("monDelai");
    arrayLength = server.arg("arrayLength");
    
    
    if(myMode == "checkedLive"){ // Torpe
      preferences.putString("myMode","live");
      myMode = "live";
      preferences.putString("checkedLive","checked");
      preferences.putString("checkedPlay","unchecked");
      preferences.putString("checkedRecord","unchecked");
      //preferences.putString("checkedErase","unchecked");
    } 
    
    else if(myMode == "checkedPlay") {
      preferences.putString("myMode","playback");
      myMode = "playback";
      preferences.putString("checkedLive","unchecked");
      preferences.putString("checkedPlay","checked");
      preferences.putString("checkedRecord","unchecked");
      //preferences.putString("checkedErase","unchecked");
    } 
    
    else if(myMode == "checkedRecord") {
      Serial.println("********** writing in record mode ***********");
      preferences.putString("myMode","record");
      myMode = "record";
      preferences.putString("checkedLive","unchecked");
      preferences.putString("checkedPlay","unchecked");
      preferences.putString("checkedRecord","checked");
      //preferences.putString("checkedErase","unchecked");
    } 
    
//    else if(myMode == "checkedErase") {
//      preferences.putString("myMode","erase");
//      myMode = "erase";
//      preferences.putString("checkedLive","unchecked");
//      preferences.putString("checkedPlay","unchecked");
//      preferences.putString("checkedRecord","unchecked");
//      preferences.putString("checkedErase","checked");
//    }
    if(monDelai != ""){
    preferences.putString("monDelai",monDelai);
    }
    if(arrayLength != ""){
    preferences.putString("arrayLength",arrayLength);
    }
    
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/html", contentHeadStyle+contentReboot);
    //server.send(200, "text/html", "rebooting, let's get this party started");

  });
  
  server.begin();
  #if defined Display
  displayMessage(1); // Show WiFI connect to CajitaAbierta + IP
  #endif
}

void serverListen(){
  dnsServer.processNextRequest();
  server.handleClient();
}

   
