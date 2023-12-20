
//this code only works on the Arduino Mega or the Mega 2560 board, not on the Arduino Uno. 

//-------------------Libraries-----------------------------------

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Stepper.h>

//-------------------Libraries-----------------------------------

//-------------------------pins----------------------------------

const int ldrPin = A0; // Connect LDR to analog pin A0
const int trigPin = 2; // Connect Trig pin of HC-SR04 to digital pin 2
const int echoPin = 3; // Connect Echo pin of HC-SR04 to digital pin 3
const int irSensorPin = A1; // Analog pin for the IR sensor
const int ledPin = 4;     // Digital pin for the LED (optional, for visual indication)
const int touchSensorPin = A2;  // Analog pin for the touch sensor
const int led2Pin = 5;         // Digital pin for the LED (optional, for visual indication)
const int waterFlowSensorPin = A3;  // Analog pin for the water flow sensor
const int led3Pin = 6;               // Digital pin for the LED (optional, for visual indication)
const int joyXPin = A6;     // Joystick X-axis connected to analog pin A0
const int joyYPin = A7;     // Joystick Y-axis connected to analog pin A1
const int servoPin = 9;     // Servo control pin
const int stepperPins[] = {8, 10, 11, 12}; // Pins for the 4 coils of the stepper motor
const int gasSensorPin = 13; // Digital pin for the gas sensor
const int led4Pin = 14;     // Digital pin for the LED (named led4)
const int waterLevelSensorPin = A8;  // Analog pin for the water level sensor
const int potpin = A9;
const int soundSensorPin = A10;  // Connect the signal pin of the sound sensor to A0

//-------------------------pins----------------------------------

//--------------------------Liquid Crystal Definitions---------------------------

const int lcdColumns = 16; // Number of columns in the LCD
const int lcdRows = 2;    // Number of rows in the LCD

//--------------------------Liquid Crystal Definitions---------------------------

//-------------------------other tasks--------------------------------------------

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);
Servo myServo;
Stepper myStepper(200, stepperPins[0], stepperPins[1], stepperPins[2], stepperPins[3]);

//-------------------------other tasks--------------------------------------------

void setup() {
  Wire.begin();
  Serial.begin(28800);
  lcd.begin(lcdColumns, lcdRows);
  lcd.backlight(); // Turn on the backlight

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Ultimate Arduino");
  Lcd.setCursor(4,1);
  lcd.print("Tutorial");
  delay(5000);
  lcd.clear();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(irSensorPin, INPUT);
  pinMode(ledPin, OUTPUT);

  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);

  pinMode(potpin, INPUT);

  myServo.attach(servoPin);
  myStepper.setSpeed(0);  // Set initial speed to 0

  pinMode(gasSensorPin, INPUT);
  pinMode(led4Pin, OUTPUT);

  Serial.begin(9600);

}

