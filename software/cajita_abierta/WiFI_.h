#include <WiFi.h> 
//****ESPAsyncWebServer.h

void getMacAddress(){
  Serial.println(WiFi.macAddress());
  // Do a little work to get a unique-ish name. Append the
  // 5th byte of the mac address
  int WL_MAC_ADDR_LENGTH = 6;
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String hexByte = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX);
  hexByte.toLowerCase();
  // String apNameString = "CajitaAbierta" + hexByte; // re-enable later
  String apNameString = "CajitaAbierta";
  Serial.print("hexByte : ");Serial.println(hexByte);
  Serial.print("apNameString : ");Serial.println(apNameString);
  for (int i = 0; i < apNameString.length(); i++)
    apName[i] = apNameString.charAt(i);
}

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
