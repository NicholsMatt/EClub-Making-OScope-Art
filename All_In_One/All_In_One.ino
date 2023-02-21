 /*
 *      Tek Block letter XY display with spin effect
 *      Created 31 Mar 2013 by Alan Wolke
 *      uses PORTs and R-2R ladder - note Y limited to 0-63, 6-bit
 *      R2R time constant 2.7k*10n or 3.9k * 6.8n
 *      works well with scope set for 0.5V/div XY mode
 */
#include "ShapeDefinitions.h"
#include "Shape.h"


pinMode(A0, INPUT); //DIP Switch 0
pinMode(A1, INPUT); //DIP Switch 1
pinMode(A2, INPUT); //DIP Switch 2
pinMode(A3, INPUT); //DIP Switch 3
pinMode(A4, INPUT); //Spin/NoSpin Toggle

  byte a0 = 0;
  byte a1 = 0;
  byte a2 = 0;
  byte SpinNoSpin = 0;

// some initial starting values...                                      
byte x_min = 50;
byte x_max = 50;
byte x_mid = 50;
byte x_half;


#define FIGURE_DELAY	100  // trace delay in uS. Adjust as desired.
#define NUM_POINTS	38   // number of XY points in figure

// x coords on port d
byte x_points[NUM_POINTS] = {10, 90, 90, 110, 130, 140, 140, 90, 90, 97, 113, 120, 90, 90, 100, 150, 150, 170, 170, 195, 220, 190, 220, 195, 170, 170, 100, 85, 77, 70, 72, 80, 90, 60, 60, 40, 40, 10};

// y coords on port b - limited to 0-63 with map function later
byte y_points[NUM_POINTS] = {100, 100, 80, 82, 74, 60, 40, 40, 50, 60, 60, 50, 50, 40, 30, 30, 100, 100, 55, 80, 80, 45, 10, 10, 35, 10, 10, 13, 23, 40, 60, 72, 80, 80, 10, 10, 80, 80};




void setup(){
  DDRD = B11111111; //initialize PORTs for writing
  DDRB = B00111111;
}




void loop(){
  
  readInputs(a0, a1, a2, SpinNoSpin);
  writePattern(input);

  //Read inputs
  //
  
  delay(10);
}

void readInputs(byte &a0, byte &a1, byte &a2, byte &SpinNoSpin){
  a0 = digitalRead(A0);
  a1 = digitalRead(A1);
  a2 = digitalRead(A2);
  SpinNoSpin = digitalRead(A3);
}

void writePattern(){
  patternSetup(); //Run setup function
  
  byte t;
  byte sx;
  float p;
  byte flip;
  
  for(p=0; p<314; p++)
  {
    sx = ( sin(p/100) * x_half);                // half-sine for X scaling to simulate rotation
    for(t = 0; t < NUM_POINTS; t++)    // run through the X points
    {
      PORTD = map(x_points[t], x_min, x_max, x_mid-sx, x_mid+sx); // scale X with half-sine about mid point
      PORTB = y_points[t];
      delayMicroseconds(FIGURE_DELAY);    // wait FIGURE_DELAY microseconds
    }
  }
  flip = x_min; // flip X min and max values so next map is reversed
  x_min = x_max;
  x_max = flip;

}

void patternSetup(int NUM_POINTS, ){
  byte t;
  for(t = 0; t < NUM_POINTS; t++)
  {
    y_points[t] = map(y_points[t],0,255,0,63); //re-map Y points to 6 bits
  }

  for(t=0; t < NUM_POINTS; t++) //get min, max and mid values of X
  {
    x_min = min(x_min, x_points[t]);
    x_max = max(x_max, x_points[t]);
  }
  x_mid = (x_max + x_min)/2;
  x_half = (x_max - x_min)/2;
}