void loop() {
  
  int potvalue = analogRead(potpin);
  Serial.println("pot value is: ");
  Serial.print(potvalue);
  
  if(potvalue >113){
    IR();
  }
  else if(potvalue <114 && potvalue >226){
    ultrasonic();
  }
  else if(potvalue <227 && potvalue >339){
    photoresistor();
  }
  else if(potvalue <340 && potvalue >452){
    touch();
  }
  else if(potvalue <453 && potvalue >565){
    waterflow();
  }
  else if(potvalue <566 && potvalue >678){
    joystick();
  }
  else if(potvalue <679 && potvalue >791){
    gas();
  }
  else if(potvalue <792 && potvalue >904){
    waterlevel();
  }
  else if(potvalue <905){
    microphone();
  }

}
void IR(){
    int irValue = analogRead(irSensorPin);
  float distance = map(irValue, 0, 1023, 0, 100); // Map analog value to a distance range (adjust as needed)

   
   if (irValue < 500) {
    digitalWrite(ledPin, HIGH); // Turn on LED for visual indication
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Distance:");
    lcd.setCursor(0, 1);
    lcd.print(distance);
    lcd.print(" cm");
    Serial.print(" | Object Detected!");
  } else {
    digitalWrite(ledPin, LOW); // Turn off LED
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No Object");
    lcd.setCursor(0, 1);
    lcd.print("Detected");
    Serial.print(" | No Object Detected");
  }
}
void ultrasonic(){
  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the pulse duration on the echo pin
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters
  float distance = duration * 0.034 / 2;

  // Display distance on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance:");
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print(" cm");

  // Print distance to Serial Monitor
  Serial.print(" | Distance in cms: ");
  Serial.print(distance);
  

}
void photoresistor(){
  int ldrValue = analogRead(ldrPin);
  int mappedValue = map(ldrValue, 0, 1023, 0, 1024); // Map the analog value to 0-1024

  lcd.clear(); // Clear the LCD

  lcd.setCursor(0, 0);
  lcd.print("LDR Value:");

  lcd.setCursor(0, 1);
  lcd.print(mappedValue);

}
void touch(){
   int touchValue = analogRead(touchSensorPin);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Touch Value:");
  lcd.setCursor(0, 1);
  lcd.print(touchValue);

  // You may need to adjust the threshold based on your specific sensor and conditions
  if (touchValue > 500) {
    digitalWrite(led2Pin, HIGH);  // Turn on LED for visual indication
    Serial.print(" | Touch Detected!");
  } else {
    digitalWrite(led2Pin, LOW);   // Turn off LED
    Serial.print(" | No Touch Detected");
  }
}
void waterflow(){
  int sensorValue = analogRead(waterFlowSensorPin);

  // Convert the sensor value to flow rate (adjust the formula based on sensor characteristics)
  float flowRate = map(sensorValue, 0, 1023, 0, 10);  // Assuming a linear relationship, adjust the range accordingly

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Flow Rate:");
  lcd.setCursor(0, 1);
  lcd.print(sensorValue);
  lcd.print(" L/min");

  // You may need to adjust the threshold based on your specific sensor and conditions
  if (sensorValue > 500) {
    digitalWrite(led3Pin, HIGH);  // Turn on LED for visual indication
    Serial.print(" | Water Flow Detected!");
  } else {
    digitalWrite(led3Pin, LOW);   // Turn off LED
    Serial.print(" | No Water Flow Detected");
  }
}
void joystick(){
  int joyXValue = analogRead(joyXPin);
  int joyYValue = analogRead(joyYPin);

  // Map joystick values to servo and stepper motor control
  int servoAngle = map(joyYValue, 0, 1023, 0, 180);
  int stepperSpeed = map(joyXValue, 0, 1023, 0, 3000);

  // Control the servo based on Y-axis
  myServo.write(servoAngle);

  // Control the stepper motor speed based on X-axis
  myStepper.setSpeed(stepperSpeed);
  myStepper.step(1);  // Move the stepper motor (adjust steps as needed)

  // Print values for debugging
  Serial.print(" | Servo Angle: ");
  Serial.print(servoAngle);
  Serial.print(" | Stepper Speed: ");
  Serial.print(stepperSpeed);

}
void gas(){
  int gasValue = digitalRead(gasSensorPin);

  if (gasValue == HIGH) {
    digitalWrite(led4Pin, HIGH); // Turn on LED4
    // You can add additional actions when gas is detected
  } else {
    digitalWrite(led4Pin, LOW);  // Turn off LED4
    // You can add additional actions when no gas is detected
  }
}
void waterlevel(){
  int waterLevel = analogRead(waterLevelSensorPin);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Water Level:");
  lcd.setCursor(0, 1);
  lcd.print(waterLevel);

}
void microphone(){
  int soundValue = analogRead(soundSensorPin);  // Read the analog value from the sound sensor
  int loudness = map(soundValue, 0, 1023, 0, 100);  // Map the value to a range from 0 to 100

  Serial.print(" | Sound Value: ");
  Serial.print(soundValue);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Loudness: ");
  lcd.print(loudness);
  lcd.print("%");

}
