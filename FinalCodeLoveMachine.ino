#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
//
int pos = 0;    // variable to store the servo position
int inc = 1;

//adding the LED sensor code
// These constants won't change:
const int sensorPin = A0;    // pin that the sensor is attached to
const int ledPin = 12;        // pin that the LED is attached to

// variables:
int sensorValue = 0;         // the sensor value
int sensorMin = 1023;        // minimum sensor value
int sensorMax = 0;           // maximum sensor value

void setup() {
   myservo.attach(7);  // attaches the servo on pin 7 to the servo object
   Serial.begin(9600);

   // turn on LED to signal the start of the calibration period:
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  // calibrate during the first five seconds
  while (millis() < 5000) {
  sensorValue = analogRead(sensorPin);

    // record the maximum sensor value
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }
  }

  Serial.print("Min: ");
  Serial.println(sensorMin);
  Serial.print("Max: ");
  Serial.println(sensorMax);

  // signal the end of the calibration period
  digitalWrite(ledPin, LOW);
}

void loop() {

  int lightControl = analogRead(A3);

  lightControl = map (lightControl, 0, 1023, 0, 180);

  myservo.write(lightControl);
  
// now adding led code
  // read the sensor:
  sensorValue = analogRead(sensorPin);

  Serial.println(sensorValue);

  if(sensorValue > 700){
    Serial.print("I like you!");
    digitalWrite(12, LOW);
  }

  else {
    Serial.println("I don't like you");
    digitalWrite(12, HIGH);
  }
//  delay(1000);

  
  // apply the calibration to the sensor reading
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 255);

  // in case the sensor value is outside the range seen during calibration
  sensorValue = constrain(sensorValue, 0, 255);

  // fade the LED using the calibrated value:
  analogWrite(ledPin, sensorValue);

  
  delay(15);
}
