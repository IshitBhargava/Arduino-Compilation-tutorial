In this project, we will operate things like servos, lcd, stepper motors, rgb led, etc using a Arduino Mega 2560 or any other compaitable board. 

**Hardware Required:**

1x Arduino Mega 
1x Joystick
1x LDR or photoresistor module
1x Microphone sensor
1x IR sensor
1x ultrasonic HC-SR04 distance sensor
1x Water flow sensor
1x Touch sensor
1x Stepper motor
1x potentiometer
1x water level sensor
1x gas sensor MQ-135
5x LED or light emitting diode
1x/2x breadboard
1x LCD I2c 1602

___________________________________________________________________________________________________________________________________________________________________________________

**Connections:**
*Joystick:*
X axis pin: A6
Y axis pin: A7
SW pin: Anode of 1st LED
VCC: 5v
GND: GND 

*Photoresistor:*
VCC: 5v
GND: GND
Signal: A0

*Microphone:*
VCC: 5v
GND: GND
Ao: A10
Do: not required

*IR sensor:*
VCC: 5v 
GND: GND
Signal: A1

*HC-SR04:*
VCC: 5v
GND: GND
Trig: 2
Echo: 3

*Water flow sensor:*
VCC: IOREF
GND: GND
Signal: A3

*Touch Sensor:*
VCC: 3.3V 
GND: GND
Signal: A2

*Stepper motor:*
Common GND: GND
Coil 1: 8
Coil 2: 10
Coil 3: 11
Coil 4: 12

*Potentiometer:*
Terminal 1: GND
Terminal 2: 5v
Wiper: A9

*Water level sensor:*
VCC: IOREF
GND: GND
Signal: A8

*MQ-135:*
VCC: IOREF 
GND: GND
Do: Not needed
Ao: A11

*LCD:*
VCC: 5v
GND: GND
SDA: SDA or A4
SCL: SCL or A5

*led1:* 
Anode: Joystick SW
Cathode: GND 

*led2:*
Anode: 4
Cathode: GND

*led3:*
Anode: 4
Cathode: GND

*led4:*
Anode: 5
Cathode: GND

*led5:*
Anode: 14
Cathode: GND

_____________________________________________________________________________________________________________________________________________________________________________

**Upload the Code:**

Step 1: Download required libraries
Step 2: Connect your Arduino board via USB or Wi-fi (if supported)
Step 3: Select you COM port and arduino board
Step 4: Press on "upload code" button

____________________________________________________________________________________________________________________________

**Troubleshooting**

View the troubleshooting file for more information.


