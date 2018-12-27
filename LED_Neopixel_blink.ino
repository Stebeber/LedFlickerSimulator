//Beispiel für WS2812B - LED-Band
//RGB-Farbwahl: https://www.sessions.edu/color-calculator/
// 

#include <Adafruit_NeoPixel.h>
#include <avr/power.h>;
 
#define PIN            12 //Output am Arduino
#define NUMPIXELS      30 //Anzahl der verketteten LEDS
 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//Register
bool state[NUMPIXELS];
 
//int delayval = 100;
 
void setup() 
{
  pixels.begin();
  Serial.begin(9600);
  Serial.print("Initialized");

  for(int i = 0; i < NUMPIXELS; i++)
  {
    state[i] = true;
    switch_light_on(i);
  }
}
 
void loop() 
{
  for(int i=0;i<NUMPIXELS;i++)
  {
    //Serial.print("Set " + i + " to: );    
    //pixels.setPixelColor(i, pixels.Color(get_rand_color(),get_rand_color(),get_rand_color()));
    //pixels.show(); // This sends the updated pixel color to the hardware.    
    //delay(delayval); // Delay for a period of time (in milliseconds).    
    //Serial.println();

    simulate_life(i);
    delay(100);
  }
}

void simulate_life(int index)
{
    int rand = random(0,100);
    if(rand == 0) //Anpassen auf Prozent der Lichtwechsel pro Loop
    {
      if(state[index] == true)
      {
        switch_light_off(index);
        state[index] = false;
      }
      else
      {
        switch_light_on(index);
        state[index] = true;
      }
    }
    //else do nothing
}

void switch_light_off(int index)
{
  pixels.setPixelColor(index,0,0,0);
  pixels.show();
}

void switch_light_on(int index)
{
  pixels.setPixelColor(index,255,172+get_random_offset(),68+get_random_offset(), 100+get_random_offset()); //Helligkeit!
  pixels.show();
}

int get_rand_color()
{
  int rand_n = random(0,256);
  //System.print(rand_n + " ");
  return rand_n;
}

int get_random_offset()
{
  int r = random(-60,+80);
  return r;
}
