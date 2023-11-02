const int pirSensorPin = 23;         // Pin connected to PIR motion sensor
const int ultrasonicTriggerPin = 33;  // Pin connected to Ultrasonic sensor trigger
const int ultrasonicEchoPin = 12;     // Pin connected to Ultrasonic sensor echo
const int switchRelayPin = 26;
int pirState = LOW; 
int val = 0;      // Pin connected to the switch relay

// Variables
bool isMotionDetected = false;
  // Flag to track motion detection

void setup() {
  // Initialize pins
  pinMode(pirSensorPin, INPUT);
  pinMode(ultrasonicTriggerPin, OUTPUT);
  pinMode(ultrasonicEchoPin, INPUT);
  pinMode(switchRelayPin, OUTPUT);
  digitalWrite(switchRelayPin, LOW);  // Turn off the switch initially
  // Other setup code for Ultrasonic sensor if needed
}

void loop() {
  // Check PIR motion sensor
    val = digitalRead(pirSensorPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(switchRelayPin, HIGH);  // turn LED ON
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    digitalWrite(switchRelayPin, LOW); // turn LED OFF
    if (pirState == HIGH) {
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
  // Check Ultrasonic sensor
  int distance = measureDistance();
  
  // Control switch based on motion and distance
  if (isMotionDetected || distance <= 100) {
    digitalWrite(switchRelayPin, LOW);  // Turn on the switch
  } else {
    digitalWrite(switchRelayPin, HIGH);   // Turn off the switch
  }
}

int measureDistance() {
  // Send a pulse to the Ultrasonic sensor
  digitalWrite(ultrasonicTriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasonicTriggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonicTriggerPin, LOW);

  // Measure the duration of the pulse
  long duration = pulseIn(ultrasonicEchoPin, HIGH);

  // Calculate the distance based on the speed of sound
  // (343 m/s or 0.0343 cm/µs)
  int distance = duration * 0.0343 / 2;

  return distance;
}