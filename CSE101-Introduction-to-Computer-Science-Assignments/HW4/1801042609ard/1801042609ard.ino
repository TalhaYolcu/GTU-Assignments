
int inc;
int i=0;
int s=0;

const int buttonPin = 2;  // NUMBER OF BUTTON PIN  THAT ATTACHED TO THE ARDUINO   
const int ledPin =  13;      // NUMBER OF THE LED THAT ATTACHED TO THE ARDUINO

int buttonState = 0;   // DEFINING BUTTON STATE
int a=0;              // NUMBER OF PRESSING BUTTON


void setup() {
  Serial.begin(9600);     // START THE SERIAL COMMUNICATION
  pinMode(2,INPUT);          // REPRESENT TO THE ARDUINO THERE IS A BUTTON ON 2. PIN
  pinMode(ledPin,OUTPUT);    // REPRESENT TO THE ARDUINO THERE IS A LED ON 13.PIN
  
 

}

void loop() {
 
  if(Serial.available()) { 
  inc=Serial.read();
  
  switch(inc) {
    case 'x' : 
      digitalWrite(ledPin,HIGH);  // TURN THE LED ON
      
      break;
    case 'y' :
      digitalWrite(ledPin,LOW);   // TURN THE LED OFF
      
      break;
    case 'z':
        digitalWrite(ledPin,LOW);   // FLASH THE ARDUINO 3 TIMES
        delay(500);
        for(i=0;i<3;i++){
          digitalWrite(ledPin,HIGH);
          delay(1000);
          digitalWrite(ledPin,LOW);
          delay(1000);
        }
        break; 
      
    case 'w':   // NUMBER OF PRESSING BUTTON
          while(1) {
          buttonState = digitalRead(buttonPin);
    
          while (buttonState == HIGH) {
            
            digitalWrite(ledPin, HIGH);
            
            delay(500);
            
            a++;
            Serial.print(a);
            Serial.print("\n");
            
            break;
          } 
          digitalWrite(ledPin, LOW);
    
         }
      
         break;
      
     default:   // COMPUTING SQUARE OF NUMBER THAT SENT TO THE ARDUINO 
        inc=inc-99;
        s=sq(inc);
      
        Serial.print(s);
        Serial.print("\n");
        s=0;
        inc=0;
   } // END OF SWITCH
 }// END OF SERIAL AVALILABLE

} // END OF LOOP
