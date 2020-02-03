
// Basic Bluetooth sketch HC-05_02
// Connect the HC-05 module and communicate using the serial monitor
//
// The HC-05 defaults to commincation mode when first powered on.
// The default baud rate for communication mode is 9600
//
 
#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3); // RX | TX
// Connect the HC-05 TX to Arduino pin 2 RX. 
// Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.
// 
 
char c = ' ';
int SensorPin=A0;
float reading=0;


void setup() 
{
    Serial.begin(9600);
    Serial.println("Arduino is ready");
 
    // HC-05 default serial speed for commincation mode is 9600
    BTserial.begin(9600); 
    BTserial.write("Connected");
    //LED Pin Mode
    pinMode(A0,INPUT);
    pinMode(13,OUTPUT);
}

 
void blueTooth(){
  // Keep reading from HC-05 and send to Arduino Serial Monitor
    if (BTserial.available())
    {  
        c = BTserial.read();
        Serial.write(c);
    }
 
    // Keep reading from Arduino Serial Monitor and send to HC-05
    if (Serial.available())
    {
        c =  Serial.read();
        BTserial.write(c);  
    }
  
}

void LED(){
    reading = analogRead(A0);
//    reading = map(/reading,0,1023,0,5);
    Serial.println(reading);
    if(reading<220 && reading > 145)
   {
    Serial.println("Danger");
    
    Serial.println("Change the Saline bottle");
      digitalWrite(13,1);
      BTserial.write("D");
     }
    else if(reading<668 && reading > 377) 
   {
      Serial.println("Safe");
      digitalWrite(13,0);
      BTserial.write("S");
     }
     else{
      Serial.println("Miss Alignment");
      BTserial.write("M");
      }
  
     //delay(1000);
}

void loop()
{
    blueTooth();
    LED();
    delay(1000);
}
