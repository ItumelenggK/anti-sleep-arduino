#include <MPU6050.h>

// Pin definitions
#define IR_PIN 2         // IR sensor connected to digital pin 2
#define BUZZER_PIN 3     // Buzzer connected to digital pin 3
#define LED_PIN 4        // LED connected to digital pin 4

void setup() {
  pinMode(IR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  bool eyesClosed = digitalRead(IR_PIN) == LOW;

  if (eyesClosed) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Eyes closed! Wake up!");
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
    Serial.println("Eyes open. All good.");
  }

  delay(500); 
}
