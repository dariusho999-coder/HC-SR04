#define TRIG  A4    // using analog pin as digital pin
#define ECHO  A5

long duration;
float distance;

void setup() {
  //Serial.begin(9600);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  Serial.println("Ultrasonic Ready");
}

void loop() {

  // ===== TRIGGER PULSE =====
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // ===== READ ECHO =====
  duration = pulseIn(ECHO, HIGH);

  // convert to cm
  distance = duration * 0.0343 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // ===== OBSTACLE DETECTED =====
  if (distance > 0 && distance < 30) {
    reverseRobot();            // reverse for a moment
  } 
  else {
    moveForward();             // normal forward
  }

  delay(80);
}

// =========================
// MOTOR FUNCTIONS
// =========================
void moveForward() {
  // Adjust these to your motor pins
  digitalWrite(1, HIGH); digitalWrite(2, LOW);  analogWrite(3, 80);
  digitalWrite(12, HIGH); digitalWrite(13, LOW); analogWrite(11, 80);
}

void reverseRobot() {
  // Reverse both motors
  digitalWrite(1, LOW); digitalWrite(2, HIGH);  analogWrite(3, 160);
  digitalWrite(12, LOW); digitalWrite(13, HIGH); analogWrite(11, 150);

  delay(500);  // reverse for half second

  stopMotors();
}

void stopMotors() {
  analogWrite(3, 0);
  analogWrite(11, 0);

  digitalWrite(1, LOW);
  digitalWrite(2, LOW);

  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
}
