int state = 8;
int lastState = -1; // Uložíme si poslední stav
float mvInput = 4.9;

void setup() {
  pinMode(11, OUTPUT); // Červená
  pinMode(12, OUTPUT); // Modrá
  pinMode(13, OUTPUT); // Zelená
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  Serial.begin(9600);

  analogWrite(11, 0); // Červená vypnuta
  analogWrite(12, 0); // Modrá vypnuta
  analogWrite(13, 0); // Zelená vypnuta
}

void loop() {
  if (Serial.available() > 0) {
    String receivedValue = Serial.readStringUntil('\n');
    if (receivedValue.startsWith("r")) {
      int redValue = receivedValue.substring(1).toInt();
      setRed(redValue);
    } else if (receivedValue.startsWith("g")) {
      int greenValue = receivedValue.substring(1).toInt();
      setGreen(greenValue);
    } else if (receivedValue.startsWith("b")) {
      int blueValue = receivedValue.substring(1).toInt();
      setBlue(blueValue);
    }
  }
  
  readVoltage();
  delay(200);
}

void setRed(int value) {
  analogWrite(11, value); // Nastavení červené barvy
  delay(100);
}

void setGreen(int value) {
  analogWrite(13, value); // Nastavení zelené barvy
  delay(100);
}

void setBlue(int value) {
  analogWrite(12, value); // Nastavení modré barvy
  delay(100);
}

void readVoltage() {
    float voltageA0 = analogRead(A0) * mvInput;
    float voltageA1 = analogRead(A1) * mvInput;
    float voltageA2 = analogRead(A2) * mvInput;
    Serial.print(voltageA0);
    Serial.print(",");
    Serial.print(voltageA1);
    Serial.print(",");
    Serial.println(voltageA2);
}