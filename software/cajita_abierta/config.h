// #define Accelerometer true
// #define PressureSensor true
#define Display true
// #define displayRotate true // Enable for the accelerometer version of the cajita
#define useButton true
#define useAnalogSensors true
#ifndef LED_BUILTIN
#define LED_BUILTIN 2 // For the boards that do not have a LED_BUILTIN
#endif

void sendSensorsData(String someValue);

void listFile(String someOtherValue);
void writeFile(String myFile, String myMessage);
