int state = 8;
int lastState = -1; // Uložíme si poslední stav
float mvInput = 4.9;
float mvOutput = 19.6;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);

  analogWrite(7, 255);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    int receivedValue = Serial.parseInt();
    if (receivedValue >= 1 && receivedValue <= 8) {
      state = receivedValue;
    }
  }

  if (state != lastState) { // Kontrola, zda se stav změnil
    switch (state) {
      case 1: turnAllOn(); break;
      case 2: turnRedOn(); break;
      case 3: turnRedOff(); break;
      case 4: turnGreenOn(); break;
      case 5: turnGreenOff(); break;
      case 6: turnBlueOn(); break;
      case 7: turnBlueOff(); break;
      case 8: turnAllOff(); break;
    }
    lastState = state; // Aktualizace posledního stavu
  }
  readVoltage();
  delay(200);
}

void turnAllOn(){
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
  delay(100);
}

void turnGreenOn(){
  digitalWrite(13, HIGH);
  delay(100);
}

void turnGreenOff(){
  digitalWrite(13, LOW);
  delay(100);
}

void turnBlueOn(){
  digitalWrite(12, HIGH);
  delay(100);
}

void turnBlueOff(){
  digitalWrite(12, LOW);
  delay(100);
}

void turnRedOn(){
  digitalWrite(11, HIGH);
  delay(100);
}

void turnRedOff(){
  digitalWrite(11, LOW);
  delay(100);
}

/*
void turn1On(){
  digitalWrite(10, HIGH);
  delay(100);
}

void turn1Off(){
  digitalWrite(10, LOW);
  delay(100);
}
*/

void turnAllOff(){
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  delay(100);
}

void readVoltage() {
  static unsigned long lastChrono;
  unsigned long currentChrono = millis();
  if (currentChrono - lastChrono >= 2) { // ~100Hz
    //Serial.print("napětí:");
    Serial.println(analogRead(A0)*mvInput);
    //Serial.println("");
    //Serial.print(zmpt101b.getRmsVoltage());
    //Serial.print(",");
    //Serial.print("proud:");
    //Serial.print(ina219.getCurrent_mA()/1000);
    //Serial.println("");
    lastChrono = currentChrono;
  }
}