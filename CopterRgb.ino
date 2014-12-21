#include <arduino.h>
#include <FastLED.h>
#include "QuadRgbLed.h"

#define LOOPTIME   50

QuadRgbLed copter(lpd8806,0,8,brg);
static long p_preMillis;
static long p_curMillis;
static int p_delMillis = LOOPTIME;
int patt_pos=0;
bool isActive=true;

void setup() {

};

void loop() {

  if(isActive) { // main loop
    p_curMillis = millis();
    if(p_curMillis - p_preMillis > p_delMillis) {
      // save the last time you blinked the LED 
      p_preMillis = p_curMillis;   
      // First we update pattern positions 
      // First we update pattern positions 
      patt_pos++;
      if(patt_pos == 16) {
        patt_pos = 0;
      }
    }
  }
};




