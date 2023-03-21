#include <WiFi.h> 
#include <ElegantOTA.h> 

bool testWifi(void)
{
  displayMessage(13,0);
  int c = 0;
  //Serial.println("Waiting for Wifi to connect");
  while ( c < 30 ) {
    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
      return true;
    }
    monIP = WiFi.localIP();
    delay(500);
      Serial.print("*");
    c++;
  }
  Serial.println("");
  Serial.println("Connect timed out, opening AP");
  return false;
}
