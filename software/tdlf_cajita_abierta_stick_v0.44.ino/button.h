#if defined useButton
//#include <ezButton.h>

//// Button to start config
bool configureCajita = false; // A button press will start it
bool firstimer = true; // needed because of a 'long presse' detected at bootup :/
int buttonCounter = 0;

#define SHORT_PRESS_TIME 1000 // 1000 milliseconds
#define LONG_PRESS_TIME  1000 // 1000 milliseconds

bool isPressing = false;
bool isLongDetected = false;

int BUTTON_PIN = 0;

// Variables will change:
int lastState = LOW;  // the previous state from the input pin
int currentState;     // the current reading from the input pin
unsigned long pressedTime  = 0;
unsigned long releasedTime = 0;

void buttonSetup(){
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void getButtonState(){
  // read the state of the switch/button:
  currentState = digitalRead(BUTTON_PIN);

  if(lastState == HIGH && currentState == LOW)        // button is pressed
    pressedTime = millis();
  else if(lastState == LOW && currentState == HIGH) { // button is released
    releasedTime = millis();
    long pressDuration = releasedTime - pressedTime;
    if( pressDuration < SHORT_PRESS_TIME ){
      buttonCounter=buttonCounter+4; // increase by one
      if (buttonCounter > 43 ){ // Find out how many sensors we are checking...
        buttonCounter = 0;
      }
      Serial.println("A short press is detected");
      Serial.print("buttonCounter : "); Serial.println(buttonCounter);
    }

    if( pressDuration > LONG_PRESS_TIME ){
      if (firstimer){ // do nothing
       firstimer = false;
      }
      else{
      Serial.println("A long press is detected");
      portalStart = "true"; 
      }
    }
  }

  // save the the last state
  lastState = currentState;
}
#endif
