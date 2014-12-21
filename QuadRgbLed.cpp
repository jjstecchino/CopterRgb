/*
  CopterRgbLed.cpp - Library for controlling RGB Ledson a multicopter.
 Author: jjstecchino, December 15, 2014.
 Relies on FastLED library
 Released into the public domain.
 */

#include "QuadRgbLed.h"
#define RGB_ORDER BRG

QuadRgbLed::QuadRgbLed(Chipset chipset, int frameType, int ledsPerArm, RgbOrder order )
{
  _ledsPerArm=ledsPerArm;
  _rgbOrder=order;
  setupFastLED(chipset, ledsPerArm);
  ledsOff();
  
}

void QuadRgbLed::runPattern(int pattern, char patpos)
{
      if(patt_pos >= 0 && patt_pos <= 7) {
        if(getLBit(pattByteA, patt_pos)) 
          digitalWrite(REAR, EN);
        else
          digitalWrite(REAR, DI);
      } else {
        if(getLBit(pattByteB, patt_pos - 8)) 
          digitalWrite(REAR, EN);
        else
          digitalWrite(REAR, DI);
      }
}

void QuadRgbLed::setArmColor(CRGB color, char arm)
{
  for(int i=0; i<_ledsPerArm; i++) {
    _leds[arm][i]=reorderRgb(color);
  }
}

void QuadRgbLed::ledsOff() {
  for(int i=0; i<ARMS; i++) {
    setArmColor(CRGB::Black, i);
  }
}

void QuadRgbLed::updateArms()
{
  FastLED.show();
}

void QuadRgbLed::setupFastLED(Chipset chipset, int numLeds)
{
  switch (chipset)
  {
    //SPI Based Chipsets
  case lpd8806:
    FastLED.addLeds<LPD8806, 2, 3, RGB>(_leds[0], numLeds);
    FastLED.addLeds<LPD8806, 4, 5, RGB>(_leds[1], numLeds);
    FastLED.addLeds<LPD8806, 6, 7, RGB>(_leds[2], numLeds);
    FastLED.addLeds<LPD8806, 8, 9, RGB>(_leds[3], numLeds);
    break;
  case ws2801:
    FastLED.addLeds<WS2801, 2, RGB>(_leds[0], numLeds);
    FastLED.addLeds<WS2801, 3, RGB>(_leds[1], numLeds);
    FastLED.addLeds<WS2801, 4, RGB>(_leds[2], numLeds);
    FastLED.addLeds<WS2801, 5, RGB>(_leds[3], numLeds);
    if (ARMS>=4){    // it is exa or octacopter
      FastLED.addLeds<WS2801, 6, RGB>(_leds[4], numLeds);
      FastLED.addLeds<WS2801, 7, RGB>(_leds[5], numLeds);
    }
    if(ARMS>=6) {    // it is octacopter
      FastLED.addLeds<WS2801, 8, RGB>(_leds[6], numLeds);
      FastLED.addLeds<WS2801, 9, RGB>(_leds[7], numLeds);
    }
    break;

  default:
    //TODO: Some error condition should go here
    break;
  }
  FastLED.clear();
  FastLED.show();
}


CRGB QuadRgbLed::reorderRgb (CRGB color) {
 CRGB reorderedColor;
 reorderedColor.r = color.raw[rgbIndex(0)];
 reorderedColor.g = color.raw[rgbIndex(1)];
 reorderedColor.b = color.raw[rgbIndex(2)];
 return reorderedColor;
}

char QuadRgbLed::rgbIndex( char x) {
    return (((_rgbOrder)>>(3*(2-(x)))) & 0x3);
}

boolean QuadRgbLed::getLBit(byte Reg, byte whichBit) {
  boolean State;
  switch(whichBit) {
    case 0:
     State = Reg & (1 << 7);
     return State;
     break;
    case 1:
     State = Reg & (1 << 6);
     return State;
     break;
    case 2:
     State = Reg & (1 << 5);
     return State;
     break;
    case 3:
     State = Reg & (1 << 4);
     return State;
     break;
    case 4:
     State = Reg & (1 << 3);
     return State;
     break;
    case 5:
     State = Reg & (1 << 2);
     return State;
     break;
    case 6:
     State = Reg & (1 << 1);
     return State;
     break;
    case 7:
     State = Reg & (1 << 0);
     return State;
     break;
  }
}




