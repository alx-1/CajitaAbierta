#if defined useAnalogSensors

int sensor1Value = 0; 
int sensor2Value = 0; 
int sensor3Value = 0; 
int sensor4Value = 0; 

void readSensors(){  // check the sensors here
    // Serial.println("reading sensors");
 
    if ( sensor1 == "checked" ){
      sensor1Value = analogRead(32); // R3 // 32
      Serial.print("sensor1Value : ");Serial.println(sensor1Value);
      if(s1EMAFilter == "checked"){
        sensor1Value = ema_filter(sensor1Value, history1);
        //Serial.print("sensor1Value After EMA filtering : ");Serial.println(sensor1Value);
        }
      // Serial.print("sensor1Min test: ");Serial.println(sensor1Min);
     /* if(sensor1Min.toInt() > sensor1Value){
        sensor1Min = sensor1Value;
        Serial.print("sensor1Min: ");Serial.println(sensor1Min);
        }
      if(sensor1Max.toInt() < sensor1Value){
        sensor1Max = sensor1Value;
        Serial.print("sensor1Max: ");Serial.println(sensor1Max);
        }
      */
      if (sensor1Midi == "checked"){
        //sensor1Value = map(sensor1Value,sensor1Min.toInt(),sensor1Max.toInt(),0,127);
        sensor1Value = map(sensor1Value,0,4095,0,127);
        }
      
      } else { sensor2Value = -42; }
      
    if (sensor2 == "checked"){
      sensor2Value = analogRead(33);  // R4
      //Serial.print("sensor2Value : ");Serial.println(sensor2Value);
      if(s2EMAFilter == "checked"){
        sensor2Value = ema_filter(sensor2Value, history2);
        //Serial.print("sensor2Value After EMA filtering : ");Serial.println(sensor2Value);
      }
      /*
      if(sensor2Min.toInt() > sensor2Value){
        sensor2Min = sensor2Value;
        }
      if(sensor2Max.toInt() < sensor2Value){
        sensor2Max = sensor2Value;
        }
      */
      if (sensor2Midi == "checked"){
        // sensor2Value = map(sensor2Value,sensor2Min.toInt(),sensor2Max.toInt(),0,127);
        sensor2Value = map(sensor2Value,0,4095,0,127);
        }  
      } else { sensor2Value = -42; }
    /*if ( sensor3 == "checked"){
      sensor3Value = analogRead(34);  // R1
      Serial.print("sensor3Value : ");Serial.println(sensor3Value);
      }
    if ( sensor4 == "checked"){
      sensor4Value = analogRead(35);  // R2
      Serial.print("sensor4Value : ");Serial.println(sensor4Value);
      }*/
//    
      if ( calibratingSensors == "analogSensors" ){
        sendSensorsData("analogSensors");   
      }
}

void playbackReadSensors(){
    //Serial.print("sensor1: ");Serial.println(sensor1);
    if ( sensor1 == "checked"){
      sensor1Value = sensorData[sensorIndex+8]; // Read the values from the array
      //Serial.print("sensor1Value at : ");
      //Serial.print(sensorIndex+8);
      //Serial.print(" : ");
      //Serial.println(sensor1Value);
      }
    if ( sensor2 == "checked"){
      sensor2Value = sensorData[sensorIndex+9];
      // Serial.print("sensor2Value : ");
      // Serial.print(sensorIndex+9);
      // Serial.println(sensor2Value);
      }
    if ( sensor3 == "checked"){
      sensor3Value = sensorData[sensorIndex+10];
      }
    if ( sensor4 == "checked"){
      sensor4Value = sensorData[sensorIndex+11];
    }
 
}

void initSensorsCfg(){ // This is needed because radio buttons do not return values if unchecked
  sensor1 = "unchecked";
  s1EMAFilter = "unchecked";
  sensor1Midi = "unchecked";
  sensor2 = "unchecked";
  s2EMAFilter = "unchecked";
  sensor2Midi = "unchecked";
}

#endif
