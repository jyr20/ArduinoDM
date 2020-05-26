# ArduinoDM
A script for an Arduino and LED light strip to model the behaviour of a cryogenic dark matter detector.

Kit requires:

* An arduino board or similar
* An LED light strip compatible with the FastLED library (I used the WS2812B strip)
* Breadboard, wires and switches/LEDs for control purposes
* Some creativity and crafts to make the resulting contraption a little more pretty

Tge code is in main.ino. It includes 6 controls:

1) On/Off
2) Implementation of underground tunnel
3) Implementation of shielding
4) Use of radiopure materials and radiation treatment
5) Implementation of data analysis techniques
6) Timewarp feature to speed progression of time

Each of these controls is wired to a switch in a loop of:

**5V in\
|\
Resister (appopriate for LED)\
|\
LED (to show when control is activated)\
|\
----------------> DIGITAL PIN on arduino (read if HIGH/LOW and determine how to respond)\
|\
Simple switch\
|\
Ground**

So that when the switch is on, there is a voltage drop across the LED and the digital pin reads LOW.

The LED light stip supplies the power to the lights and the arduino. It connects to ground, Vin and a digital pin for control.
