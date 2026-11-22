void setup() {
  // put your setup code here
  pinMode(PC13, OUTPUT);
}

void loop() {
  // put your main code here
  digitalWrite(PC13, HIGH);
  delay(1000);
  digitalWrite(PC13, LOW);
  delay(1000);
}
