#include <Debounce.h>


//Stroudsburg PA KLUES Escape Room Cake puzzle
//
//------------------------------------2016 Sigmaz

#include "FastLED.h"
FASTLED_USING_NAMESPACE
#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define LOCK_PIN    13    // Pin to control the lock
#define DATA_PIN0   3
#define DATA_PIN1   4
#define DATA_PIN2   5
#define DATA_PIN3   6
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS   1

CRGB candle0[NUM_LEDS];
CRGB candle1[NUM_LEDS];
CRGB candle2[NUM_LEDS];
CRGB candle3[NUM_LEDS];
#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120


///end LED defines---------------------------

//--Setup Password stuff
#include <Password.h>
Password password = Password( "1234" );
#define PW_PIN0   8
#define PW_PIN1   9
#define PW_PIN2   10
#define PW_PIN3   11
int pwtry = 0;
int PW0L = 0; //password lock registers
int PW1L = 0;
int PW2L = 0;
int PW3L = 0;

//---End PW stuff--------------

//Pin debouncer setup----------
Debounce PW0 = Debounce( 20 , PW_PIN0 ); 
Debounce PW1 = Debounce( 20 , PW_PIN1 ); 
Debounce PW2 = Debounce( 20 , PW_PIN2 ); 
Debounce PW3 = Debounce( 20 , PW_PIN3 ); 
//-----------------------------


void setup()                    // run once, when the sketch starts
 
//start LED setup----------------------------
{

  Serial.begin(9600);
  Serial.println("'Blow out the candles' puzzle lock 2016 -Sigmaz@gmail.com(Jon Bruno)");
  Serial.println("sequence is simply 0-1-2-3");
  Serial.println("---PINOUTS--- ");
  Serial.println("LED_DATA0 - Pin D3        PW_PIN0 - Pin D8");
  Serial.println("LED_DATA1 - Pin D4        PW_PIN1 - Pin D9");
  Serial.println("LED_DATA2 - Pin D5        PW_PIN2 - Pin D10");
  Serial.println("LED_DATA3 - Pin D6        PW_PIN3 - Pin D11");
  Serial.println("LOCK_PIN - Pin D13");
  Serial.println("");
  Serial.println("Each candle has 1 WS2812B LED and a modified knock sensor. ");
  Serial.println("4 flickering (WS2812b) candles, Blown out in order trigger unlock event on D13.");
  Serial.println("In this project use 4 cheap digital knock sensors, remove the spring trigger");
  Serial.println("and install an electret MIC element. When the player blows on the element it should trigger the sensor.");
  Serial.println("sensitivity can be adjusted to eliminate false triggers by ambient noise");
  Serial.println("");
  
  
  
  delay(3000); // 3 second delay for recovery
//Button setup
  pinMode(LOCK_PIN, OUTPUT);      // sets the digital pin as output
  pinMode(PW_PIN0, INPUT_PULLUP);
  pinMode(PW_PIN1, INPUT_PULLUP);
  pinMode(PW_PIN2, INPUT_PULLUP);
  pinMode(PW_PIN3, INPUT_PULLUP);
   
// tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN0,COLOR_ORDER>(candle0, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE,DATA_PIN1,COLOR_ORDER>(candle1, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE,DATA_PIN2,COLOR_ORDER>(candle2, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE,DATA_PIN3,COLOR_ORDER>(candle3, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);





  
//end LED setup------------------------------  



}
uint8_t gHue = 0; // rotating "base color" used by many of the patterns


void loop()                     // run over and over again
{ 

   EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
   LockIt();
   LightCandles();
   PwCollect();
    
   
  // send the data out to the actual LEDS
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

}

void LockIt()
{
digitalWrite(LOCK_PIN,LOW);   // sets the LED off. See "Unlock"
}
void Unlock()
{
digitalWrite(LOCK_PIN,HIGH);// sets the LED on, in mock up. On=unlocked  
 delay(5000);
   reLightCandles();
}



//led stuff--------------------------

