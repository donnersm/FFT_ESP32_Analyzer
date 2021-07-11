 /********************************************************************************************************************************************************
 *                                                                                                                                                       *
 *  Project:         FFT Spectrum Analyzer                                                                                                               *
 *  Target Platform: ESP32                                                                                                                               *
 *                                                                                                                                                       * 
 *  Version: 1.0                                                                                                                                         *
 *  Hardware setup: See github                                                                                                                           *
 *  Spectrum analyses done with analog chips MSGEQ7                                                                                                      *
 *                                                                                                                                                       * 
 *  Mark Donners                                                                                                                                         *
 *  The Electronic Engineer                                                                                                                              *
 *  Website:   www.theelectronicengineer.nl                                                                                                              *
 *  facebook:  https://www.facebook.com/TheelectronicEngineer                                                                                            *
 *  youtube:   https://www.youtube.com/channel/UCm5wy-2RoXGjG2F9wpDFF3w                                                                                  *
 *  github:    https://github.com/donnersm                                                                                                               *
 *                                                                                                                                                       *  
 ********************************************************************************************************************************************************/
 

#pragma once
#include "Settings.h"
/* There are several options to display the data from the FFT.
 * 1. Use a ledstrip like WS2812 or simular
 * 2. Use a Hub75 display
 * 3. Using both is possible but not recommended because of the required speed.
 */

// select one of these and comment out the other
//#define Ledstrip
#define HUB75

//Panel settings change to match your setup
#ifdef HUB75
 #define PANEL_WIDTH            64
 #define PANEL_HEIGHT           64                  // Panel height of 64 will required PIN_E to be defined.
 #define PANELS_NUMBER          2                   // Number of chained panels, if just a single panel, obviously set to 1
 // only need to match panel settings above
 #define PANE_WIDTH PANEL_WIDTH * PANELS_NUMBER
 #define PANE_HEIGHT PANEL_HEIGHT
 const uint8_t kMatrixWidth =   PANEL_WIDTH * PANELS_NUMBER;                // Matrix width --> number of columns in your led matrix
 const uint8_t kMatrixHeight =  PANEL_HEIGHT;                 // Matrix height --> number of leds per column
#endif



// Ledstrip settings
#define CHIPSET         WS2812B                     // LED strip type
#define LED_PIN         21                          // LED strip data
//#define SERPENTINE     false                        // Set to false if you're LEDS are connected end to end, true if serpentine
#define COLOR_ORDER     GRB                         // If colours look wrong, play with this
#define LED_VOLTS       5                           // Usually 5 or 12
#define MAX_MILLIAMPS   2000                        // Careful with the amount of power here if running off USB port
#ifdef Ledstrip
 const uint8_t kMatrixWidth =32;//128;                    // Matrix width --> number of columns in your led matrix
 const uint8_t kMatrixHeight = 16;//64;                   // Matrix height --> number of leds per column
 #define PANE_WIDTH kMatrixWidth
#endif

#define BAR_WIDTH  (kMatrixWidth /(numBands ))  // If width >= 8 light 1 LED width per bar, >= 16 light 2 LEDs width bar etc
#define TOP            (kMatrixHeight - 0)         // Don't allow the bars to go offscreen
#define NeededWidth (BAR_WIDTH * numBands)           // we need this to see if all bands fit or that we have left over space
#define NUM_LEDS   (kMatrixWidth * kMatrixHeight)   // Total number of LEDs
CRGB leds[NUM_LEDS];

//***********************************************************************
// These are the settings for the Hub75 display
// pin settings, dont change unless you are using customized hardware
//***********************************************************************

#define A_PIN         23
#define B_PIN         19
#define C_PIN         5
#define D_PIN         17
#define E_PIN         22
#define LAT_PIN       18
#define OE_PIN        15
#define CLK_PIN       16
#define R1_PIN        33
#define B2_PIN        13
#define R2_PIN        14
#define G2_PIN        12
#define G1_PIN        26
#define B1_PIN        27

 
#ifdef HUB75
// placeholder for the matrix object
MatrixPanel_I2S_DMA *dma_display = nullptr;
#endif


