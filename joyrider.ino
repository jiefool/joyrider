// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.
//https://learn.adafruit.com/multi-tasking-the-arduino-part-1/overview


#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int input = 0;
int init_prog = 0;
int servoState = 0;
int servoPos = 90;
long previousMillis = 0;
int increment = 1;
const int buttonPin = 3;
const int motorPin = 4;
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;
 
void setup() 
{ 
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object   
  pinMode(buttonPin, INPUT);
  pinMode(motorPin, OUTPUT);
} 
 
void loop() 
{   
   if (init_prog == 0){ 
        init_prog = 1;
        for(int i=servoPos;i<115;i++){
          servoPos = i;
          myservo.write(servoPos);
          delay(15);     
        }
    }

  
  buttonState = digitalRead(buttonPin);
  
   if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
       buttonPushCounter++;
       if (buttonPushCounter % 4 == 0){
         input = 2;
       }else if (buttonPushCounter % 5 == 0 ){
         input = 1;
       }
    } 
    else {
      // if the current state is LOW then the button
      // wend from on to off:
      Serial.println("off"); 
    }
  }
  
  
   if (input == 1){ 
       digitalWrite(motorPin, LOW);
       servoState = 0;
        for(int i=servoPos;i<115;i++){
          servoPos = i;
          myservo.write(servoPos);
          delay(15);     
        }
    }
    
   if (input == 2){
       
      if (servoState !=1){   
        servoState = 1;     
        for(int i=servoPos;i>5;i--){
          servoPos = i;
          myservo.write(servoPos);
          delay(15);  
        }    
      }else{   
         digitalWrite(motorPin, HIGH);    
         unsigned long currentMillis = millis();
         if((currentMillis - previousMillis) > 5)
          {
            previousMillis = millis();
            servoPos += increment;
            myservo.write(servoPos);           
            if ((servoPos >= 30) || (servoPos <= 0))
            {              
              increment = -increment;
            }
          }
      }
   }
   
   
  
  
  
} 