void FlickerOut0()
{

   
  FastLED.setBrightness(96);
  fill_solid(candle0, NUM_LEDS, CRGB::Orange);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(56);
  fill_solid(candle0, NUM_LEDS, CRGB::Orange);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(76);
  fill_solid(candle0, NUM_LEDS, CRGB::Orange);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(46);
  fill_solid(candle0, NUM_LEDS, CRGB::Orange);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(66);
  fill_solid(candle0, NUM_LEDS, CRGB::Orange);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(36);
  fill_solid(candle0, NUM_LEDS, CRGB::Orange);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(26);
  fill_solid(candle0, NUM_LEDS, CRGB::Orange);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(255);
  fill_solid(candle0, NUM_LEDS, CRGB::Black);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(BRIGHTNESS);
}
void FlickerOut1()
{

   
  FastLED.setBrightness(96);
  fill_solid(candle1, NUM_LEDS, CRGB::Orange);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(56);
  fill_solid(candle1, NUM_LEDS, CRGB::Orange);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(76);
  fill_solid(candle1, NUM_LEDS, CRGB::Orange);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(46);
  fill_solid(candle1, NUM_LEDS, CRGB::Orange);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(66);
  fill_solid(candle1, NUM_LEDS, CRGB::Orange);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(36);
  fill_solid(candle1, NUM_LEDS, CRGB::Orange);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(26);
  fill_solid(candle1, NUM_LEDS, CRGB::Orange);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(255);
  fill_solid(candle1, NUM_LEDS, CRGB::Black);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(BRIGHTNESS);
}

void FlickerOut2()
{

   
  FastLED.setBrightness(96);
  fill_solid(candle2, NUM_LEDS, CRGB::Orange);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(56);
  fill_solid(candle2, NUM_LEDS, CRGB::Orange);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(76);
  fill_solid(candle2, NUM_LEDS, CRGB::Orange);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(46);
  fill_solid(candle2, NUM_LEDS, CRGB::Orange);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(66);
  fill_solid(candle2, NUM_LEDS, CRGB::Orange);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(36);
  fill_solid(candle2, NUM_LEDS, CRGB::Orange);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(26);
  fill_solid(candle2, NUM_LEDS, CRGB::Orange);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(255);
  fill_solid(candle2, NUM_LEDS, CRGB::Black);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(BRIGHTNESS);
}

void FlickerOut3()
{

   
  FastLED.setBrightness(96);
  fill_solid(candle3, NUM_LEDS, CRGB::Orange);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(56);
  fill_solid(candle3, NUM_LEDS, CRGB::Orange);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(76);
  fill_solid(candle3, NUM_LEDS, CRGB::Orange);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(46);
  fill_solid(candle3, NUM_LEDS, CRGB::Orange);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(66);
  fill_solid(candle3, NUM_LEDS, CRGB::Orange);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(36);
  fill_solid(candle3, NUM_LEDS, CRGB::Orange);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(26);
  fill_solid(candle3, NUM_LEDS, CRGB::Orange);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(255);
  fill_solid(candle3, NUM_LEDS, CRGB::Black);
  FastLED.show();
  delay(50);
  FastLED.setBrightness(BRIGHTNESS);
}



void LightCandles() 
{
    if (PW0L == 1){
      fill_solid(candle0, NUM_LEDS, CRGB::Black);
    }else{
      fill_rainbow( candle0, NUM_LEDS, gHue, 7);
      addGlitterToCandle0(5);
         }
     
    if (PW1L == 1){
      fill_solid(candle1, NUM_LEDS, CRGB::Black);
    }else{
      fill_rainbow( candle1, NUM_LEDS, gHue + 64 , 7);
      addGlitterToCandle1(5);
         }
    
    if (PW2L == 1){
      fill_solid(candle2, NUM_LEDS, CRGB::Black);
    }else{
      fill_rainbow( candle2, NUM_LEDS, gHue + 128 , 7);
      addGlitterToCandle2(5);
         }
    
    if (PW3L == 1){
      fill_solid(candle3, NUM_LEDS, CRGB::Black);
    }else{
      fill_rainbow( candle3, NUM_LEDS, gHue + 191 , 7);
      addGlitterToCandle3(5);
         }
 
  }


