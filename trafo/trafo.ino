#include <ZMPT101B.h>
#include <Adafruit_INA219.h> // K použití knihovny senzoru je třeba ji zahrnout

// definování adresy senzoru
#define ADDR 0x40
// inicializace senzoru s nastavenou adresou z knihovny
Adafruit_INA219 ina219_5(0x40);
Adafruit_INA219 ina219_12(0x41); // I2C adresu senzoru s přepájenou ploškou jsme fyzicky změnili na 0x41, takže je potřeba přizpůsobit kód

int state = 1;
int lastState = -1; // Uložíme si poslední stav

void setup() {
  Serial.begin(19200);
  ina219_5.begin();
  ina219_12.begin();

  // Příklad použití spínacího relé
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);

  digitalWrite(13, HIGH); // HIGH - zapnuto, poloha switche je spojena s NO
  digitalWrite(12, HIGH);
  digitalWrite(11, LOW); // LOW - vypnuto, poloha switche je spojena s NC
  digitalWrite(10, LOW);

  ina219_5.setCalibration_16V_400mA(); // nastavili jsme nejnižší citlivost čidla
  ina219_12.setCalibration_16V_400mA();
}

void loop() {
  if (Serial.available() > 0) {
    int receivedValue = Serial.parseInt();
    if (receivedValue >= 1 && receivedValue <= 7) {
      state = receivedValue;
      Serial.print("Received state: ");
      Serial.println(state); // Výpis přijatého stavu
    }
  }

  if (state != lastState) { // Kontrola, zda se stav změnil
    Serial.print("Changing state to: ");
    Serial.println(state); // Výpis změny stavu
    switch (state) {
      case 1: set200z(); break;
      case 2: set400z(); break;
      case 3: set600z(); break;
      case 4: set0r(); break;
      case 5: set1r(); break;
      case 6: set2r(); break;
      case 7: set3r(); break;
    }
    lastState = state; // Aktualizace posledního stavu
  }
  
  readVoltage();
  delay(5); // Zpoždění 5 ms pro rychlé měření
}

void set200z() {
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
}

void set400z() {
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
}

void set600z() {
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
}

void set0r() {
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
}

void set1r() {
  digitalWrite(11, HIGH);
  digitalWrite(10, LOW);
}

void set2r() {
  digitalWrite(11, LOW);
  digitalWrite(10, HIGH);
}

void set3r() {
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
}

void readVoltage() {
  static unsigned long lastChrono;
  unsigned long currentChrono = millis();
  if (currentChrono - lastChrono >= 1) { // ~100Hz
    Serial.print("Uin:");
    Serial.print((230 * (analogRead(A0) - 512)) / 512); // Hodnoty z modulu lze získat pouze z formátu 0-5V, takže pro převod na voltu je potřeba kódově ošetřit
    Serial.print(",");
    Serial.print("Uout:");
    Serial.print((230 * (analogRead(A1) - 512)) / 512);
    Serial.print(",");
    Serial.print("proud1:");
    Serial.print(ina219_5.getCurrent_mA()); // Čtení senzoru v mA
    Serial.print(",");
    Serial.print("proud2:");
    Serial.print(ina219_12.getCurrent_mA());
    Serial.println("");
    lastChrono = currentChrono;
  }
}