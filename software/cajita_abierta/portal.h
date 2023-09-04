//*#include <WebServer.h>
#include <AsyncTCP.h> 

#include <AsyncElegantOTA.h>
#include "ESPAsyncWebServer.h" 
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

//* WebServer server(80);
AsyncWebServer server(80); //*
// Create an Event Source on /events
AsyncEventSource events("/events"); //*


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
  displayMessage(12,0);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  //WiFi.softAP("CajitaAbierta");
  WiFi.softAP(apName);

  portalScanNetworks();
  preferencesGet();
  //monContentHTMLScript();
  monContentHome(); // Try to update with the latest values

  #if defined PressureSensor
  monContentBreath();
  #endif
  monContentSensors();
  monContentMode();
  // if DNSServer is started with "*" for domain name, it will reply with
  // provided IP to all DNS request
  dnsServer.start(DNS_PORT, "*", apIP);
  
  server.onNotFound([](AsyncWebServerRequest *request){
    Serial.println("Captive Portal-ish");
    request->send(200, "text/html", contentHeadStyle+menuHome+routersList+contentHome); 
    //request->send(200, "text/html", "hello home"); 
    });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("Captive Portal-ish");
    //request->send(200, "text/html", paramPage); 
    request->send(200, "text/html", "hello home"); 
    });
  
  server.on("/accel.html", HTTP_GET, [](AsyncWebServerRequest *request){ 
    Serial.println("whaaat accel");
    #if defined Accelerometer
    monContentAccel(); // _This_ is weird
    #endif
    request->send(200, "text/html", contentHeadStyle+contentAccel); 
    //request->send(200, "text/html", contentHeadStyle+"hello world"); 

    });
  
  server.on("/blowsuck.html", HTTP_GET, [](AsyncWebServerRequest *request){ 
    request->send(200, "text/html", contentHeadStyle+contentBreath); 
    });
  
  server.on("/sensors.html", HTTP_GET, [](AsyncWebServerRequest *request){ 
    calibratingSensors = "analogSensors"; // accel, blow/suck, none
    myMode = "calibrating";
    request->send(200, "text/html", contentHeadStyle+contentSensors+contentScript); 
    });
  
  server.on("/mode.html", HTTP_GET, [](AsyncWebServerRequest *request){ 
    request->send(200, "text/html", contentHeadStyle+contentMode); 
    });
  
  #if defined Accelerometer
  server.on("/accelcfg", HTTP_GET, [](AsyncWebServerRequest *request){ 
     int params = request->params();
        for(int i=0;i<params;i++){
        AsyncWebParameter* p = request->getParam(i);
        if (p->name() == "accelX"){accelX = p->value().c_str();}
        else if (p->name() == "accelXChan"){accelXChan = p->value().c_str();}
        else if (p->name() == "accelXCC"){accelXCC = p->value().c_str();}
        
        else if (p->name() == "accelY"){accelY = p->value().c_str();}
        else if (p->name() == "accelYChan"){accelYChan = p->value().c_str();}
        else if (p->name() == "accelYCC"){accelYCC = p->value().c_str();}
        
        else if (p->name() == "accelZ"){accelZ = p->value().c_str();}
        else if (p->name() == "accelZChan"){accelXChan = p->value().c_str();}
        else if (p->name() == "accelZCC"){accelZCC = p->value().c_str();}
        
        else if (p->name() == "pan_"){pan_ = p->value().c_str();}
        else if (p->name() == "panChan"){panChan = p->value().c_str();}
        else if (p->name() == "panCC"){panCC = p->value().c_str();}
        
        else if (p->name() == "tilt_"){tilt_ = p->value().c_str();}
        else if (p->name() == "tiltChan"){tiltChan = p->value().c_str();}
        else if (p->name() == "tiltCC"){tiltCC = p->value().c_str();}
        
        else if (p->name() == "roll_"){roll_ = p->value().c_str();}
        else if (p->name() == "rollChan"){rollChan = p->value().c_str();}
        else if (p->name() == "rollCC"){rollCC = p->value().c_str();}
        
        Serial.printf("_GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
        }
    
    // AccelX // check // channel // CC message
    if ( accelX == "on" ){ accelX = "checked"; } else { accelX = "unchecked"; }
    
    Serial.print("accelX: "); Serial.println(accelX);
    if(accelX != preferences.getString("accelX")){
    preferences.putString("accelX",accelX);
    }
    
    Serial.print("accelXChan: "); Serial.println(accelXChan);
    if(accelXChan != ""){
    preferences.putString("accelXChan",accelXChan);
    }
    
    Serial.print("accelXCC: "); Serial.println(accelXCC);
    if(accelXCC != ""){
    preferences.putString("accelXCC",accelXCC);
    }
    
    // AccelY // check // channel // CC message
    if ( accelY == "on" ){ accelY = "checked"; } else { accelY = "unchecked"; }
    Serial.print("accelY: "); Serial.println(accelY);
    if(accelY != preferences.getString("accelY")){
    preferences.putString("accelY",accelY);
    }

    Serial.print("accelYChan: "); Serial.println(accelYChan);
    if(accelYChan != ""){
    preferences.putString("accelYChan",accelYChan);
    }
    
    Serial.print("accelYCC: "); Serial.println(accelYCC);
    if(accelYCC != ""){
    preferences.putString("accelYCC",accelYCC);
    }

    // AccelZ // check // channel // CC message
    if ( accelZ == "on" ){ accelZ = "checked"; } else { accelZ = "unchecked"; }
    Serial.print("accelZ: "); Serial.println(accelZ);
    if(accelZ != preferences.getString("accelZ")){
    preferences.putString("accelZ",accelZ);
    }
    
    Serial.print("accelZChan: "); Serial.println(accelZChan);
    if(accelZChan != ""){
    preferences.putString("accelZChan",accelZChan);
    }
    
    Serial.print("accelZCC: "); Serial.println(accelZCC);
    if(accelZCC != ""){
    preferences.putString("accelZCC",accelZCC);
    }

    // Pan // check // channel // CC message
    if ( pan_ == "on" ){ pan_ = "checked"; } else { pan_ = "unchecked"; }
    Serial.print("pan_: "); Serial.println(pan_);
    if(pan_ != preferences.getString("pan_")){
    preferences.putString("pan_",pan_);
    }

    Serial.print("panChan: "); Serial.println(panChan);
    if(panChan != ""){
    preferences.putString("panChan",panChan);
    }
    
    Serial.print("panCC: "); Serial.println(panCC);
    if(panCC != ""){
    preferences.putString("panCC",panCC);
    }

    // Tilt // check // channel // CC message
    if ( tilt_ == "on" ){ tilt_ = "checked"; } else { tilt_ = "unchecked"; }
    Serial.print("tilt_: "); Serial.println(tilt_);
    if(tilt_ != preferences.getString("tilt_")){
    preferences.putString("tilt_",tilt_);
    }

    Serial.print("tiltChan: "); Serial.println(tiltChan);
    if(tiltChan != ""){
    preferences.putString("tiltChan",tiltChan);
    }
    
    Serial.print("tiltCC: "); Serial.println(tiltCC);
    if(tiltCC != ""){
    preferences.putString("tiltCC",tiltCC);
    }
    
    // Roll // check // channel // CC message
    if ( roll_ == "on" ){ roll_ = "checked"; } else { roll_ = "unchecked"; }
    Serial.print("roll_: "); Serial.println(roll_);
    if(roll_ != preferences.getString("roll_")){
    preferences.putString("roll_",roll_);
    }

    Serial.print("rollChan: "); Serial.println(rollChan);
    if(rollChan != ""){
    preferences.putString("rollChan",rollChan);
    }
    
    Serial.print("rollCC: "); Serial.println(rollCC);
    if(rollCC != ""){
    preferences.putString("rollCC",rollCC);
    }

    request->send(200, "text/html", contentHeadStyle+contentReboot);   
  });
  #endif

#if defined PressureSensor
  server.on("/blowsuckcfg", HTTP_GET, [](AsyncWebServerRequest *request){ 
        int params = request->params();
        for(int i=0;i<params;i++){
        AsyncWebParameter* p = request->getParam(i);
        if (p->name() == "expire"){expire = p->value().c_str();}
        else if (p->name() == "inspire"){inspire = p->value().c_str();}
        else if (p->name() == "blowChan"){blowChan = p->value().c_str();}
        else if (p->name() == "suckChan"){suckChan = p->value().c_str();}
        else if (p->name() == "blowCC"){blowCC = p->value().c_str();}
        else if (p->name() == "suckCC"){suckCC = p->value().c_str();}
        Serial.printf("_GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
        }
      if ( expire == "on" ){ expire = "checked"; } else { expire = "unchecked"; }
      if(expire!= preferences.getString("expire")){
      preferences.putString("expire",expire);
      }
      if ( inspire == "on" ){ inspire = "checked"; } else { inspire = "unchecked"; }
      if(inspire!= preferences.getString("inspire")){
      preferences.putString("inspire",inspire);
      }
      Serial.print("blowChan: "); Serial.println(blowChan);
      if(blowChan != ""){
      preferences.putString("blowChan",blowChan);
      }
      Serial.print("suckChan: "); Serial.println(suckChan);
      if(suckChan != ""){
      preferences.putString("suckChan",suckChan);
      }
      Serial.print("blowCC: "); Serial.println(blowCC);
      if(blowCC != ""){
      preferences.putString("blowCC",blowCC);
      }
      Serial.print("suckCC: "); Serial.println(suckCC);
      if(suckCC != ""){
      preferences.putString("suckCC",suckCC);
      }
      
      request->send(200, "text/html", contentHeadStyle+contentReboot);
    }); // Fin blowsuckcfg
#endif

    server.on("/sensorscfg", HTTP_GET, [](AsyncWebServerRequest *request){
      preferencesGet();
      //monContentHTMLScript();
      monContentSensors();
      
      calibratingSensors = "analogSensors"; // accel, blow/suck, none
      myMode = "calibrating";
      initSensorsCfg(); // set them all to "unchecked"
      int params = request->params();
    for(int i=0;i<params;i++){
      AsyncWebParameter* p = request->getParam(i);
        if (p->name() == "sensor1"){sensor1 = p->value().c_str();
          Serial.print(" ---- sensor1 :");Serial.println(sensor1); 
          }
        else if (p->name() == "s1EMAFilter"){s1EMAFilter = p->value().c_str();}
        else if (p->name() == "sensor1Midi"){sensor1Midi = p->value().c_str();}
        else if (p->name() == "sensor1Chan"){sensor1Chan = p->value().c_str();}
        else if (p->name() == "sensor1CC"){sensor1CC = p->value().c_str();}
        
        else if (p->name() == "sensor2"){sensor2 = p->value().c_str();
          Serial.print(" ---- sensor2 :");Serial.println(sensor2);
          }
        else if (p->name() == "s2EMAFilter"){s2EMAFilter = p->value().c_str();}
        else if (p->name() == "sensor2Midi"){sensor2Midi = p->value().c_str();}
        else if (p->name() == "sensor2Chan"){sensor2Chan = p->value().c_str();}
        else if (p->name() == "sensor2CC"){sensor2CC = p->value().c_str();}
        Serial.printf("_GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
    }

      if ( sensor1 == "on" ){ sensor1 = "checked"; } else { sensor1 = "unchecked"; }
      //if(sensor1!= preferences.getString("sensor1")){
        preferences.putString("sensor1",sensor1);
        //}

      Serial.print("sensor1CC: "); Serial.println(sensor1CC);
      if(sensor1CC != ""){
        Serial.print("sensor1CC: "); Serial.println(sensor1CC);
        preferences.putString("sensor1CC",sensor1CC);
        }

      if ( sensor1Midi == "on" ){ sensor1Midi = "checked"; } else { sensor1Midi = "unchecked"; }
      if(sensor1Midi!= preferences.getString("sensor1Midi")){
        preferences.putString("sensor1Midi",sensor1Midi);
        }

      Serial.print("sensor1Chan: "); Serial.println(sensor1Chan);
      if(sensor1Chan != ""){
        preferences.putString("sensor1Chan",sensor1Chan);
        }
        
      if ( s1EMAFilter == "on" ){ s1EMAFilter = "checked"; } else { s1EMAFilter = "unchecked"; }
      if(s1EMAFilter != preferences.getString("s1EMAFilter")){
        preferences.putString("s1EMAFilter",s1EMAFilter);
        Serial.print("writing s1EMAFilter : ");Serial.println(s1EMAFilter);
        s1EMAFilter = preferences.getString("s1EMAFilter","grr");
        Serial.print("reading s1EMAFilter : ");Serial.println(s1EMAFilter); 
        }

      /*
      preferences.putString("sensor1Min",sensor1Min);
      //preferences.putString("sensor1Min","4096");
      Serial.print("writing sensor1Min : ");Serial.println(sensor1Min);
      sensor1Min = preferences.getString("sensor1Min","4095");
      Serial.print("reading sensor1Min : ");Serial.println(sensor1Min); 

      preferences.putString("sensor1Max",sensor1Max);
      //preferences.putString("sensor1Max","0");
      Serial.print("writing sensor1Max : ");Serial.println(sensor1Max);
      sensor1Max = preferences.getString("sensor1Max","0");
      Serial.print("reading sensor1Max : ");Serial.println(sensor1Max); 
       */
      // sensor2      
      if ( sensor2 == "on" ){ sensor2 = "checked"; } else { sensor2 = "unchecked"; }
      if(sensor2!= preferences.getString("sensor2")){
      preferences.putString("sensor2",sensor2);
      }

      if ( s2EMAFilter == "on" ){ s2EMAFilter = "checked"; } else { s2EMAFilter = "unchecked"; }
      if(s2EMAFilter != preferences.getString("s2EMAFilter")){
        preferences.putString("s2EMAFilter",s2EMAFilter);
        Serial.print("writing s2EMAFilter : ");Serial.println(s2EMAFilter);
        s2EMAFilter = preferences.getString("s2EMAFilter","grr");
        Serial.print("reading s2EMAFilter : ");Serial.println(s2EMAFilter); 
      }

      if ( sensor2Midi == "on" ){ sensor2Midi = "checked"; } else { sensor2Midi = "unchecked"; }
      if(sensor2Midi!= preferences.getString("sensor2Midi")){
        preferences.putString("sensor2Midi",sensor2Midi);
      }
    
      Serial.print("sensor2Chan: "); Serial.println(sensor2Chan);
      if(sensor2Chan != ""){
      preferences.putString("sensor2Chan",sensor2Chan);
      }
      
      Serial.print("sensor2CC: "); Serial.println(sensor2CC);
      if(sensor2CC != ""){
      preferences.putString("sensor2CC",sensor2CC);
      }

      preferencesGet();
      monContentSensors(); // reload the new prefs for display
      request->send(200, "text/html", contentHeadStyle+contentSensors+contentScript); 
        
     }); // Fin sensorscfg

  server.on("/wificfg", HTTP_GET, [](AsyncWebServerRequest *request){ 

    int params = request->params();
    for(int i=0;i<params;i++){
      AsyncWebParameter* p = request->getParam(i);
      if (p->name() == "ssid"){ssid = p->value().c_str();}
      else if (p->name() == "pass"){password = p->value().c_str();}
      else if (p->name() == "OSCServer"){OSCServer = p->value().c_str();}
      Serial.printf("_GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
      }
    
    if(ssid != ""){
    preferences.putString("ssid",ssid);
    }
    if(password != ""){
    preferences.putString("password",password);
    }
    
    Serial.print("OSCServer : ");Serial.println(OSCServer);
    if (OSCServer == "checkedTDLF"){
      preferences.putString("checkedTDLF","checked");
      preferences.putString("checkedTOSCB","unchecked");
      preferences.putString("checkedOSC","unchecked");
      } else if (OSCServer == "checkedTOSCB"){
        preferences.putString("checkedTDLF","unchecked");
        preferences.putString("checkedTOSCB","checked");
        preferences.putString("checkedOSC","unchecked");
      } else if (OSCServer == "checkedOSC"){
        Serial.println("yes it is !!!!");
        preferences.putString("checkedTDLF","unchecked");
        preferences.putString("checkedTOSCB","unchecked");
        preferences.getString("checkedTOSCB","not set");
        Serial.println(preferences.getString("checkedTOSCB"));
        preferences.putString("checkedOSC","checked");
        }

    request->send(200, "text/html", contentHeadStyle+contentReboot);

    });

  server.on("/reboot", HTTP_GET, [](AsyncWebServerRequest *request){ 
    Serial.println("reboot");
    request->send(200, "text/html", contentHeadStyle+"Rebooting, let's get this party started.</body></html>"); 
    delay(2000);
    ESP.restart();
    });

  server.on("/modeConfig", HTTP_GET, [](AsyncWebServerRequest *request){
    int params = request->params();
    for(int i=0;i<params;i++){
      AsyncWebParameter* p = request->getParam(i);
      if (p->name() == "myMode"){myMode = p->value().c_str();}
      else if (p->name() == "monDelai"){monDelai = p->value().c_str();}
      else if (p->name() == "monArrayLength"){monArrayLength = p->value().c_str();}
      //Serial.printf("_GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
      }
    
    Serial.print("myMode is : ");Serial.println(myMode);

    if(myMode == "checkedLive"){ 
      preferences.putString("myMode","live");
      // myMode = "live";
      preferences.putString("checkedLive","checked");
      preferences.putString("checkedPlay","unchecked");
      preferences.putString("checkedRecord","unchecked");
      preferences.putString("checkedFormatFS","unchecked");
      } else if(myMode == "checkedPlay") {
      preferences.putString("myMode","playback");
      // myMode = "playback";
      preferences.putString("checkedLive","unchecked");
      preferences.putString("checkedPlay","checked");
      preferences.putString("checkedRecord","unchecked");
      preferences.putString("checkedFormatFS","unchecked");
      } else if(myMode == "checkedRecord") {
      Serial.println("*** Will reboot in record mode ***");
      preferences.putString("myMode","record");
      // myMode = "record";
      preferences.putString("checkedLive","unchecked");
      preferences.putString("checkedPlay","unchecked");
      preferences.putString("checkedRecord","checked");
      preferences.putString("checkedFormatFS","unchecked");
      } else if(myMode == "checkedFormatFS") {
      preferences.putString("myMode","formatFS");
      // myMode = "formatFS";
      preferences.putString("checkedLive","unchecked");
      preferences.putString("checkedPlay","unchecked");
      preferences.putString("checkedRecord","unchecked");
      preferences.putString("checkedFormatFS","checked");
      }

    Serial.print("monDelai : ");Serial.println(monDelai);
    if(monDelai != ""){
      Serial.println("Writing monDelai");
      preferences.putString("monDelai",monDelai);
      }
    if(monArrayLength != ""){
      preferences.putString("monArrayLength",monArrayLength);
      }
      
    request->send(200, "text/html", contentHeadStyle+contentReboot);
    
  });
  
  AsyncElegantOTA.begin(&server);    // Start AsyncElegantOTA // Connect to 192.168.1.1/update
 
  // Handle Web Server Events
  events.onConnect([](AsyncEventSourceClient *client){
    if(client->lastId()){
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    }
    // send event with message "hello!", id current millis
    // and set reconnect delay to 1 second
    client->send("hello!", NULL, millis(), 10000);
  });
  
  server.addHandler(&events);
  
  server.begin();
  #if defined Display
  displayMessage(1,0); // Show WiFI connect to CajitaAbierta + IP
  #endif
}

void serverListen(){
  dnsServer.processNextRequest();
  //*server.handleClient();
}

   
