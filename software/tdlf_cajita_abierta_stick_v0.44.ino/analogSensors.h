#if defined useAnalogSensors

int sensor1Value = 0; 
int sensor2Value = 0; 
int sensor3Value = 0; 
int sensor4Value = 0; 

///// Sensors
//String storedSensor1Chan;
//String storedSensor1CC;
//int storedSensor1ChanInt;
//int storedSensor1CCInt;
//
//String storedSensor2Chan;
//String storedSensor2CC;
//int storedSensor2ChanInt;
//int storedSensor2CCInt;
//
//String storedSensor3Chan;
//String storedSensor3CC;
//int storedSensor3ChanInt;
//int storedSensor3CCInt;
//
//String storedSensor4Chan;
//String storedSensor4CC;
//int storedSensor4ChanInt;
//int storedSensor4CCInt;
//
//bool sensor1 = false;
//bool sensor2 = false;
//bool sensor3 = false;
//bool sensor4 = false;

void readSensors(){  // check the sensors here
  // if (playback == 0 ) {
    if ( sensor1 == "checked"){
      sensor1Value = analogRead(32);
      Serial.print("sensor1Value : ");Serial.println(sensor1Value);
      }
    if ( sensor2 == "checked"){
      sensor2Value = analogRead(33);
      Serial.print("sensor2Value : ");Serial.println(sensor2Value);
      }
    if ( sensor3 == "checked"){
      sensor3Value = analogRead(34);
      Serial.print("sensor3Value : ");Serial.println(sensor3Value);
      }
    if ( sensor4 == "checked"){
      sensor4Value = analogRead(35);
      Serial.print("sensor4Value : ");Serial.println(sensor4Value);
      }
//        } else {
//          sensor1Value = sensorData[sensorIndex+8]; // Read the values from the array
//          sensor2Value = sensorData[sensorIndex+9];
//          sensor3Value = sensorData[sensorIndex+10];
//          sensor4Value = sensorData[sensorIndex+11];
//        }   
 //    }
}
#endif
