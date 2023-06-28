
int trigPin=5;
int echoPin = 18;
int duration;
int distance;

//hc-sr04
//vcc - > vin
//trig -> d5
//echo -> d18
//gnd -> gnd

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration=pulseIn(echoPin,HIGH);
  //distance=duration*0.034/2;
  distance=duration/58.2;
  Serial.println(distance);
  delay(100);
}
