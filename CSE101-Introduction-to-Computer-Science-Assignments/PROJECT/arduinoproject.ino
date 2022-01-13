
int pirPin=8;
int hareket;
int i;
void setup() {
  pinMode(8,INPUT);
  pinMode(4,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(10,OUTPUT);
  

}

void loop() {
    digitalWrite(6,HIGH);
    
    hareket=digitalRead(8);
    while(hareket== HIGH) {
      digitalWrite(6,LOW);
      digitalWrite(4,HIGH);
      digitalWrite(10,HIGH);
      delay(1000);
      hareket=digitalRead(8);
    }
  
    
      digitalWrite(6,HIGH);
      digitalWrite(4,LOW);
      digitalWrite(10,LOW);
      
    
  
  

}
