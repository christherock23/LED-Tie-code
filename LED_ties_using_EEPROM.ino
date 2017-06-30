#include "FastLED.h"
#include "Patterns.h"
#include "Buttons.h"
#include <EEPROM.h>

FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    0
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

#define BRIGHTNESS          85
#define FRAMES_PER_SECOND  120

void setup() {
  delay(3000); // 3 second delay for recovery
  pinMode(BRIGHTNESS_BUTTON, INPUT_PULLUP);
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  
  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { 
rainbow,
rainbowWithGlitter,
confetti,
sinelon,
juggle,
bpm,
pride,
seashell
};

/* typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { 
sinelon,
rainbow,
rainbowWithGlitter,
juggle,
bpm,
confetti,
random_burst,
Fire,
}; */

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
  
void loop()
{

  switch (brightness){
    case 1:
    FastLED.setBrightness(brightness1);
    break;

    case 2:
    FastLED.setBrightness(brightness2);
    break;

    case 3:
    FastLED.setBrightness(brightness3);
    break;

    case 4:
    FastLED.setBrightness(brightness4);
    break;

    case 5:
    FastLED.setBrightness(brightness5);
    break;

    case 6:
    FastLED.setBrightness(brightness6);
    break;

    default:
    brightness = 1;
    break;
  }
  gCurrentPatternNumber = EEPROM.read(1);
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  if(buttonListener()) { nextPattern(); }
  if(brightnessButtonListener()) { return; }

}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
  EEPROM.write(1, gCurrentPatternNumber);
}
