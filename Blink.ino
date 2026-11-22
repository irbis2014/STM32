void setup() {
  // put your setup code here
  pinMode(PC13, OUTPUT);
  pinMode(PB1,OUTPUT);
}

void loop() {
  // put your main code here
  digitalWrite(PC13, HIGH);
  digitalWrite(PB1, HIGH);
  delay(1000);
  digitalWrite(PC13, LOW);
  digitalWrite(PB1, LOW);
  delay(1000);
}
