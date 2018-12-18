#include <Arduino.h>
#include "variant.h"
#include "due_can.h"

CAN_FRAME myframe[3];
//bool flag=1;

void Frame_Init()
{
   myframe[0].id = 0x10;
   myframe[0].length = 4;
   myframe[0].data.byte[0] = 4;
   myframe[0].data.byte[1] = 50;
   myframe[0].data.byte[2] = 50;
   myframe[0].data.byte[3] = 50;  
   
   myframe[1].id = 0x11;
   myframe[1].length = 3;
   myframe[1].data.byte[0] = 150;
   myframe[1].data.byte[1] = 150;
   myframe[1].data.byte[2] = 150;

   myframe[2].id = 0x12;
   myframe[2].length = 1;
   myframe[2].data.byte[0] = 1;
}

void setup() {
  // put your setup code here, to run once:
  
    Frame_Init();     //Parameter initialisieren
    
  // start serial port at 115200 bps:
   Serial.begin(115200);
   Can0.begin(CAN_BPS_250K);
   Can0.watchFor();  
  Serial.println("Program Started");
}

void sendData(CAN_FRAME frame)
{
  CAN_FRAME outgoing;
  int i;

  outgoing.id = frame.id;
  outgoing.length = frame.length;
  for(int i=0;i<frame.length;i++)
  {
    outgoing.data.byte[i] = frame.data.byte[i];  
  }
    Can0.sendFrame(outgoing);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(1)
  {
    for(int g=0; g<2; g++)
    {
     sendData(myframe[g]); 
     delay(100);
     sendData(myframe[2]); 
     delay(100);
    }
    delay(200);
  }
}








