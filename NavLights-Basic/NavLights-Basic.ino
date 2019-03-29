/*  NavLights-Basic
 *   Aaron Woehler
 */
/**CONFIGURATION***********************************/
#define LED_PIN              12
#define LED_COUNT             8
#define PORT_NAVIGATION       0
#define PORT_COLLISION        1
#define STARBOARD_NAVIGATION  2
#define STARBOARD_COLLISION   3
#define ANTICOLLISSION_1      4
#define ANTICOLLISSION_2      5
#define LANDING_1             6
#define LANDING_2             7

int delayMills = 10;

/**SETUP*******************************************/
#include <PololuLedStrip.h>

// Create an ledStrip object and specify the pin it will use.
PololuLedStrip<LED_PIN> ledStrip;

// Create a buffer for holding the colors (3 bytes per color).
rgb_color colors[LED_COUNT];
rgb_color red;
rgb_color green;
rgb_color white;
rgb_color off;
int counter = 0;
void setup()
{
  delay(delayMills);
  // Start up the serial port, for communication with the PC.
  Serial.begin(57600);
  Serial.println("NavLight-Basic");
  Serial.print("LED Pin: ");
  Serial.println( LED_PIN );
  Serial.print("delay: ");
  Serial.println( delayMills );
  Serial.print("LEDS: ");
  Serial.println( LED_COUNT );
  Serial.print("Port Navigation:");
  Serial.println( PORT_NAVIGATION );
  Serial.print("Port Collision: ");
  Serial.println( PORT_COLLISION );
  Serial.print("Starboard Navigation: ");
  Serial.println( STARBOARD_NAVIGATION );
  Serial.print("Starboard Collision: ");
  Serial.println( STARBOARD_COLLISION );
  Serial.print("Anticollission 1: ");
  Serial.println( ANTICOLLISSION_1 );
  Serial.print("Anticollission 2: ");
  Serial.println( ANTICOLLISSION_2 );
  Serial.print("Landing 1:");
  Serial.println( LANDING_1 );
  Serial.print("Landing 2:");
  Serial.println( LANDING_2 );
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  off.red = 0;
  off.green = 0;
  off.blue = 0;
  
  red.red = 255;
  red.green = 0;
  red.blue = 0;

  green.red = 0;
  green.green = 255;
  green.blue = 0;

  white.red = 255;
  white.green = 255;
  white.blue = 255;
  // Write to the LED strip.

  //Landing light
  colors[LANDING_1] = off;
  colors[LANDING_2] = off;

  //Port Wing Tip
  colors[PORT_NAVIGATION] = red;
  colors[PORT_COLLISION] = white;
  
  //Starboard Wing Tip
  colors[STARBOARD_NAVIGATION] = green;
  colors[STARBOARD_COLLISION] = white;

  //Red Strobe;
  colors[ANTICOLLISSION_1] = red;
  colors[ANTICOLLISSION_2] = red;
  colors[LANDING_1] = white;
  colors[LANDING_2] = white;

  ledStrip.write(colors, LED_COUNT);
  digitalWrite(LED_BUILTIN, LOW);
  delay(delayMills);
}

void loop()
{
  delay(delayMills);
  counter = (counter + 1) %250;
  //Alternate red anticollision and white stobe lights.
  if( counter > 150 ) {
    colors[PORT_COLLISION] = white;
    colors[STARBOARD_COLLISION] = white;
    colors[ANTICOLLISSION_1] = off;
    colors[ANTICOLLISSION_2] = off;
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    colors[PORT_COLLISION] = off;
    colors[STARBOARD_COLLISION] = off;
    colors[ANTICOLLISSION_1] = red;
    colors[ANTICOLLISSION_2] = red;
    digitalWrite(LED_BUILTIN, LOW);
  }
  ledStrip.write(colors, LED_COUNT);
}
