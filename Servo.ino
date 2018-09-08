Servo servo;

void setup_Servo() {
  servo.attach(PIN_Servo); //D4
  servo.write(0);
}

void loop_Servo() {
  servo.write(180);
  delay(1000);
  servo.write(10);
  delay(1000);
}