// See manual if you need to change these settings
#ifdef Ledstrip
  // FastLED_NeoMaxtrix - see https://github.com/marcmerlin/FastLED_NeoMatrix for Tiled Matrixes, Zig-Zag and so forth
  FastLED_NeoMatrix *matrix = new FastLED_NeoMatrix(leds, kMatrixWidth, kMatrixHeight,
                                  NEO_MATRIX_BOTTOM        + NEO_MATRIX_RIGHT +
                                  NEO_MATRIX_COLUMNS       + NEO_MATRIX_ZIGZAG +
                                  NEO_TILE_TOP + NEO_TILE_LEFT + NEO_TILE_ROWS);

/* // this one is used if you are using a ledstrip setup simular to the one from the acryllic spectrum analyzer
  FastLED_NeoMatrix *matrix = new FastLED_NeoMatrix(leds, kMatrixWidth, kMatrixHeight,
                                  NEO_MATRIX_BOTTOM        + NEO_MATRIX_LEFT +
                                  NEO_MATRIX_COLUMNS       + NEO_MATRIX_PROGRESSIVE +
                                  NEO_TILE_TOP + NEO_TILE_LEFT + NEO_TILE_ROWS);
 */

#endif

// See manual if you need to change these settings
void SetupHUB75(void){
 #ifdef HUB75
  HUB75_I2S_CFG mxconfig;
  mxconfig.mx_height = PANEL_HEIGHT;      // we have 64 pix heigh panels
  mxconfig.mx_width = PANEL_WIDTH;
  mxconfig.chain_length = PANELS_NUMBER;  // we have 2 panels chained
  mxconfig.gpio.e = E_PIN;                // we MUST assign pin e to some free pin on a board to drive 64 pix height panels with 1/32 scan
  mxconfig.gpio.r1 =R1_PIN;
  mxconfig.gpio.g1 = G1_PIN;
  mxconfig.gpio.b1 = B1_PIN;
  mxconfig.gpio.r2 = R2_PIN;
  mxconfig.gpio.g2 = G2_PIN;
  mxconfig.gpio.b2 = B2_PIN;
  mxconfig.gpio.a = A_PIN;
  mxconfig.gpio.b = B_PIN;
  mxconfig.gpio.c = C_PIN;
  mxconfig.gpio.d = D_PIN;
  mxconfig.gpio.e = E_PIN;
  mxconfig.gpio.lat = LAT_PIN;
  mxconfig.gpio.oe = OE_PIN;
  mxconfig.gpio.clk = CLK_PIN;
  mxconfig.driver = HUB75_I2S_CFG::MBI5124;     // in case that we use panels based on FM6126A chip, we can change that
  mxconfig.clkphase = true; // some panels need a  reversed clockpulse I first encountered it in batch may 2021 PH3 64*64 V4.1 HX
  mxconfig.latch_blanking = 4;
  //mxconfig.i2sspeed = HUB75_I2S_CFG::HZ_20M;
  // OK, now we can create our matrix object
  dma_display = new MatrixPanel_I2S_DMA(mxconfig);
  // dma_display->setLatBlanking(2);
  // let's adjust default brightness to about xx%
  dma_display->setBrightness8(50);    // range is 0-255, 0 - 0%, 255 - 100%
  //dma_display->setBrightness8(map(analogRead(BRIGHTNESSPOT),0,4095,10,BRIGHTNESSMAX));
  // Allocate memory and start DMA display
  if( not dma_display->begin() )
      Serial.println("****** !KABOOM! I2S memory allocation failed ***********");
 #endif  
}


void SetupLEDSTRIP(void){
 #ifdef Ledstrip
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.setMaxPowerInVoltsAndMilliamps(LED_VOLTS, MAX_MILLIAMPS);
  FastLED.setBrightness(BRIGHTNESSMARK);
  FastLED.clear();
 #endif   
}
