/*
 *      Tek Block letter XY display with spin effect
 *      Created 31 Mar 2013 by Alan Wolke
 *      uses PORTs and R-2R ladder - note Y limited to 0-63, 6-bit
 *      R2R time constant 2.7k*10n or 3.9k * 6.8n
 *      works well with scope set for 0.5V/div XY mode
 */


#define FIGURE_DELAY	100  // trace delay in uS. Adjust as desired.
#define NUM_POINTS	76   // number of XY points in figure


// x coords on port d
byte x_points[NUM_POINTS] = {	
  0,1,2,7,8,15,18,26,29,40,43,54,58,69,72,83,86,95,98,106,107,109,115,117,121,122,125,127,128,129,131,132,135,136,138,142,143,144,145,151,152,153,155,162,164,165,167,175,177,178,180,189,191,193,195,204,206,207,210,218,220,221,223,231,233,234,236,242,243,244,245,250,251,252,254,255
  };
// y coords on port b - limited to 0-63 with map function later
byte y_points[NUM_POINTS] = { 
   183,200,166,215,150,229,133,241,118,249,103,254,89,255,75,252,62,246,49,237,39,37,227,26,217,16,207,200,194,202,210,15,219,220,24,229,231,33,35,239,241,45,47,247,248,57,59,253,253,70,73,255,255,84,86,253,253,98,101,248,247,113,115,239,237,128,131,227,225,144,147,213,210,163,197,194
  };
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
