/*
AUTHOR: Hazim Bitar (techbitar)
DATE: Aug 29, 2013
LICENSE: Public domain (use at your own risk)
CONTACT: techbitar at gmail dot com (techbitar.com)
*/
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Servo.h>
SoftwareSerial BTSerial(6, 7); // RX | TX

Servo leftServo, rightServo;
int leftValue = -1, rightValue = -1;

void setup()
{
 pinMode(9, OUTPUT); // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
 digitalWrite(9, HIGH);
 Serial.begin(9600);
 Serial.println("BT is ready!");
 BTSerial.begin(38400); // HC-05 default speed in AT command more
}
void loop()
{
  if (Serial.available()) {
    char val = Serial.read();
    BTSerial.print(val);
 }
 // Keep reading from HC-05 and send to Arduino Serial Monitor
 if (BTSerial.available()){
    char c = BTSerial.read();
    if(c == 'U'){
       leftValue = 1700;
       rightValue = 1300;
    }
    if(c == 'D'){
       leftValue = 1300;
       rightValue = 1700;
    }
    if(c == 'S'){
       leftValue = -1;
       rightValue = -1;
    }
    if(c == 'L'){
       leftValue = 1300;
       rightValue = -1;
    }
    if(c == 'R'){
      leftValue = 1700;
      rightValue = -1;
    }
    Serial.print(c);
 }
 if(leftValue == -1){
    leftServo.detach();
 }else{
    leftServo.attach(12);
    leftServo.writeMicroseconds(leftValue);
 }
 if(rightValue == -1){
    rightServo.detach();
 }else{
    rightServo.attach(13);
    rightServo.writeMicroseconds(rightValue);
 }
 
}
