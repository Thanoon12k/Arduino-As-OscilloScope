#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(51, 50, 52, 53, 48, 49); // CS, WR-DC, SDI, SCL, RST, NONE-D/C



int boxLeft=20;
int boxTop=20;
int boxWidth=200;
int boxHeight=200;
int centerX=boxLeft+ (boxWidth/2);
int centerY=boxTop+(boxHeight/2);
int x=boxLeft;
int prevY = centerY; // Initial y-coordinate for the first line segment

void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
  Serial.println("Arduino ocilloscope START!"); 
  tft.begin();
  tft.fillScreen(ILI9341_BLACK);
drawPlotBox();
displayText();

}

void loop(void) {
drawInpuwave(); // Call the function to draw the A0 value on the screen
 delay(5); 
 
}
void drawInpuwave() {
 int r = analogRead(A0); // Read the analog value from A0
 int mappedValue = map(r, 0, 1023, 0, boxHeight); // Map the value to the box's height
 int y = centerY - ((mappedValue / 2)); // Calculate the y-coordinate, adjusting for the center of the box
 tft.drawLine(x - 1, prevY+boxTop, x, y+boxTop, ILI9341_YELLOW);
 prevY = y;
 x++;

if (x>=boxLeft+boxWidth)
{ 
  tft.fillRect(boxLeft, boxTop, boxWidth, centerY+10, ILI9341_BLACK);

drawPlotBox();
 x = boxLeft; // Reset the x-coordinate to the start of the box
 prevY = centerY; 
}

}

void drawPlotBox(){

tft.drawRect(boxLeft, boxTop, boxWidth , boxHeight,  ILI9341_DARKGREEN);
tft.drawFastHLine(boxLeft,centerY,boxWidth,ILI9341_BLUE);
tft.drawFastVLine(centerX,boxTop,boxHeight,ILI9341_BLUE);
}

void displayText() {
  tft.setCursor(boxLeft,boxTop+boxHeight+20 ); tft.setTextColor(ILI9341_YELLOW);  tft.setTextSize(2);  tft.println(" OSCilloScope ");
  tft.setCursor(0, boxTop+boxHeight+60); tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(1);  tft.println("...............");
  tft.setCursor(0, boxTop+boxHeight+80); tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(1);  tft.println(".............");
 
}