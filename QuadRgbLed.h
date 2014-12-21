/*
  CopterRgbLed.h - Library for controlling RGB Ledson a multicopter.
 Author: jjstecchino, December 15, 2014.
 Relies on FastLED library
 Released into the public domain.
 */
#ifndef CopterRgbLed_h
#define CopterRgbLed_h

#include <FastLED.h>
#include <arduino.h>

#define MAX_LEDS  16
#define ARMS    4

#define RO(X) RGB_BYTE(RGB_ORDER, X)
#define RGB_BYTE(RO,X) (((RO)>>(3*(2-(X)))) & 0x3)

#define RGB_BYTE0(RO) ((RO>>6) & 0x3)
#define RGB_BYTE1(RO) ((RO>>3) & 0x3)
#define RGB_BYTE2(RO) ((RO) & 0x3)

enum Chipset {
  lpd8806,
  ws2801
};

// Define RGB orderings
enum RgbOrder {
  rgb=0012,
  rbg=0021,
  grb=0102,
  gbr=0120,
  brg=0201,
  bgr=0210
};

class QuadRgbLed
{
public:
  QuadRgbLed(Chipset chipset, int frameType, int ledsPerArm, RgbOrder rgbOrder );
  void setArmColor(CRGB color, char arm);
  void ledsOff();
  void runPattern(int pattern, char arm);
  void updateArms();
private:
  static int const _pattern = 0xaaaa;
  Chipset _chipset;
  RgbOrder _rgbOrder;
  int _frameType;
  int _ledsPerArm;
  CRGB _leds[8][MAX_LEDS];   // array of pointers to a CRGB (3 bytes) array 
  bool _flashers[8][MAX_LEDS];
  void setupFastLED(Chipset chipset, int numLeds);   // private method to setup fastled
  CRGB reorderRgb(CRGB color);
  char rgbIndex( char x);
  boolean getLBit(byte Reg, byte whichBit);

};

#endif


