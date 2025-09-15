/*
  Mock Anti-Sleep Data Generator (TCRT5000 + MPU6050)
  - Blink duration (ms) from TCRT5000 (simulated)
  - Head tilt angles from MPU6050 (simulated)
  - CSV: millis,blinkDuration,ax,ay,az,pitch,roll,mode
*/

const uint32_t BAUD = 115200;
const uint16_t SAMPLE_MS = 50; // 20 Hz

// Mode state
enum Mode { ALERT, DROWSY };
Mode mode = ALERT;

// Blink simulation
unsigned long blinkEndMs = 0;
unsigned long blinkDuration = 0;
unsigned long nextBlinkMs = 0;

// Thresholds
const float TILT_THRESHOLD = 25.0; // degrees
const int BLINK_DROWSY_MS = 200;    // threshold for drowsy blink

// === Helpers ===
long randBetween(long a, long b) { return a + random(b - a + 1); }

void scheduleNextBlink(unsigned long now) {
  unsigned long interval = randBetween(1000, 6000); // random interval
  nextBlinkMs = now + interval;
}

void setup() {
  Serial.begin(BAUD);
  randomSeed(analogRead(A3));
  scheduleNextBlink(millis());

  Serial.println("timestamp,blinkDuration,ax,ay,az,pitch,roll,mode");
}

void loop() {
  static unsigned long lastSample = 0;
  unsigned long now = millis();
  if (now - lastSample < SAMPLE_MS) return;
  lastSample = now;

  // === Blink Simulation (TCRT5000) ===
  if (now >= nextBlinkMs && blinkEndMs == 0) {
    // Generate random blink duration (mix of alert and drowsy)
    blinkDuration = randBetween(80, 400); 
    blinkEndMs = now + blinkDuration;
  }
  if (blinkEndMs > 0 && now >= blinkEndMs) {
    blinkEndMs = 0;
    scheduleNextBlink(now);
  }

  // === Accelerometer (MPU6050) ===
  float axf = randBetween(-2000, 2000);
  float ayf = randBetween(-2000, 2000);
  float azf = 16384 + randBetween(-500, 500);

  // Convert to angles
  float pitch = atan2(axf, sqrt(ayf * ayf + azf * azf)) * 180.0 / PI;
  float roll  = atan2(ayf, sqrt(axf * axf + azf * azf)) * 180.0 / PI;

  // === Mode decision (both tilt and blink) ===
  bool tiltDrowsy = (abs(pitch) > TILT_THRESHOLD || abs(roll) > TILT_THRESHOLD);
  bool blinkDrowsy = (blinkDuration >= BLINK_DROWSY_MS);

  if (tiltDrowsy || blinkDrowsy) {
    mode = DROWSY;
  } else {
    mode = ALERT;
  }

  // === Emit CSV ===
  Serial.print(now); Serial.print(',');
  Serial.print(blinkDuration); Serial.print(',');
  Serial.print((int16_t)axf); Serial.print(',');
  Serial.print((int16_t)ayf); Serial.print(',');
  Serial.print((int16_t)azf); Serial.print(',');
  Serial.print(pitch, 1); Serial.print(',');
  Serial.print(roll, 1); Serial.print(',');
  Serial.println(mode == ALERT ? "alert" : "drowsy");
}
