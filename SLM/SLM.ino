
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
float photoVoltS1,photoVoltS2;
const int GREEN = 0, YELLOW = 1, RED = 2, NOCOLOR = 3;
bool trigger = false; 

void setup() 
{
    // HC-05 default serial speed for commincation mode is 9600
    BTserial.begin(9600); 
    Serial.println("BlueTooth is ready");
    pinMode(A0,INPUT);//Sensor 1
    pinMode(A1,INPUT);//Sensor 2
    pinMode(13,OUTPUT);//yellow
    pinMode(12,OUTPUT);//Red
    pinMode(11,OUTPUT);//green
    pinMode(10,OUTPUT);//relay
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

void activateLED(int color){
    switch(color){
        case 0://GREEN
          digitalWrite(13,LOW);
          digitalWrite(12,LOW);
          digitalWrite(11,HIGH);
          break;
        case 1://YELLOW
          digitalWrite(13,HIGH);
          digitalWrite(12,LOW);
          digitalWrite(11,LOW);
          break;
        case 2://RED
          digitalWrite(13,LOW);
          digitalWrite(12,HIGH);
          digitalWrite(11,LOW);
          break;
        case 3://NOCOLOR
          digitalWrite(13,LOW);
          digitalWrite(12,LOW);
          digitalWrite(11,LOW);
          break;
        default:
          digitalWrite(13,LOW);
          digitalWrite(12,LOW);
          digitalWrite(11,LOW);
          break;
      }
  
  }

// void LED2(){
  
  
//   }

void LED(){
  reading = analogRead(A0);
  photoVoltS1= reading * (5.0 / 1023.0);
  
  reading = analogRead(A1);
  photoVoltS2 = reading * (5.0 / 1023.0);
  
  Serial.print("photoout1= ");
  Serial.println(photoVoltS1);
  Serial.print("photoout2= ");
  Serial.println(photoVoltS2);
  
  if(photoVoltS1<5 && photoVoltS1>1.0){
     Serial.println("Safe");
     activateLED(GREEN);
     BTserial.write("G");
   }else if(photoVoltS1<1 && photoVoltS1>0){
      Serial.println("Call the nurse");
      activateLED(YELLOW);
      BTserial.write("Y");
      trigger = true;
    }

    while(trigger){
      if(photoVoltS2<1 && photoVoltS2>0){
        Serial.println("Danger");
        activateLED(RED);
        digitalWrite(9,HIGH);//Buzzer
        digitalWrite(10,HIGH);//RELAY
        delay(5000);
        digitalWrite(9,LOW);
        digitalWrite(10,LOW);
        while(1){
          BTserial.write("R");
        };
      }else {
          trigger = false;
        }
    }
  delay(1000);
}

void loop()
{
 
    blueTooth();
    LED();
    delay(1000);
}
