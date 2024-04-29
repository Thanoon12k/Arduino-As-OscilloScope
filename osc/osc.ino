#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
// 240 * 320
Adafruit_ILI9341 tft = Adafruit_ILI9341(8, 9, 11, 13, 10, 12);

// Maximum number of pixels to track. Adjust based on your screen size and sine wave amplitude.
const int MAX_PIXELS = tft.width(); // Assuming a 320x240 screen
int XPixels[1000];

 int amplitude = 40; // Adjust as needed
int frequency = 1; // Adjust as needed
int screen_width=240;
int screen_height=320;

int boxLeft=20;
int boxTop=20;
int boxWidth=200;
int boxHeight=200;
int centerX=boxLeft+ (boxWidth/2);
int centerY=boxTop+(boxHeight/2);

void setup() {
  Serial.begin(9600);
  Serial.println("Arduino ocilloscope START!"); 
  tft.begin();
tft.fillScreen(ILI9341_BLACK);
  Serial.print("Generated Sine Wave      Amplitude " + String(amplitude) + " V      Frequency " + String(frequency) + " Hz");

tft.drawRect(boxLeft, boxTop, boxWidth , boxHeight,  ILI9341_DARKGREEN);
tft.drawFastHLine(boxLeft,centerY,boxWidth,ILI9341_DARKGREEN);
tft.drawFastVLine(centerX,boxTop,boxHeight,ILI9341_BLUE);
Serial.println(tft.height());
Serial.println(tft.width());
 

}

void loop(void) {
drawSquareWave(boxLeft, 40, 30,ILI9341_YELLOW);
delay(10);
drawSquareWave(boxLeft, 40, 30,ILI9341_BLACK);
delay(10);
// static int xOffset = 0;
//  cleanOldSineWave();
//  drawSquareWave(xOffset, 40, 60);
// cleanOldSineWave();
//  drawSquareWave(xOffset, 40, 60);
// xOffset=xOffset+5;
// delay(50);

}
void ClearScreen() {
    tft.fillScreen(ILI9341_BLACK);
}


void cleanOldSineWave() {
 for (int i = boxLeft; i < boxWidth; i++) {
    tft.drawPixel(i, XPixels[i],ILI9341_BLACK );
 }
}


void drawSquareWave(int xOffset, int pulseWidth, int amplitude,uint16_t color) {
  int wavetop=centerY;
  for (int x = boxLeft; x < boxWidth; x=x+pulseWidth) {
    if (wavetop<centerY){
      wavetop=centerY;}
      else{
        wavetop=centerY-amplitude;
      }
    tft.drawFastHLine(x,wavetop,pulseWidth,color);
    tft.drawFastVLine(x+pulseWidth,centerY-amplitude,amplitude,color);
   }
}

void myDrawHLine(int16_t startx, int16_t y, int16_t width, uint16_t color){
 for (int x=startx; x<width;x++) {
 tft.drawPixel(x, y, color);
 XPixels[x]=y;
 }

}
void myDrawVLine(int16_t x, int16_t starty, int16_t width, uint16_t color){
for (int y=starty; y<width;y++) {
 tft.drawPixel(x, y, ILI9341_YELLOW);
 XPixels[x]=y;
 }

}
unsigned long drawMovingSineWave(int xOffset, int amplitude, int frequency) {
 unsigned long start = micros();

 int centerX = tft.width() / 2;
 int centerY = tft.height() / 2;
 for (int x = boxLeft; x < boxWidth; x++) {
    float radians = (x + xOffset) * 2 * PI / tft.width();
    int y = centerY + amplitude * sin(frequency * radians);
    tft.drawPixel(x, y, ILI9341_YELLOW);
    XPixels[x]=y;
   
 }

 return micros() - start;
}
