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
// Debug features should default be off!
#define PrintRAWBins        0                       // set to 1 if you want to print the RAW FFT BIN values of each pass to the serial port
#define PrintADCRAW         0                       // Set to 1 if you want to print the RAW ADC Values's of each pass to the serial port--> that is a lot of samples!!
#define VisualizeAudio      0                       // Sends the raw ADC values from buffer to serial plotter...that is a lot of data!!
#define CalibratieLog       0                       // a tool tell help with  calibrating to noise input signal
int  DEBUG =                0 ;                     // When debug=1, extra information is printed to serial port. Turn of if not needed--> DEBUG=0
#define DEBUG_BUFFER_SIZE   100                     // Debug buffer size

//Options Change to your likings
#define BottomRowAlwaysOn   1                       // if set to 1, bottom row is always on. Setting only applies to LEDstrip not HUB75
#define Fallingspeed        5                       // Falling down factor that effects the speed of falling tiles
#define LogoBoot            1                       // Show logo on boot when set to 1, only works in combination with HUB75
int Peakdelay =             60;                     // Delay before peak falls down to stack. Overruled by PEAKDEALY Potmeter
#define GAIN_DAMPEN         2                       // Higher values cause auto gain to react more slowly
#define SecToChangePattern  10                      // number of seconds that pattern changes when auto change mode is enabled
#define MAX_VU              5000                    // How high our VU could max out at.  Arbitarily tuned.
int buttonPushCounter =     0;                      // This number defines what pattern to start after boot (0 to 12)
bool autoChangePatterns =   true;                  // After boot, the pattern will not change automatically. 
int NoiseTresshold =        1500;                   // this will effect the upper bands most.
#define DemoAfterSec        6000                    // if there is no input signal during this number of milli seconds, the unit will go to demo mode
#define DemoTreshold        500                     // this defines the treshold that will get the unit out of demo mode
#define BRIGHTNESSMAX       255                     // Max brightness of the leds...carefull...to bright might draw to much amps!
int BRIGHTNESSMARK= 50;                            // Default brightnetss, however, overruled by the Brightness potmeter
int BRIGHTNESSMIN = 20;                              // Min brightness
//buttonstuf don't change unless you know what you are doing
#define ShortPress          45
#define LongPress           2000
#define LongerPress         4000
#define ButtonTimeout       200
#define ButtonSequenceRepeatTime 200

//Controls  //don't change unless you are using your own hardware design
#define BRIGHTNESSPOT 2 
#define PEAKDELAYPOT  4

// Other stuff don't change
#define ARRAYSIZE(a)    (sizeof(a)/sizeof(a[0]))
char PeakFlag[numBands];                           // the top peak delay needs to have a flag because it has different timing while floating compared to falling to the stack
int PeakTimer[numBands];                           // counter how many loops to stay floating before falling to stack
uint8_t colorTimer = 0;
volatile float         gVU       = 0;              // Instantaneous read of VU value
volatile float         oldVU     = 0;              // Previous read of VU value
#define ADC_INPUT ADC1_CHANNEL_0
uint16_t offset = (int)ADC_INPUT * 0x1000 + 0xFFF;
double vReal[SAMPLEBLOCK];
double vImag[SAMPLEBLOCK];
int16_t samples[SAMPLEBLOCK];
arduinoFFT FFT = arduinoFFT(); /* Create FFT object */
byte peak[65] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};              // The length of these arrays must be >= NUM_BANDS
int oldBarHeights[65] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};      // so they are set to 65
float FreqBins[65] = {0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};



/****************************************************************************
 * Colors of bars and peaks in different modes, changeable to your likings  *
 ****************************************************************************/
// Colors mode 0
#define ChangingBar_Color   y * (255 / kMatrixHeight) + colorTimer, 255, 255
// no peaks

// Colors mode 1 These are the colors from the TRIBAR when using Ledstrip
#define TriBar_Color_Top      0 , 255, 255    // Red CHSV
#define TriBar_Color_Bottom   95 , 255, 255   // Green CHSV
#define TriBar_Color_Middle   45, 255, 255    // Yellow CHSV

#define TriBar_Color_Top_Peak      0 , 255, 255    // Red CHSV
#define TriBar_Color_Bottom_Peak   95 , 255, 255   // Green CHSV
#define TriBar_Color_Middle_Peak   45, 255, 255    // Yellow CHSV

