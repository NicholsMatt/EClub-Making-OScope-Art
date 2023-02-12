/*
 *      Tek Block letter XY display with spin effect
 *      Created 31 Mar 2013 by Alan Wolke
 *      uses PORTs and R-2R ladder - note Y limited to 0-63, 6-bit
 *      R2R time constant 2.7k*10n or 3.9k * 6.8n
 *      works well with scope set for 0.5V/div XY mode
 */


#define FIGURE_DELAY	100  // trace delay in uS. Adjust as desired.
#define NUM_POINTS	23   // number of XY points in figure


//// x coords on port d
//byte x_points[NUM_POINTS] = {	
//  10, 90, 90, 110, 130, 140, 140,
//  90, 90, 97, 113, 120, 90, 90, 100,
//  150, 150, 170, 170,
//  195, 220, 190, 220, 195, 170,
//  170, 100, 85, 77, 70, 72, 80, 90,
//  60, 60, 40, 40, 10};
//
//// y coords on port b - limited to 0-63 with map function later
//byte y_points[NUM_POINTS] = { 
//  100, 100, 80, 82, 74, 60, 40, 40,
//  50, 60, 60, 50, 50, 40, 30, 30, 100, 
//  100, 55, 80, 80, 45, 10, 10,
//  35, 10, 10, 13, 23, 40, 60, 72, 80, 80,
//  10, 10, 80, 80};

//x coords
byte x_points[NUM_POINTS] = {  50,130,150,150,170,160,170,170,160,160,150,150,130,130,120,120,110,110,120,110,130,130,50 };

// y coords
byte y_points[NUM_POINTS] = {  180,180,160,130,130,75,80,70,70,50,50,70,70,50,50,70,70,80,80,130,130,160,160 };

// some initial starting values...                                      
byte x_min = 50;
byte x_max = 50;
byte x_mid = 50;
byte x_half;

void setup()
{
  DDRD = B11111111; //initialize PORTs for writing
  DDRB = B00111111;

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

void loop()
{
  byte t;
  byte sx;
  float p;
  byte flip;
  for(p=0; p<314; p++)
  {
    sx = ( sin(p/100) * x_half);                // half-sine for X scaling to simulate rotation
    for(t = 0; t < NUM_POINTS; t++)		// run through the X points
    {
      PORTD = map(x_points[t], x_min, x_max, x_mid-sx, x_mid+sx); // scale X with half-sine about mid point
      PORTB = y_points[t];
      delayMicroseconds(FIGURE_DELAY);		// wait FIGURE_DELAY microseconds
    }
  }
  flip = x_min; // flip X min and max values so next map is reversed
  x_min = x_max;
  x_max = flip;
}
