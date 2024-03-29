#if defined Accelerometer
#include <ADXL345.h>
ADXL345 adxl; //variable adxl is an instance of the ADXL345 library
double ax,ay,az; // actual acceleration on all axis
int aIntX, aIntY, aIntZ; // Lose precision but hey it's MIDI!
int x,y,z; // pan tilt roll
bool error = 0;

//
///// Accelerometer ///
//String storedAccelxChan;
//String storedAccelxCC;
//int storedAccelxChanInt;
//int storedAccelxCCInt;
//
//String storedAccelyChan;
//String storedAccelyCC;
//int storedAccelyChanInt;
//int storedAccelyCCInt;
//
//String storedAccelzChan;
//String storedAccelzCC;
//int storedAccelzChanInt;
//int storedAccelzCCInt;
//
//String storedPanChan;
//String storedPanCC;
//int storedPanChanInt;
//int storedPanCCInt;
//
//String storedTiltChan;
//String storedTiltCC;
//int storedTiltChanInt;
//int storedTiltCCInt;
//
//String storedRollChan;
//String storedRollCC;
//int storedRollChanInt;
//int storedRollCCInt;
//
//bool checkAccel = false;
//bool checkPanTiltRoll = false;

bool readAccelerometer();

void accelerometerSetup(){
  
  adxl.powerOn();

  //set activity/ inactivity thresholds (0-255)
  adxl.setActivityThreshold(75); //62.5mg per increment
  adxl.setInactivityThreshold(75); //62.5mg per increment
  adxl.setTimeInactivity(10); // how many seconds of no activity is inactive?
 
  //look of activity movement on this axes - 1 == on; 0 == off 
  adxl.setActivityX(1);
  adxl.setActivityY(1);
  adxl.setActivityZ(1);
 
  //look of inactivity movement on this axes - 1 == on; 0 == off
  adxl.setInactivityX(1);
  adxl.setInactivityY(1);
  adxl.setInactivityZ(1);
 
  //look of tap movement on this axes - 1 == on; 0 == off
  adxl.setTapDetectionOnX(0);
  adxl.setTapDetectionOnY(0);
  adxl.setTapDetectionOnZ(0); // 1 
 
  //set values for what is a tap, and what is a double tap (0-255)
  adxl.setTapThreshold(50); //62.5mg per increment
  adxl.setTapDuration(15); //625us per increment
  adxl.setDoubleTapLatency(80); //1.25ms per increment
  adxl.setDoubleTapWindow(200); //1.25ms per increment
 
  //set values for what is considered freefall (0-255)
  adxl.setFreeFallThreshold(7); //(5 - 9) recommended - 62.5mg per increment
  adxl.setFreeFallDuration(45); //(20 - 70) recommended - 5ms per increment
 
  //setting all interrupts to take place on int pin 1
  //I had issues with int pin 2, was unable to reset it
  adxl.setInterruptMapping( ADXL345_INT_SINGLE_TAP_BIT,   ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_DOUBLE_TAP_BIT,   ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_FREE_FALL_BIT,    ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_ACTIVITY_BIT,     ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_INACTIVITY_BIT,   ADXL345_INT1_PIN );
 
  //register interrupt actions - 1 == on; 0 == off  
  adxl.setInterrupt( ADXL345_INT_SINGLE_TAP_BIT, 0);
  adxl.setInterrupt( ADXL345_INT_DOUBLE_TAP_BIT, 0);
  adxl.setInterrupt( ADXL345_INT_FREE_FALL_BIT,  0);
  adxl.setInterrupt( ADXL345_INT_ACTIVITY_BIT,   0);
  adxl.setInterrupt( ADXL345_INT_INACTIVITY_BIT, 0);
  Serial.println("Accelerometer setup complete");
}


bool readAccelerometer() {
  Serial.println("Reading accelerometer");

  adxl.readXYZ(&x, &y, &z); //read the accelerometer values and store them in variables  x,y,z
  x = map(x,-320,320,0,127); // Should be 355 degrees but in practice I don't see values above 320...
  y = map(y,-320,320,0,127);
  z = map(z,-320,320,0,127);
  // Output x,y,z values
  Serial.print("values of X , Y , Z: ");
  Serial.print(x);
  Serial.print(" , ");
  Serial.print(y);
  Serial.print(" , ");
  Serial.println(z);
  
  double xyz[3];
  //double ax,ay,az;
  adxl.getAcceleration(xyz);
  aIntX = int(xyz[0] * 100);
  aIntY = int(xyz[1] * 100);
  aIntZ = int(xyz[2] * 100);
  aIntX = map(aIntX,-200,200,0,127);
  aIntY = map(aIntY,-200,200,0,127);
  aIntZ = map(aIntZ,-200,200,0,127);
  
      Serial.print("X=");
      Serial.print(aIntX);
      Serial.println(" g");
      Serial.print("Y=");
      Serial.print(aIntY);
      Serial.println(" g");
      Serial.print("Z=");
      Serial.print(aIntZ);
      Serial.println(" g");
      Serial.println("**********************");
  delay(1); // 50
 
  return 0;
}

void checkAccelerometer(){
    Serial.println("checking accelerometer");
    if ( accelX == "checked"|| accelY == "checked" || accelZ == "checked" || pan_ == "checked" || tilt_ == "checked" || roll_ == "checked"){
    
        error = readAccelerometer(); // Using the seed library (thank you!)
    
      } 
} // End readAccelerometer

void playbackAccelerometer(){
  
   if ( accelX == "checked"|| accelY == "checked" || accelZ == "checked" || pan_ == "checked" || tilt_ == "checked" || roll_ == "checked"){
        // play it back from memory
        aIntX = sensorData[sensorIndex];  // fill in the values from the sensorData array : " );
        // Serial.print("Playback, ");Serial.print("sensorIndex aIntX : "); Serial.print(sensorIndex);Serial.print(" value = ");Serial.println(sensorData[sensorIndex]);
        aIntY = sensorData[sensorIndex+1];
        //Serial.print("aIntY err : " );
        //Serial.println(aIntY);
        aIntZ = sensorData[sensorIndex+2];
        //Serial.print("aIntZ err: " );
        //Serial.println(aIntZ);
        x = sensorData[sensorIndex+3]; 
           //     Serial.print("Playback, ");Serial.print("sensorIndex + 3 X : "); Serial.print(sensorIndex+3);Serial.print(" value = ");Serial.println(sensorData[sensorIndex+3]);
 
        y = sensorData[sensorIndex+4];
           //     Serial.print("Playback, ");Serial.print("sensorIndex + 4 Y : "); Serial.print(sensorIndex+4);Serial.print(" value = ");Serial.println(sensorData[sensorIndex+4]);

        z = sensorData[sensorIndex+5];
            //    Serial.print("Playback, ");Serial.print("sensorIndex + 5 Z : "); Serial.print(sensorIndex+5);Serial.print(" value = ");Serial.println(sensorData[sensorIndex+5]);

      }
}

 #endif