void addGlitterToCandle0( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    candle0[ random16(NUM_LEDS) ] += CRGB::Red;
     }
}

void addGlitterToCandle1( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    candle1[ random16(NUM_LEDS) ] += CRGB::Red;
     }
}
void addGlitterToCandle2( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    candle2[ random16(NUM_LEDS) ] += CRGB::Red;
     }
}
void addGlitterToCandle3( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    candle3[ random16(NUM_LEDS) ] += CRGB::Red;
     }
}

void correctPW() 

{
  fill_solid(candle0, NUM_LEDS, CRGB::Black);
  fill_solid(candle1, NUM_LEDS, CRGB::Black);
  fill_solid(candle2, NUM_LEDS, CRGB::Black);
  fill_solid(candle3, NUM_LEDS, CRGB::Black);
  FastLED.show();
  delay (1000);
  FastLED.setBrightness(255);
  fill_solid(candle0, NUM_LEDS, CRGB::Green);
  fill_solid(candle1, NUM_LEDS, CRGB::Green);
  fill_solid(candle2, NUM_LEDS, CRGB::Green);
  fill_solid(candle3, NUM_LEDS, CRGB::Green);
  FastLED.show();
  delay(3000);
  FastLED.setBrightness(BRIGHTNESS);
  Unlock();
}  
void incorrectPW() 

{
  fill_solid(candle0, NUM_LEDS, CRGB::Black);
  fill_solid(candle1, NUM_LEDS, CRGB::Black);
  fill_solid(candle2, NUM_LEDS, CRGB::Black);
  fill_solid(candle3, NUM_LEDS, CRGB::Black);
  FastLED.show();
  delay (1000);
  FastLED.setBrightness(255);
  fill_solid(candle0, NUM_LEDS, CRGB::Red);
  fill_solid(candle1, NUM_LEDS, CRGB::Red);
  fill_solid(candle2, NUM_LEDS, CRGB::Red);
  fill_solid(candle3, NUM_LEDS, CRGB::Red);
  FastLED.show();
  delay(3000);
  FastLED.setBrightness(BRIGHTNESS);

}  





void PwCollect()  {
//Serial.println(pwtry);
if (pwtry == 4){
  checkPassword();

  
}else{
    PW0.update();
    PW1.update();
    PW2.update();
    PW3.update();

if (PW0.read()==LOW){
  if (PW0L == 0) {
password.append('1');
pwtry++;
FlickerOut0();
PW0L=1;
  }
}

if (PW1.read()==LOW){
  if (PW1L == 0) {
password.append('2');
pwtry++;
FlickerOut1();
PW1L=1;
  }
}
if (PW2.read()==LOW){
  if (PW2L == 0) {
password.append('3');
pwtry++;
FlickerOut2();
PW2L=1;
  }
}
if (PW3.read()==LOW){
  if (PW3L == 0) {
password.append('4');
pwtry++;
FlickerOut3();
PW3L=1;
  }
}

}


/*
//Fordebugging purposes only
Serial.print("Pins: ");
Serial.print (PW0.read());
Serial.print (PW1.read());
Serial.print (PW2.read());
Serial.print (PW3.read());
Serial.print (" locks: ");
Serial.print (PW0L);
Serial.print (PW1L);
Serial.print (PW2L);
Serial.print (PW3L);
Serial.print (" loop: ");
Serial.println(pwtry);
*/

  
}

void checkPassword(){
  if (password.evaluate()){
    Serial.println("Success");
    //Add code to run if it works
  correctPW();
  pwtry=0;//Reset all the registers for next use.
  PW0L=0;
  PW1L=0;
  PW2L=0;
  PW3L=0;
  password.reset();
 
    
  }else{
    Serial.println("Wrong");
  incorrectPW();
  pwtry=0;//Reset all the registers and try again...
  PW0L=0;
  PW1L=0;
  PW2L=0;
  PW3L=0;
  password.reset();
  reLightCandles();
   }
}


