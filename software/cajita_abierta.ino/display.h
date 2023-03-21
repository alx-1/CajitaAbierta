////////////// DISPLAY //////////
#if defined Display
#include <SPI.h>
//#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#endif
/////////////////////////////

void displaySetup(){
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  ///////////// DISPLAY /////////////
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  #if defined displayRotate
  display.setRotation(0);
  #endif
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(25, 0);
  display.print(F("Technologies"));// Start at top-left corner
  display.setCursor(30, 16);
  display.println(F("de la fete "));
  
  #if defined Accelerometer
  display.setCursor(0, 35);
  display.println(F("Accel/Press/Sensors"));
  display.setCursor(15, 52);
  display.println(F("CAJITA ABIERTA"));
  
  #endif
  
  display.display();
  delay(2000); // Pause for 1 second
  ////////////////////////////////
}

void displayMessage(int i, int j){

  switch (i) {
    case 1:  // No connection to link or button press to open config portal
      //display.setRotation(2);
      display.clearDisplay();
      display.setTextSize(1);             // Normal 1:1 pixel scale
      display.setTextColor(WHITE);        // Draw white text
      display.setCursor(5, 0);
      display.print(F("Connect to:"));// Start at top-left corner
      display.setCursor(5, 20);
      display.println(F("CajitaAbierta"));
      display.setCursor(5, 52);
      display.println(F("http://192.168.1.1"));
      display.display();
      delay(5000); // Pause for 5 second
      Serial.println("Connect to CajitaAbiera");
      break;
      
    case 2: // We are connected and checking sensors
      display.clearDisplay();
      display.setTextSize(1);             // Normal 1:1 pixel scale
      display.setTextColor(WHITE);        // Draw white text

      if (j == 1){
        display.setCursor(0, 0);
        display.print(F("Recording"));
      }

      #if defined Accelerometer
      if (accelX=="checked"){
      display.setCursor(0, 0);
      display.print(F("AX "));
      display.setCursor(16, 0);
      display.println(aIntX);
      }
      if (accelY=="checked"){
      display.setCursor(42, 0);
      display.print(F("AY "));
      display.setCursor(58, 0);
      display.println(aIntY);
      }
      if (accelZ=="checked"){
      display.setCursor(87, 0);
      display.print(F("AZ "));
      display.setCursor(104, 0);
      display.println(aIntZ);
      }
      if (pan_=="checked"){
      display.setCursor(0, 12);
      display.print(F("X "));
      display.setCursor(16, 12);
      display.println(x);
      }
      if (tilt_=="checked"){
      display.setCursor(42, 12);
      display.print(F("Y "));
      display.setCursor(58, 12);
      display.println(y);
      }
      if (roll_=="checked"){
      display.setCursor(87, 12);
      display.print(F("Z "));
      display.setCursor(104, 12);
      display.println(z);
      }
      #endif

      #if defined PressureSensor
      if (expire=="checked"){
      display.setCursor(0, 24);
      display.print(F("Blow: "));
      display.setCursor(28, 24);
      display.println(int(blowValue));   
      }
      if (inspire=="checked"){   
      display.setCursor(64, 24);
      display.print(F("Suck:"));
      display.setCursor(94, 24);
      display.println(int(suckValue)); 
      }
      #endif

      #if defined useAnalogSensors
      if (sensor1 =="checked"){   
      display.setCursor(0, 36);
      display.print(F("S1:"));
      display.setCursor(16, 36);
      display.println(int(sensor1Value)); 
      }
      if (sensor2 =="checked"){   
      display.setCursor(32, 36);
      display.print(F("S2:"));
      display.setCursor(48, 36);
      display.println(int(sensor2Value)); 
      }
      if (sensor3 == "checked"){
      display.setCursor(64, 36);
      display.print(F("S3:"));
      display.setCursor(80, 36);
      display.println(sensor3Value); 
      }
      if (sensor4 == "checked"){
      display.setCursor(96, 36);
      display.print(F("S4:"));
      display.setCursor(112, 36);
      display.println(sensor4Value);  
      }
      #endif
      
      display.setCursor(5, 52);
      display.println("IP:");
      display.setCursor(22, 52);
      //display.println(WiFi.localIP());
      display.println(monIP);
      display.setCursor(22, 72);
      display.println("port:");
      display.display();
      //delay(1); // Pause for 1 ms
      break;
      
    case 3: // Short Button presses are increasing the value
      display.clearDisplay();
      display.setTextSize(1); 
      if (j == 1){
        display.setCursor(0, 0);
        display.print(F("Recording"));
      }
      display.setTextSize(2);             // Normal 1:1 pixel scale
      display.setTextColor(WHITE);        // Draw white text

      // Serial.print("mesKeys[buttonCounter].c_str() "); Serial.println(mesKeys[buttonCounter].c_str());

      if (preferences.getString(mesKeys[buttonCounter].c_str()) == "checked"){
        display.setCursor(0, 0);
        display.println(mesKeys[buttonCounter]);
        
        display.setCursor(0, 17);
        display.print(F("ch"));
        display.setCursor(26, 17);
        display.println(preferences.getString(mesKeys[buttonCounter+1].c_str()));
        
        display.setCursor(54, 17);
        display.print(F("cc"));
        display.setCursor(80, 17);
        display.println(preferences.getString(mesKeys[buttonCounter+2].c_str()));

        display.setCursor(0, 34);
        display.print(F("value"));
        #if defined Accelerometer
        display.setCursor(80, 34);
        if (mesKeys[buttonCounter] == "accelX"){
        display.println(aIntX); 
        } else if (mesKeys[buttonCounter] == "accelY"){
        display.println(aIntY);   
        } else if (mesKeys[buttonCounter] == "accelZ"){
        display.println(aIntZ);  
        } else if (mesKeys[buttonCounter] == "pan_"){
        display.println(x); 
        }else if (mesKeys[buttonCounter] == "tilt_"){
        display.println(y); 
        }else if (mesKeys[buttonCounter] == "roll_"){
        display.println(z); 
        }
        #endif
        
        #if defined PressureSensor
        else if (mesKeys[buttonCounter] == "expire"){
        display.println(int(blowValue));   
        } else if (mesKeys[buttonCounter] == "inspire"){
        display.println(int(suckValue)); 
        }
        #endif 
         
        if (mesKeys[buttonCounter] == "sensor1"){
        display.println(int(sensor1Value));   
        } else if (mesKeys[buttonCounter] == "sensor2"){
        display.println(int(sensor2Value));   
        }
        
      } else {
      buttonCounter = buttonCounter + 4;  // go on to next value in the list
      }

      display.setTextSize(1);   
      display.setCursor(5, 52);
      display.println("IP:");
      display.setCursor(22, 52);
      display.println(monIP);
      display.setCursor(22, 72);
      display.println("PORT");
      display.display();
      //delay(1); // Pause for 1 ms
     
      break;

    case 4: // recording 
      display.clearDisplay();
      display.setTextSize(2);             // Normal 1:1 pixel scale
      display.setCursor(3, 5);
      display.print(F("Recording"));// Start at top-left corner
      display.setCursor(3, 25);
      display.print(F("Mode"));// Start at top-left corner
      display.display();
      delay(2000);
      break;

    case 5: // stand alone recording
      display.clearDisplay();
      display.setTextSize(2);             // Normal 1:1 pixel scale
      display.setCursor(0, 5);
      display.print(F("Stand Alone"));// Start at top-left corner
      display.setCursor(0, 25);
      display.print(F("Recording"));// Start at top-left corner
      display.display();
      delay(2000);
      break;
      
    case 6: // populate array from file
      display.clearDisplay();
      display.setTextSize(2);             // Normal 1:1 pixel scale
      display.setCursor(0, 5);
      display.print(F("Load Array"));// Start at top-left corner
      display.setCursor(0, 25);
      display.print(F("From File"));// Start at top-left corner
      display.setCursor(0,48);
      display.setTextSize(1);  
      //display.print(F("Might take a few mins")); 
      display.print((j));
      display.setCursor(36,48);
      display.println(F("/"));
      display.setCursor(46,48);
      display.print((myArrayLength));
      display.display();
      // delay(2000);
      break;

    case 7: // Array Loaded
      display.clearDisplay();
      display.setTextSize(2);             // Normal 1:1 pixel scale
      display.setCursor(0, 5);
      display.print(F("Array"));// Start at top-left corner
      display.setCursor(0, 25);
      display.print(F("Loaded"));// Start at top-left corner
      display.display();
      delay(2000);
      break;

    case 8 : // use the array and save it, line by line with commas between the data points
      display.clearDisplay();
      display.setTextSize(2);  // Normal 1:1 pixel scale
      display.setCursor(0, 5);
      display.println(F("Saving to"));// Start at top-left corner
      display.setCursor(0, 25); 
      display.println(F("File"));
      display.setCursor(0,48);
      display.setTextSize(1);  
      //display.print(F("Might take a few mins"));
      display.print((j));
      display.setCursor(36,48);
      display.println(F("/"));
      display.setCursor(46,48);
      display.print((myArrayLength));
      display.display();
      //delay(2000);
      break;

    case 9: // Live mode
      display.clearDisplay();
      display.setTextSize(2);             // Normal 1:1 pixel scale
      display.setCursor(0, 5);
      display.print(F("Live"));// Start at top-left corner
      display.setCursor(0, 25);
      display.print(F("Mode"));// Start at top-left corner
      display.display();
      delay(2000);
      break;
  
    case 10: // Playback mode
      display.clearDisplay();
      display.setTextSize(2);             // Normal 1:1 pixel scale
      display.setCursor(0, 5);
      display.print(F("Playback"));// Start at top-left corner
      display.setCursor(0, 25);
      display.print(F("Mode"));// Start at top-left corner
      display.display();
      delay(2000);
      break;
        
    case 11: // Record mode
      display.clearDisplay();
      display.setTextSize(2);             // Normal 1:1 pixel scale
      display.setCursor(0, 5);
      display.print(F("Record"));// Start at top-left corner
      display.setCursor(0, 25);
      display.print(F("Mode"));// Start at top-left corner
      display.display();
      delay(2000);
      break;
   
   case 12: // Starting portal
      display.clearDisplay();
      display.setTextSize(2);             // Normal 1:1 pixel scale
      display.setCursor(0, 5);
      display.print(F("Starting"));// Start at top-left corner
      display.setCursor(0, 25);
      display.print(F("Portal"));// Start at top-left corner
      display.display();
      delay(2000);
      break;

   case 13: // Connecting to WiFI
      display.clearDisplay();
      display.setTextSize(2);             // Normal 1:1 pixel scale
      display.setCursor(0, 5);
      display.print(F("Connecting"));// Start at top-left corner
      display.setCursor(0, 25);
      display.print(F("to WiFI"));// Start at top-left corner
      display.display();
      delay(2000);
      break;

   case 14: // Starting portal
      display.clearDisplay();
      display.setTextSize(2);             // Normal 1:1 pixel scale
      display.setCursor(0, 5);
      display.print(F("Formatting"));// Start at top-left corner
      display.setCursor(0, 25);
      display.print(F("File System"));// Start at top-left corner
      display.display();
      delay(2000);
      break;
      
      }
}
