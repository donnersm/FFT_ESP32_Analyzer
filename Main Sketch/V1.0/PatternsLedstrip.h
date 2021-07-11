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

/********************************************************************************************************************************
 * ** SUB Rountines related to Paterns and Peaks                                                                               **
 ********************************************************************************************************************************/
#ifdef Ledstrip


//************ Mode 0 ***********
 void changingBarsLS(int band, int barHeight) {
  int xStart = BAR_WIDTH * band;
  for (int x = xStart; x < xStart + BAR_WIDTH; x++) {
    for (int y = TOP; y >= 0; y--) {
     if(y >= TOP - barHeight){
        matrix -> drawPixel(x, y, CHSV(ChangingBar_Color));
     }
     else {
      matrix->drawPixel(x, y, CRGB(0, 0, 0)); // make unused pixel in a band black
     }
    } 
  }
}

//************ Mode 1 ***********
 void TriBarLS(int band, int barHeight) {
  int xStart = BAR_WIDTH * band;
  for (int x = xStart; x < xStart + BAR_WIDTH; x++) {
    for (int y = TOP; y >= 0; y--) {
     if(y >= TOP - barHeight){
        if (y < (kMatrixHeight/3)) matrix -> drawPixel(x, y, CHSV(TriBar_Color_Top));     //Top red
      else if (y > (1 *kMatrixHeight/2)) matrix -> drawPixel(x, y, CHSV(TriBar_Color_Bottom)); //green
      else matrix -> drawPixel(x, y, CHSV(TriBar_Color_Middle));      //yellow
     }
     else {
      matrix->drawPixel(x, y, CRGB(0, 0, 0)); // make unused pixel in a band black
     }
    } 
  }
}

void TriPeakLS(int band) {
  int xStart = BAR_WIDTH * band;
  int peakHeight = TOP - peak[band] - 1;
  for (int x = xStart; x < xStart + BAR_WIDTH; x++) {
    if (peakHeight < 4) matrix -> drawPixel(x, peakHeight, CHSV(TriBar_Color_Top_Peak)); //Top red
    else if (peakHeight > 8) matrix -> drawPixel(x, peakHeight, CHSV(TriBar_Color_Bottom_Peak)); //green
    else matrix -> drawPixel(x, peakHeight, CHSV(TriBar_Color_Middle_Peak)); //yellow
  }
}
//************ Mode 2 ***********
 void rainbowBarsLS(int band, int barHeight) {
  int xStart = BAR_WIDTH * band;
  for (int x = xStart; x < xStart + BAR_WIDTH; x++) {
    for (int y = TOP; y >= 0; y--) {
     if(y >= TOP - barHeight){
        matrix -> drawPixel(x, y, CHSV(RainbowBar_Color));
     }
     else {
      matrix->drawPixel(x, y, CRGB(0, 0, 0)); // make unused pixel in a band black
     }
    } 
  }
}

void NormalPeakLS(int band, int H, int S, int V) {
  int xStart = BAR_WIDTH * band;
  int peakHeight = TOP - peak[band] - 1;
  for (int x = xStart; x < xStart + BAR_WIDTH; x++) {
    matrix -> drawPixel(x, peakHeight, CHSV(H, S, V));
  }
}

//************ Mode 3 ***********

void purpleBarsLS(int band, int barHeight) {
  int xStart = BAR_WIDTH * band;
  for (int x = xStart; x < xStart + BAR_WIDTH; x++) {
    for (int y = TOP; y >= 0; y--) {
     if(y >= TOP - barHeight){
        matrix -> drawPixel(x, y, ColorFromPalette(purplePal, y * (255 / (barHeight + 1))));
     }
     else {
      matrix->drawPixel(x, y, CRGB(0, 0, 0)); // make unused pixel in a band black
     }
    } 
  }
}

// for peaks see mode 2

//************ Mode 4 ***********

void SameBarLS(int band, int barHeight) {
  int xStart = BAR_WIDTH * band;
  for (int x = xStart; x < xStart + BAR_WIDTH; x++) {
    for (int y = TOP; y >= 0; y--) {
     if(y >= TOP - barHeight){
        matrix -> drawPixel(x, y, CHSV(SameBar_Color1)); //blue
     }
     else {
      matrix->drawPixel(x, y, CRGB(0, 0, 0)); // make unused pixel in a band black
     }
    } 
  }
}
// for peaks see mode 2

//************ Mode 5 ***********
void SameBar2LS(int band, int barHeight) {
  int xStart = BAR_WIDTH * band;
  for (int x = xStart; x < xStart + BAR_WIDTH; x++) {
    for (int y = TOP; y >= 0; y--) {
     if(y >= TOP - barHeight){
        matrix -> drawPixel(x, y, CHSV(SameBar_Color2)); //blue
     }
     else {
      matrix->drawPixel(x, y, CRGB(0, 0, 0)); // make unused pixel in a band black
     }
    } 
  }
}
// for peaks see mode 2

