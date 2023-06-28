#include "BluetoothSerial.h"


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

int trigPin = 5;
int echoPin = 18;
int duration;
int distance;
int isReady=0;
int halt=0;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Valentine_Cup_1"); // Set the name of the Bluetooth device
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  int stopSignal = Serial.read();
  if(stopSignal=='1') {
    halt=1;
    isReady=0;
  }
  else if(stopSignal=='2') {
    halt=0;
    isReady=0;
  }
  else {
    if(halt==0) {
      if(isReady==0) {
        int readByte=SerialBT.read();
        Serial.print("Read byte : ");
        Serial.print((char)readByte);
        Serial.print(" ");
        Serial.println(readByte);    
        if(readByte=='+') {
          isReady=1;
        }
        else if(readByte=='-') {
          isReady=0;
          halt=1;
        }
        else {
          Serial.println("Read byte is not +");
        }
      }
      else {

        Serial.print("Distance is : ");
        Serial.println(distance);
        if(distance < 10) {
          SerialBT.println("DOWN");
        }
        else {
          SerialBT.println("UP");
        }
        int readByte=SerialBT.read();
        if(readByte=='-') {
          isReady=0;
          halt=1;          
        }    
        if(SerialBT.connected()) {
        } 
        else {
          SerialBT.println("SerialBT not available");
          isReady=0;
          halt=0;
        }   
      }
    }
    else {
      Serial.println("Halted");
    }
  }
  delay(100);
}