void reLightCandles()
{
  
  fill_solid(candle0, NUM_LEDS, CRGB::White);
  FastLED.show();
  delay(20);
  
  fill_solid(candle0, NUM_LEDS, CRGB::Black);
  fill_solid(candle1, NUM_LEDS, CRGB::Black);
  fill_solid(candle2, NUM_LEDS, CRGB::Black);
  fill_solid(candle3, NUM_LEDS, CRGB::Black);
  FastLED.show();
  delay (10);
  
  fill_solid(candle0, NUM_LEDS, CRGB::White);
  fill_solid(candle1, NUM_LEDS, CRGB::White);
  fill_solid(candle2, NUM_LEDS, CRGB::White);
  fill_solid(candle3, NUM_LEDS, CRGB::White);
  FastLED.show();
  delay(10);
  
  fill_solid(candle0, NUM_LEDS, CRGB::Black);
  fill_solid(candle1, NUM_LEDS, CRGB::Black);
  fill_solid(candle2, NUM_LEDS, CRGB::Black);
  fill_solid(candle3, NUM_LEDS, CRGB::Black);
  FastLED.show();
  delay(20);
  
  fill_solid(candle0, NUM_LEDS, CRGB::White);
  fill_solid(candle1, NUM_LEDS, CRGB::White);
  fill_solid(candle2, NUM_LEDS, CRGB::White);
  fill_solid(candle3, NUM_LEDS, CRGB::White);
  FastLED.show();
  delay(20);
  
  fill_solid(candle0, NUM_LEDS, CRGB::Black);
  fill_solid(candle1, NUM_LEDS, CRGB::Black);
  fill_solid(candle2, NUM_LEDS, CRGB::Black);
  fill_solid(candle3, NUM_LEDS, CRGB::Black);
  FastLED.show();
  delay (20);
  
  fill_solid(candle0, NUM_LEDS, CRGB::White);
  fill_solid(candle1, NUM_LEDS, CRGB::White);
  fill_solid(candle2, NUM_LEDS, CRGB::White);
  fill_solid(candle3, NUM_LEDS, CRGB::White);
  FastLED.show();
  delay(30);
  
  fill_solid(candle0, NUM_LEDS, CRGB::Black);
  fill_solid(candle1, NUM_LEDS, CRGB::Black);
  fill_solid(candle2, NUM_LEDS, CRGB::Black);
  fill_solid(candle3, NUM_LEDS, CRGB::Black);
  FastLED.show();
  delay(50);
  
  fill_solid(candle0, NUM_LEDS, CRGB::White);
  fill_solid(candle1, NUM_LEDS, CRGB::White);
  fill_solid(candle2, NUM_LEDS, CRGB::White);
  fill_solid(candle3, NUM_LEDS, CRGB::White);
  FastLED.show();
  delay(30);
  
  fill_solid(candle0, NUM_LEDS, CRGB::Black);
  fill_solid(candle1, NUM_LEDS, CRGB::Black);
  fill_solid(candle2, NUM_LEDS, CRGB::Black);
  fill_solid(candle3, NUM_LEDS, CRGB::Black);
  FastLED.show();
  delay(10);
  
  fill_solid(candle0, NUM_LEDS, CRGB::White);
  fill_solid(candle1, NUM_LEDS, CRGB::White);
  fill_solid(candle2, NUM_LEDS, CRGB::White);
  fill_solid(candle3, NUM_LEDS, CRGB::White);
  FastLED.show();
  delay(20);
  
  fill_solid(candle0, NUM_LEDS, CRGB::Black);
  fill_solid(candle1, NUM_LEDS, CRGB::Black);
  fill_solid(candle2, NUM_LEDS, CRGB::Black);
  fill_solid(candle3, NUM_LEDS, CRGB::Black);
  FastLED.show();
  LightCandles(); 
}