//************ Mode 6 ***********
void centerBarsLS(int band, int barHeight) {
  int xStart = BAR_WIDTH * band;
  int center= TOP/2;
  for (int x = xStart; x < xStart + BAR_WIDTH; x++) {
    if (barHeight % 2 == 0) barHeight--;
    if (barHeight < 0) barHeight = 1; // at least a white line in the middle is what we want
    int yStart = ((kMatrixHeight - barHeight) / 2);
    for (int y = yStart; y <= (yStart + barHeight); y++) {
      int colorIndex = constrain((y - yStart) * (255 / barHeight), 0, 255);
      matrix -> drawPixel(x, y, ColorFromPalette(heatPal, colorIndex));
    }
    for (int y= barHeight/2;y<TOP;y++){
      matrix->drawPixel(x, center+y+1, CRGB(0, 0, 0)); // make unused pixel bottom black
      matrix->drawPixel(x, center-y-2, CRGB(0, 0, 0)); // make unused pixel bottom black
    }
    
  }
}

//************ Mode 7 ***********
void centerBars2LS(int band, int barHeight) {
  int xStart = BAR_WIDTH * band;
  int center= TOP/2;
  for (int x = xStart; x < xStart + BAR_WIDTH; x++) {
    if (barHeight % 2 == 0) barHeight--;
    if (barHeight < 0) barHeight = 1; // at least a white line in the middle is what we want
    int yStart = ((kMatrixHeight - barHeight) / 2);
    for (int y = yStart; y <= (yStart + barHeight); y++) {
      int colorIndex = constrain((y - yStart) * (255 / barHeight), 0, 255);
      matrix -> drawPixel(x, y, ColorFromPalette(markPal, colorIndex));
    }
    for (int y= barHeight/2;y<TOP;y++){
      matrix->drawPixel(x, center+y+1, CRGB(0, 0, 0)); // make unused pixel bottom black
      matrix->drawPixel(x, center-y-2, CRGB(0, 0, 0)); // make unused pixel bottom black
    }
    
  }
}

//************ Mode 8 ***********
void centerBars3LS(int band, int barHeight) {
  int xStart = BAR_WIDTH * band;
  int center= TOP/2;
  for (int x = xStart; x < xStart + BAR_WIDTH; x++) {
    if (barHeight % 2 == 0) barHeight--;
    if (barHeight < 0) barHeight = 1; // at least a white line in the middle is what we want
    int yStart = ((kMatrixHeight - barHeight) / 2);
    for (int y = yStart; y <= (yStart + barHeight); y++) {
      int colorIndex = constrain((y - yStart) * (255 / barHeight), 0, 255);
      matrix -> drawPixel(x, y, ColorFromPalette(markPal2, colorIndex));
    }
    for (int y= barHeight/2;y<TOP;y++){
      matrix->drawPixel(x, center+y+1, CRGB(0, 0, 0)); // make unused pixel bottom black
      matrix->drawPixel(x, center-y-2, CRGB(0, 0, 0)); // make unused pixel bottom black
    }
    
  }
}
//************ Mode 9 ***********
void BlackBarLS(int band, int barHeight) {
  int xStart = BAR_WIDTH * band;
  for (int x = xStart; x < xStart + BAR_WIDTH; x++) {
    for (int y = TOP; y >= 0; y--) {
     if(y >= TOP - barHeight){
        matrix->drawPixel(x, y, CRGB(0, 0, 0)); // make unused pixel in a band black
     }
     else {
      matrix->drawPixel(x, y, CRGB(0, 0, 0)); // make unused pixel in a band black
     }
    } 
  }
}

void outrunPeakLS(int band) {
  int xStart = BAR_WIDTH * band;
  int peakHeight = TOP - peak[band] - 1;
  for (int x = xStart; x < xStart + BAR_WIDTH; x++) {
    matrix -> drawPixel(x, peakHeight, ColorFromPalette(outrunPal, peakHeight * (255 / kMatrixHeight)));
  }
}

//************ Mode 10 ***********
void TriPeak2LS(int band) {
  int xStart = BAR_WIDTH * band;
  int peakHeight = TOP - peak[band] - 1;
  for (int x = xStart; x < xStart + BAR_WIDTH; x++) {
    if (peakHeight < 4) matrix -> drawPixel(x, peakHeight, CHSV(TriBar_Color_Top_Peak2)); //Top red
    else if (peakHeight > 8) matrix -> drawPixel(x, peakHeight, CHSV(TriBar_Color_Bottom_Peak2)); //green
    else matrix -> drawPixel(x, peakHeight, CHSV(TriBar_Color_Middle_Peak2)); //yellow
  }
}

//************ Mode 10 ***********
// for peaks see mode 1
#endif



/********************************************************************************************************************************
 * ** END SUB Rountines related to Paterns and Peaks                                                                           **
 ********************************************************************************************************************************/
