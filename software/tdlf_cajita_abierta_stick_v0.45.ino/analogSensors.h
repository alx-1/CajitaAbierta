#if defined useAnalogSensors

int sensor1Value = 0; 
int sensor2Value = 0; 
int sensor3Value = 0; 
int sensor4Value = 0; 

void readSensors(){  // check the sensors here
  
    if ( sensor1 == "checked"){
      sensor1Value = analogRead(32); // R3
      Serial.print("sensor1Value : ");Serial.println(sensor1Value);
      }
    if ( sensor2 == "checked"){
      sensor2Value = analogRead(33);  // R4
      Serial.print("sensor2Value : ");Serial.println(sensor2Value);
      }
    if ( sensor3 == "checked"){
      sensor3Value = analogRead(34);  // R1
      R1
      Serial.print("sensor3Value : ");Serial.println(sensor3Value);
      }
    if ( sensor4 == "checked"){
      sensor4Value = analogRead(35);  // R2
      Serial.print("sensor4Value : ");Serial.println(sensor4Value);
      }
//       
}

void playbackReadSensors(){
    if ( sensor1 == "checked"){
      sensor1Value = sensorData[sensorIndex+8]; // Read the values from the array
      }
    if ( sensor2 == "checked"){
      sensor2Value = sensorData[sensorIndex+9];
      }
    if ( sensor3 == "checked"){
      sensor3Value = sensorData[sensorIndex+10];
      }
    if ( sensor4 == "checked"){
      sensor4Value = sensorData[sensorIndex+11];
    }
 
}

#endif