// Colors mode 1 These are the colors from the TRIBAR when using HUB75
#define TriBar_RGB_Top      255 , 0, 0    // Red CRGB
#define TriBar_RGB_Bottom   0 , 255, 0   // Green CRGB
#define TriBar_RGB_Middle   255, 255, 0    // Yellow CRGB

#define TriBar_RGB_Top_Peak      255 , 0, 0    // Red CRGB
#define TriBar_RGB_Bottom_Peak   0 , 255, 0   // Green CRGB
#define TriBar_RGB_Middle_Peak   255, 255, 0    // Yellow CRGB

// hub 75 center bars
#define Center_RGB_Edge      255 , 0, 0    // Red CRGB
#define Center_RGB_Middle   255, 255, 0    // Yellow CRGB
// hub 75 center bars 2
#define Center_RGB_Edge2      255 , 0, 0    // Red CRGB
#define Center_RGB_Middle2   255, 255, 255    // Yellow CRGB

// Colors mode 2
#define RainbowBar_Color  (x / BAR_WIDTH) * (255 / numBands), 255, 255
#define PeakColor1  0, 0, 255       // white CHSV

// Colors mode 3
#define PeakColor2  0, 0, 255       // white CHSV
DEFINE_GRADIENT_PALETTE( purple_gp ) {
  0,   0, 212, 255,   //blue
255, 179,   0, 255 }; //purple
CRGBPalette16 purplePal = purple_gp;


// Colors mode 4
#define SameBar_Color1      0 , 255, 255      //red  CHSV
#define PeakColor3  160, 255, 255   // blue CHSV

// Colors mode 5
#define SameBar_Color2      160 , 255, 255    //blue  CHSV
#define PeakColor4  0, 255, 255   // red CHSV

// Colors mode 6
DEFINE_GRADIENT_PALETTE( redyellow_gp ) {  
  0,   200, 200,  200,   //white
 64,   255, 218,    0,   //yellow
128,   231,   0,    0,   //red
192,   255, 218,    0,   //yellow
255,   200, 200,  200 }; //white
CRGBPalette16 heatPal = redyellow_gp;
// no peaks

// Colors mode 7
DEFINE_GRADIENT_PALETTE( outrun_gp ) {
  0, 141,   0, 100,   //purple
127, 255, 192,   0,   //yellow
255,   0,   5, 255 };  //blue
CRGBPalette16 outrunPal = outrun_gp;
// no peaks

// Colors mode 8
DEFINE_GRADIENT_PALETTE( mark_gp2 ) {
  0,   255,   218,    0,   //Yellow
 64,   200, 200,    200,   //white
128,   141,   0, 100,   //pur
192,   200, 200,    200,   //white
255,   255,   218,    0,};   //Yellow
CRGBPalette16 markPal2 = mark_gp2;

// Colors mode 9
// no bars only peaks
DEFINE_GRADIENT_PALETTE( mark_gp ) {
  0,   231,   0,    0,   //red
 64,   200, 200,    200,   //white
128,   200, 200,    200,   //white
192,   200, 200,    200,   //white
255,   231, 0,  0,};   //red
CRGBPalette16 markPal = mark_gp;

// Colors mode 10
// no bars only peaks
#define PeakColor5  160, 255, 255   // blue CHSV

// These are the colors from the TRIPEAK mode 11
// no bars
#define TriBar_Color_Top_Peak2      0 , 255, 255    // Red CHSV
#define TriBar_Color_Bottom_Peak2   95 , 255, 255   // Green CHSV
#define TriBar_Color_Middle_Peak2   45, 255, 255    // Yellow CHSV

/******************************************************************
* Setting below are only related to the demo Fire mode            *
*******************************************************************/


#define FPS 25              /* Refresh rate 15 looks good*/

/* Flare constants */
const uint8_t flarerows = 8;  //8  /* number of rows (from bottom) allowed to flare */
const uint8_t maxflare = 50;//4;     /* max number of simultaneous flares */
const uint8_t flarechance = 50; /* 50chance (%) of a new flare (if there's room) */
const uint8_t flaredecay = 14;  /* decay rate of flare radiation; 14 is good */

/* This is the map of colors from coolest (black) to hottest. Want blue flames? Go for it! */
const uint32_t colors[] = {
  0x000000,
  0x100000,
  0x300000,
  0x600000,
  0x800000,
  0xA00000,
  0xC02000,
  0xC04000,
  0xC06000,
  0xC08000,
  0x807080
};
