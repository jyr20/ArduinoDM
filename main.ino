// For LED strip
#include <FastLED.h>
#define LED_PIN     10
#define NUM_LEDS    60
#define BRIGHTNESS  128
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 24


// Define pin numbers for different switches
int onSwitch = 2;
int caveSwitch = 3;
int shieldSwitch = 4;
int pureSwitch = 5;
int procSwitch = 6;
int timeSwitch = 7;
int switches[4] = {caveSwitch, shieldSwitch, pureSwitch, procSwitch};
int nums[4] = {1, 2, 4, 8};

// Switch mode variables
int switchMode;
int onOff;
int timeWarp;
double warpSpeed = 1.0E9;

// Stats needed to calculate light logic
double Bnum;
double Snum = 5000.0;
double rat;
double totnum;
double metric;
double randNum;
double randNum2;
double scale = 50.0;

void setup() {
  // put your setup code here, to run once:
  delay( 1000 ); // power-up safety delay

  // Initialize serial communication
//  Serial.begin(9600);

  // LED strip initialisation
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );

  // make the switch's pins inputs:
  pinMode(onSwitch, INPUT);
  pinMode(caveSwitch, INPUT);
  pinMode(shieldSwitch, INPUT);
  pinMode(pureSwitch, INPUT);
  pinMode(procSwitch, INPUT);
  pinMode(timeSwitch, INPUT);
  digitalWrite(onSwitch,HIGH);
  digitalWrite(caveSwitch,HIGH);
  digitalWrite(pureSwitch,HIGH);
  digitalWrite(shieldSwitch,HIGH);
  digitalWrite(procSwitch,HIGH);
  digitalWrite(timeSwitch,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

  // Check on/off
  onOff = digitalRead(onSwitch);

  if (onOff == LOW) {  
    // Declare mode and loop through switch status
    int mode = 0;
    for (int i = 0; i < 4; i++) {
      switchMode = digitalRead(switches[i]);
      mode += (switchMode == LOW) ? nums[i] : 0;
    }

    // switch expression for 16 different possibilities
    switch (mode) {
      case 0:
        Bnum = 7.9E14;
        rat = 0.1;
        break;
      case 1:
        Bnum = 7.9E14*0.2; // 0.2 to account for saturation
        rat = 0.999;
        break;
      case 2:
        Bnum = 1.2E10;
        rat = 0.1;
        break;
      case 3:
        Bnum = 1.7E7;
        rat = 0.999;
        break;
      case 4:
        Bnum = 7.9E14;
        rat = 0.1;
        break;
      case 5:
        Bnum = 7.9E14;
        rat = 0.999;
        break;
      case 6:
        Bnum = 1.2E10;
        rat = 0.1;
        break;
      case 7:
        Bnum = 2.2E5;
        rat = 0.999;
        break;
      case 8:
        Bnum = 5.2E7;
        rat = 0.1;
        break;
      case 9:
        Bnum = 4.7E6;
        rat = 0.999;
        break;
      case 10:
        Bnum = 4.7E7;
        rat = 0.1;
        break;
      case 11:
        Bnum = 120.0;
        rat = 0.999;
        break;
      case 12:
        Bnum = 5.2E7;
        rat = 0.1;
        break;
      case 13:
        Bnum = 4.7E6;
        rat = 0.999;
        break;
      case 14:
        Bnum = 4.7E7;
        rat = 0.1;
        break;
      case 15:
        Bnum = 1.0;
        rat = 0.999;
        break;
    }
    
    // Calculate total, and metric
    // Metric is totnum/saturation*0.1*(warpspeed || 1)
    totnum = Snum + Bnum;
    metric = (timeWarp == LOW) ? totnum/7.9E14*warpSpeed : totnum/7.9E14*0.1;
//    metric = (timeWarp == LOW) ? log(totnum)/scale : totnum/7.9E14*0.1;

    
    // Check if in TimeWarp mode
    timeWarp = digitalRead(timeSwitch);

    for (int i = 0; i < NUM_LEDS; i++) {
      // check if it should be on, else turn off,
      // using the total number in log space as metric
      randNum = r2();
      if (metric > randNum) {
        // Check type of hit
        randNum2 = r2();
        //        Serial.println(randNum2);
        if (Bnum / totnum > randNum2) {
          // Background event triggered
          // Check if cave or cosmic
          if (Bnum / totnum * rat < randNum2) {
            // It's cosmic
            leds[i] = CRGB(255, 255, 0);
          }
          else {
            // It's cave
            leds[i] = CRGB(255, 0, 0);
          }

        }
        else {
          // It's DM!
          leds[i] = CRGB(0, 0, 255);
        }
      }
      else {
        // Turn off LED
        leds[i] = CRGB(0, 0, 0);
      }
    }
  }

  // Turn LEDs off
  else {
    for ( int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(0, 0, 0);
    }
  }


  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);


}

// Function for random number 0 to 1
double r2()
{
  return (double)rand() / (double)RAND_MAX ;
}
