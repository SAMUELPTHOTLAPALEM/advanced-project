#define TRIG_PIN D1  // Connect TRIG pin of ultrasonic sensor to D1
#define ECHO_PIN D2  // Connect ECHO pin of ultrasonic sensor to D2
#define LED_PIN_1 D5 // Connect LED 1 to GPIO pin D5
#define LED_PIN_2 D6 // Connect LED 2 to GPIO pin D6

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
}

void loop() {
  long duration, distance;
  
  // Trigger the ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Read the duration of the echo pulse
  duration = pulseIn(ECHO_PIN, HIGH);
  
  // Calculate distance
  distance = duration * 0.034 / 2;  // Speed of sound is 340 m/s, divide by 2 for one-way travel
  
  // Print distance to serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Control LEDs based on distance
  if (distance > 30) {
    // If the object is far, turn off both LEDs
    analogWrite(LED_PIN_1, 0); // Turn off LED 1
    analogWrite(LED_PIN_2, 0); // Turn off LED 2
  } else {
    // If the object is near, dim and glow the LEDs
    int brightness = map(distance, 0, 50, 255, 0); // Map distance to LED brightness (inverse relationship)
    analogWrite(LED_PIN_1, brightness); // Set brightness for LED 1
    analogWrite(LED_PIN_2, brightness); // Set brightness for LED 2
  }
  
  delay(2000);  // Small delay between distance measurements
}
