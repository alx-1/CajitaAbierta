#include <MicroOscUdp.h>

WiFiUDP udp;
IPAddress sendIp(192, 168, 0, 255); // <- default not really used, we are using Bonjour (mDNS) to find IP and PORT of touchoscbridge
unsigned int sendPort = 12101; // <- touchosc port
bool oscServerFound = false;

MicroOscUdp<1024> oscUdp(&udp, sendIp, sendPort);
uint8_t midi[4]; 

void sendOSCMidi(){
 
  for (int i = 0; i<41; i=i+4){

    if (preferences.getString(mesKeys[i].c_str()) == "checked"){
    
      midi[0] = (preferences.getString(mesKeys[i+1].c_str())).toInt(); // Midi Channel value
        #if defined PressureSensor
          if (mesKeys[i] == "accelX"){
          midi[1] = aIntX; 
          } else if (mesKeys[i] == "accelY"){
          midi[1] = aIntY;   
          } else if (mesKeys[i] == "accelZ"){
          midi[1] = aIntZ;  
          } else if (mesKeys[i] == "pan_"){
          midi[1] = x; 
          }else if (mesKeys[i] == "tilt_"){
          midi[1] = y; 
          }else if (mesKeys[i] == "roll_"){
          midi[1] = z; 
          }
          #endif
          #if defined PressureSensor
          if (mesKeys[i] == "expire"){
          midi[1] = int(blowValue);   
          } else if (mesKeys[i] == "inspire"){
          midi[1] = int(suckValue); 
          }
          #endif  
          if (mesKeys[i] == "sensor1"){
          midi[1] = int(sensor1Value);   
          } else if (mesKeys[i] == "sensor2"){
          midi[1] = int(sensor2Value);   
        }
    midi[2] = (preferences.getString(mesKeys[i+2].c_str())).toInt(); // CC value
    midi[3] = 0;     // Extra  

   if (checkedTDLF == "checked"){
      // Serial.println("sending to tdlf");
      oscUdp.sendMessage("/midi",  "m",  midi); // send to tdlf server
      } else if (checkedTOSCB == "checked" || checkedOSC == "checked"){
        oscUdp.sendMessage("/midi/", "i", midi[1]); // send to Udp server, such as chataigne
      }
     
    
    //int monInt = random(42);
    //oscUdp.sendMessage("/midi/sensor1", "i", monInt); // send to Udp server

    // delay(1); // delay(2)
    }
  }
  // hard coded for testing
  // midi[0] = 6;      // midi channel // 90 + midi channel (note on)
  // midi[1] = z; // SensorValue  // velocity
  // midi[2] = 54;     // Control Change message (11 is expression) // Pitch (note value)
  // midi[3] = 0;     // Extra                                          
  // oscUdp.sendMessage("/midi",  "m",  midi); // send to Udp server
}


void browseService(const char * service, const char * proto){
      Serial.printf("Browsing for service _%s._%s.local. ... ", service, proto);
    int n = MDNS.queryService(service, proto);
    if (n == 0) {
      analogWrite(LED_BUILTIN, 255);
      delay(250);
      analogWrite(LED_BUILTIN, 0);
      delay(250);
      Serial.println("no services found");
      } else {
      Serial.print(n);
      Serial.println(" service(s) found");
      for (int i = 0; i < n; ++i) {
        oscUdp.setDestination(MDNS.IP(i), MDNS.port(i));
        // Print details for each service found
        Serial.print("  ");
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(MDNS.hostname(i));
        Serial.print(" (");
        Serial.print(MDNS.IP(i));
        Serial.print(":");
        Serial.print(MDNS.port(i));
        Serial.println(")");
        }
        analogWrite(LED_BUILTIN, 255);
        oscServerFound = true; 
      }
}
