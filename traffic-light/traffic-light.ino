
int greenPin  = 8;
int yellowPin = 9;
int redPin    = 10;



void setup() {
  pinMode(greenPin,OUTPUT);
  pinMode(yellowPin,OUTPUT);  
  pinMode(redPin,OUTPUT);
}

void loop() {
  digitalWrite(yellowPin,LOW);
  digitalWrite(greenPin,HIGH);
  delay(5*1000);
  digitalWrite(yellowPin,HIGH);
  delay(2*1000);
  digitalWrite(greenPin,LOW);
  digitalWrite(yellowPin,LOW);
  digitalWrite(redPin,HIGH);
  delay(5*1000);
  digitalWrite(yellowPin,HIGH);
  digitalWrite(redPin,LOW);
  delay(2*1000);

}
