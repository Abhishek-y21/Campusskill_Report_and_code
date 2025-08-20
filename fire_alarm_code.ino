// Automatic Fire Alarm and Extinguisher System
// Components: Arduino UNO, IR Flame Sensor, L298N, DC Pump, Buzzer

const int IR_FLAME_PIN = 2;   // IR sensor OUT
const int BUZZER_PIN   = 3;   // Buzzer
const int L298N_ENA    = 5;   // ENA pin (PWM)
const int L298N_IN1    = 8;
const int L298N_IN2    = 9;

const bool FLAME_ACTIVE_LOW = true;  
const int PUMP_SPEED = 255;   // 0-255
const int PUMP_TIME  = 5000;  // ms

void setup() {
  pinMode(IR_FLAME_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(L298N_ENA, OUTPUT);
  pinMode(L298N_IN1, OUTPUT);
  pinMode(L298N_IN2, OUTPUT);

  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
  bool fireDetected = (FLAME_ACTIVE_LOW) ? (digitalRead(IR_FLAME_PIN) == LOW)
                                         : (digitalRead(IR_FLAME_PIN) == HIGH);

  if (fireDetected) {
    digitalWrite(BUZZER_PIN, HIGH);  // buzzer ON
    digitalWrite(L298N_IN1, HIGH);
    digitalWrite(L298N_IN2, LOW);
    analogWrite(L298N_ENA, PUMP_SPEED); // pump ON
    delay(PUMP_TIME);

    // Stop pump after spray
    analogWrite(L298N_ENA, 0);
    digitalWrite(BUZZER_PIN, LOW);
  } else {
    analogWrite(L298N_ENA, 0);  // pump OFF
    digitalWrite(BUZZER_PIN, LOW);
  }
}