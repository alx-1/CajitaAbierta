

///// LITTLEFS ///

void littleFSSetup(){
  
  if (LITTLEFS.begin()){
    Serial.println(F("Initializing FS done."));
  }else{
    Serial.println(F("fail."));
  }

}

void littleFSFormat(){
  
    LITTLEFS.format(); ///////////// Only do this once ///////////////////
    Serial.println("Formatting FS (erasing previously recorded values!");
    File file = LITTLEFS.open("/sensorData.txt", "w");
    if(!file){
       Serial.println("- failed to open file for writing");
       return;
    }
       
    if(file){
      Serial.println("Testing Write file content!");
      file.print("77");
      file.close();
      LITTLEFS.remove("/sensorData.txt");
      Serial.println("File removed!");
      }else{
      Serial.println("Problem on create file!");
    }
    
    preferences.putString("myMode","live");
    preferences.putString("checkedLive","checked");
    preferences.putString("checkedPlay","unchecked");
    preferences.putString("checkedRecord","unchecked");
    preferences.putString("checkedFormatFS","unchecked");
    ESP.restart();
}



void readArrayFromFile(){ // Open file, save it into the array and start going through the array
    //displayMessage(6,0); 

    File filetoRead = LITTLEFS.open(F("/sensorData.txt"), "r");
    if(!filetoRead || filetoRead.isDirectory()){
      Serial.println("- failed to open file for reading");
      return;
    }
    // Serial.println(filetoRead.size());  
    // if(LITTLEFS.exists("/sensorData.txt"){
    // Serial.print("sensorData exists, size : "); 
    // }
    Serial.println("- read from file:");
    
    sensorIndex = 0;
    char buffer[6]; // 6
    int value;

    while(filetoRead.available()){
      int l = filetoRead.readBytesUntil('\n', buffer, sizeof(buffer)-1);
      buffer[l] = '\0';
      value = atoi(buffer);
      sensorData[sensorIndex] = value; // Populating the sensorData array
      delay(1); // delay(2)
      //Serial.print("value : ");Serial.println(value);
      sensorIndex++;
      if (sensorIndex % 100 == 0){
        displayMessage(6,sensorIndex); 
      }
      }
      filetoRead.close();
      displayMessage(7,0);
      
}

 void writeToFile() {
   Serial.println("Writing to file");
   //displayMessage(8,0); // "writing to file"

   // First erase previous file
   LITTLEFS.remove("/sensorData.txt"); 
   
   File fileToAppend = LITTLEFS.open("/sensorData.txt", "a");       // open file
      
      // for ( int i = 0 ; i < arrayLength; i++){ // Change this back to 65535  
      for ( int i = 0 ; i < myArrayLength; i++){ // Change this back to 65535  

          fileToAppend.println(sensorData[i]);
          //fileToAppend.println("127");
          delay(1);
          Serial.print("Writing, ");Serial.print("sensorData[");Serial.print(i);Serial.print("] : ");Serial.println(sensorData[i]);
          //fileToAppend.println(i); // This would write the line number
          //fileToAppend.print(','); 
          if(i % 500 == 0){
          displayMessage(8,i); // "writing to file"  
          }
      }   
      fileToAppend.close(); 
 }
