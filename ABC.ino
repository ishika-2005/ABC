#include <Servo.h>

Servo gateServo1;
Servo gateServo2;

// Define pins
const int irSensorEntry = 2;
const int irSensorExit = 3;
const int redLED = 11;
const int greenLED = 10;
const int buzzer = 12;
const int Station_signal_green = 4;
const int Station_signal_red = 5;
const int Station_signal_buzzer = 6;

const int gateOpenPos = 0;
const int gateClosedPos = 90;

bool trainDetected = false;
bool automaticMode = true;
bool redBlinking = false;

unsigned long previousMillis = 0;
const long blinkInterval = 500; // Interval for blinking in milliseconds
bool ledState = LOW;

void setup() {
  gateServo1.attach(9);
  gateServo2.attach(8);
  gateServo1.write(gateOpenPos);
  gateServo2.write(gateOpenPos);

  pinMode(irSensorEntry, INPUT);
  pinMode(irSensorExit, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(Station_signal_green, OUTPUT);
  pinMode(Station_signal_red, OUTPUT);
  pinMode(Station_signal_buzzer, OUTPUT);

  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, LOW);
  digitalWrite(buzzer, LOW);
  digitalWrite(Station_signal_buzzer, LOW);

  Serial.begin(9600);
  Serial.println("System Ready");
}

void loop() {
  checkSerialCommand();
  

  if (automaticMode) {
    int entrySensorState = digitalRead(irSensorEntry);
    int exitSensorState = digitalRead(irSensorExit);

    if (entrySensorState == LOW && !trainDetected) {
      trainDetected = true;
      Serial.println("TRAIN_DETECTED");
      closeGates();
    }

    if (exitSensorState == LOW && trainDetected) {
      trainDetected = false;
      Serial.println("TRAIN_CLEARED");
      openGates();
    }
  }

  // Handle red light blinking
  if (redBlinking) {
    blinkRedNonBlocking();
  }
}

void closeGates() {
  Serial.println("Closing gates...");
  gateServo1.write(gateClosedPos);
  gateServo2.write(gateClosedPos);
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, HIGH);
  soundBuzzer();
  delay(1000);
  Serial.println("GATES_CLOSED");

  // Start blinking red light
  redBlinking = true;
}

void openGates() {
  Serial.println("Opening gates...");
  gateServo1.write(gateOpenPos);
  gateServo2.write(gateOpenPos);
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, HIGH);
  soundBuzzer();
  delay(1000);
  Serial.println("GATES_OPENED");

  // Stop blinking red light
  redBlinking = false;
  digitalWrite(Station_signal_red, LOW);
}

void checkSerialCommand() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "CLOSE") {
      automaticMode = false;
      closeGates();
      blinkRedTwice();
      Serial.println("MANUAL_CLOSE");
    } else if (command == "OPEN") {
      automaticMode = false;
      openGates();
      blinkGreenTwice();
      Serial.println("MANUAL_OPEN");
    } else if (command == "SUCCESS") {
      digitalWrite(Station_signal_green, HIGH);
      digitalWrite(Station_signal_red, LOW);
      digitalWrite(Station_signal_buzzer, LOW);
      Serial.println("SUCCESS_COMMAND_RECEIVED");
    } else if (command == "FAILURE") {
      closeGates();
      Serial.println("FAILURE_COMMAND_RECEIVED");
      automaticMode = true; // Override to automatic mode
      Serial.println("SWITCHED_TO_AUTOMATIC_MODE");
    } else {
      Serial.println("INVALID_COMMAND");
    }
  }
}

void soundBuzzer() {
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
}

void blinkGreenTwice() {
  for (int i = 0; i < 2; i++) {
    digitalWrite(Station_signal_green, HIGH);
    delay(300);
    digitalWrite(Station_signal_green, LOW);
    delay(300);
  }
}

void blinkRedTwice() {
  for (int i = 0; i < 2; i++) {
    digitalWrite(Station_signal_red, HIGH);
    delay(300);
    digitalWrite(Station_signal_red, LOW);
    delay(300);
  }
}

void blinkRedNonBlocking() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= blinkInterval) {
    previousMillis = currentMillis;
    ledState = !ledState;
    digitalWrite(Station_signal_red, ledState);
  }
}