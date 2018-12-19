#include <Arduino.h>
#include "variant.h"
#include "due_can.h"
#include <FastLED.h>

#define LED_PIN 7
#define NUM_LEDS 10
#define Serial SerialUSB

CRGB leds [NUM_LEDS];
CAN_FRAME incoming;

char LedLeiste[NUM_LEDS][3]={0};
 
void setup() {
  // put your setup code here, to run once:
 
 
    FastLED.addLeds<WS2812, LED_PIN, RGB>(leds, NUM_LEDS);

  // start serial port at 115200 bps:
  
    Serial.begin(115200);
    Can0.begin(CAN_BPS_250K);
    //Can0.watchFor();  
    //Can0.watchForRange(0x100,0x120);  
    //Can0.watchFor(0x10,0x12);  
    Can0.watchForRange(0x10,0x12);  // //Watch for a range of ids from 0x100 to 0x120
    Serial.println("Program Started");

    /*************LED Power on Self-Test*******/
    /*
    for(int k=0;k<NUM_LEDS;k++)
    {
      leds[k]=CRGB(255,0,0);
      FastLED.show();
      delay(50);
     }
     for(int k=0;k<NUM_LEDS;k++)
    {
      leds[k]=CRGB(0,0,0);
      FastLED.show();
      delay(50);
     }
*/
  
}
//-----------------------------------------------

  void Buffering(CAN_FRAME *)
 {
  // CAN_FRAME incoming;

      LedLeiste[incoming.data.byte[0]][0] = incoming.data.byte[1];
      LedLeiste[incoming.data.byte[0]][1] = incoming.data.byte[2];
      LedLeiste[incoming.data.byte[0]][2] = incoming.data.byte[3];
  } 
//----------------------------------------

void Message_Handling()
{

  switch (incoming.id)
  {
    case 0x10:
      LedLeiste[incoming.data.byte[0]][0] = incoming.data.byte[1];
      LedLeiste[incoming.data.byte[0]][1] = incoming.data.byte[2];
      LedLeiste[incoming.data.byte[0]][2] = incoming.data.byte[3];
      break;
     case 0x11:
      for(int k=0;k<NUM_LEDS;k++)
      {
        LedLeiste[k][0]=incoming.data.byte[0];
        LedLeiste[k][1]=incoming.data.byte[1];
        LedLeiste[k][2]=incoming.data.byte[2];
       }
      break;
    case 0x12:
    //case '0x12':
      if(incoming.data.byte[0]==1)
      {
        printData();  
       }
      break;
      
    default:
     // printData();
      break;
  }
  
 }
 

 void printData()
  { 
    for(int j=0 ; j<NUM_LEDS ; j++)
    {
      leds[j]=CRGB(LedLeiste[j][0],LedLeiste[j][1],LedLeiste[j][2]);
      FastLED.show(); 
    }
  }
  
 //-------------------------------------------------

void loop() 
{
  while(1)
  {
      // put your main code here, to run repeatedly:
   if (Can0.available() > 0) 
   {
      Can0.read(incoming);
      Message_Handling();
  }
    }

}

