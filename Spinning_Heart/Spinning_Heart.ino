/*
 *      Tek Block letter XY display with spin effect
 *      Created 31 Mar 2013 by Alan Wolke
 *      uses PORTs and R-2R ladder - note Y limited to 0-63, 6-bit
 *      R2R time constant 2.7k*10n or 3.9k * 6.8n
 *      works well with scope set for 0.5V/div XY mode
 */


#define FIGURE_DELAY	100  // trace delay in uS. Adjust as desired.
#define NUM_POINTS	22   // number of XY points in figure


// x coords on port d
byte x_points[NUM_POINTS] = {	
  50, 75, 100, 125, 150, 175, 200, 210, 210, 195,
  175, 165, 155, 135, 125, 110, 100, 90, 70, 50,
  40, 40};

// y coords on port b - limited to 0-63 with map function later
byte y_points[NUM_POINTS] = { 
  180, 175, 150, 125, 150, 175, 180, 170, 150, 130,
  100, 70, 50, 30, 5, 30, 50, 70, 100, 130, 150, 170};

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
