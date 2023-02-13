/*
 *      Tek Block letter XY display with spin effect
 *      Created 31 Mar 2013 by Alan Wolke
 *      uses PORTs and R-2R ladder - note Y limited to 0-63, 6-bit
 *      R2R time constant 2.7k*10n or 3.9k * 6.8n
 *      works well with scope set for 0.5V/div XY mode
 */


#define FIGURE_DELAY	10  // trace delay in uS. Adjust as desired.
#define NUM_POINTS	101   // number of XY points in figure


// x coords on port d
byte x_points[NUM_POINTS] = {	
  128,128,129,131,135,142,151,162,175,189,204,218,231,242,250,254,255,252,245,236,223,210,195,180,167,155,145,138,132,129,128,128,128,127,125,122,117,109,98,86,72,58,43,29,18,8,2,0,1,7,15,26,40,54,69,83,95,106,115,121,125,127,127,128,128,129,131,136,143,152,164,177,191,206,220,233,243,251,255,255,251,244,234,221,207,193,178,165,153,144,136,132,129,128,128,128,127,125,121,115,107
  
  };
// y coords on port b - limited to 0-63 with map function later
byte y_points[NUM_POINTS] = { 
   194,196,201,209,219,229,239,247,253,255,253,248,239,227,213,197,180,163,147,131,115,101,86,73,59,47,35,24,15,8,3,0,0,3,9,16,26,37,49,62,75,89,103,118,133,150,166,183,200,215,229,241,249,254,255,252,246,237,227,217,207,200,195,194,196,202,210,220,231,241,248,253,255,253,247,237,225,210,194,177,161,144,128,113,98,84,70,57,45,33,23,14,7,2,0,1,4,10,18,28,39
 
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
