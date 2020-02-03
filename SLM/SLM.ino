
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
int secondled=A1;
int photoout=0;
float readvolt,photvolt;

void setup() 
{
    // HC-05 default serial speed for commincation mode is 9600
    BTserial.begin(9600); 
    Serial.println("BlueTooth is ready");
    pinMode(A0,INPUT);
    pinMode(A1,INPUT);
    pinMode(13,OUTPUT);//yellow
    pinMode(12,OUTPUT);//Red
    pinMode(11,OUTPUT);//green
    //pinMode(10,OUTPUT);//relay
    pinMode(9,OUTPUT);//Buzzer
    Serial.begin(9600);
    Serial.println("Arduino is ready");

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
  reading=analogRead(A0);
  readvolt= reading * (5.0 / 1023.0);
  
  photoout=analogRead(A1);
  photvolt= photoout * (5.0 / 1023.0);
  
  Serial.print("photoout1= ");
  Serial.println(readvolt);
  Serial.print("photoout2= ");
  Serial.println(photvolt);
  
  if(readvolt<5 && readvolt>1.0){
     Serial.println("Safe");
     digitalWrite(13,LOW);
     digitalWrite(12,LOW);
     digitalWrite(11,1);
     BTserial.write("G");
   }
  else{
    digitalWrite(11,0);
  }
  
if(readvolt<1 && readvolt>0)
{
    Serial.println("Call the nurse");
    digitalWrite(13,1);
    BTserial.write("Y");
 }
  else
  {
    
    digitalWrite(13,0);
    }
if(photvolt<1 && photvolt>0)
 {
    Serial.println("Danger");
    
    digitalWrite(11,LOW);
    digitalWrite(13,LOW);
    digitalWrite(12,HIGH);
    digitalWrite(9,HIGH);//Buzzer
    digitalWrite(10,HIGH);
    delay(5000);
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    BTserial.write("R");
    while(1);
   }
 else
 {
   digitalWrite(12,0);
   digitalWrite(10,LOW);
   }
 
    delay(1000);
}

void loop()
{
 
    blueTooth();
    LED();
    delay(1000);
}
