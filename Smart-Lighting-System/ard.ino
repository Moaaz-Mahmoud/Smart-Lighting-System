int lightSensorPin = A0;
int LEDPin = 13;
int lightThreshold = 100;
int objectsDetected = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LEDPin, OUTPUT);
}

void loop() {
  int lightLevel = analogRead(lightSensorPin);
  if (lightLevel < lightThreshold) {
    Serial.write(objectsDetected);
    analogWrite(LEDPin, map(objectsDetected, 0, 10, 0, 255));
  }
}
