

///// LITTLEFS ///

void littleFSSetup(){
  
//  if(!LITTLEFS.begin(FORMAT_LITTLEFS_IF_FAILED)){
//        Serial.println("LITTLEFS Mount Failed");
//        return;
//    }

  if (LITTLEFS.begin()){
    Serial.println(F("Inizializing FS done."));
  }else{
    Serial.println(F("fail."));
  }

  // LITTLEFS.format(); ///////////// Only do this once ///////////////////
    
   File file = LITTLEFS.open("/sensorData.txt", "w");
  if(!file){
       Serial.println("- failed to open file for writing");
       return;
   }
 
if(file){
    Serial.println("Write file content!");
    file.print("Here the test text!!");
    file.close();
    }else{
    Serial.println("Problem on create file!");
  }

}

void readArrayFromFile(){ // Open file, save it into the array and start going through the array
    displayMessage(6); 

    File filetoRead = LITTLEFS.open(F("/sensorData.txt"), "r");
    if(!filetoRead || filetoRead.isDirectory()){
      Serial.println("- failed to open file for reading");
      return;
    }
    Serial.println(filetoRead.size());
//    
//    if(LITTLEFS.exists("/sensorData.txt"){
//      Serial.print("sensorData exists, size : "); 
//      }
    Serial.println("- read from file:");
      
//     int count = 0;
//      while(filetoRead.available()){
//        Serial.write(filetoRead.read());
//        int grr = atoi(filetoRead.read()); // - '48';;
//        sensorData[count] = sensorData[grr];
//        count++;
//        }
//        filetoRead.close();
//      
    sensorIndex = 0;
    char buffer[6]; // 6
    String stringOne = "";    
    int value;
    Serial.println("Getting here ! ");

    while(filetoRead.available()){
      int l = filetoRead.readBytesUntil('\n', buffer, sizeof(buffer)-1);
      buffer[l] = '\0';
      value = atoi(buffer);
      sensorData[sensorIndex] = value; // Populating the sensorData array
      Serial.print("sensorData[");Serial.print(sensorIndex);Serial.print("] : ");Serial.println(sensorData[sensorIndex]);
      //stringOne = String(buffer); // converting a constant char buffer into a String
      //value = stringOne.toInt();

//          if (value >= 0){
//            //Serial.print("value : ");
//            //Serial.println(value);
//          }
         
    sensorIndex++;
    if ( sensorIndex > arrayLength ) {
      break;    
    }
 }
            
    filetoRead.close();
    displayMessage(7);
 }

 void writeToFile() {
   Serial.println("Writing to file");
   displayMessage(8); // "writing to file"
   File fileToAppend = LITTLEFS.open("/sensorData.txt", "a");       // open file
      
      for ( int i = 0 ; i < arrayLength; i++){ // Change this back to 65535  
          fileToAppend.println(sensorData[i]);
          delay(5);
          Serial.print("Writing, ");Serial.print("sensorData[");Serial.print(i);Serial.print("] : ");Serial.println(sensorData[i]);
          fileToAppend.println(i);
          fileToAppend.print(',');   
      }   
      fileToAppend.close(); 
 }
