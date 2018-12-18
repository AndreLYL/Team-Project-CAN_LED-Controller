#include <Arduino.h>
#include "variant.h"
#include "due_can.h"

#define NUM_LEDS 10
char Color[5][3] = { {0, 255, 0},     //Green: Evething is fine
                     {255, 0, 0},     //Red:   You should stop
                     {0, 0, 255},     //Blue:  Someone in the overhead
                     {255,255,0},     //Yellow:Take care       
                     {0, 0, 0}       //OFF:           
                    };

CAN_FRAME myframe[3];

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

void Application_Demo()
{
  /**********系统正常**********/
  for(int j=0; j < 3; j++){
  for(int i=0; i < 3; i++){
    myframe[1].data.byte[i] = Color[0][i];
  }
  sendData(myframe[1]); 
  myframe[2].data.byte[0] = 1;
  sendData(myframe[2]); 
  delay(1000);
  delay(1000);
  for(int i=0; i < 3; i++){
    myframe[1].data.byte[i] = Color[4][i];
  }
  sendData(myframe[1]); 
  myframe[2].data.byte[0] = 0;
  sendData(myframe[2]); 
  delay(1000);
  delay(1000);
  }
  //延时
  delay(1000);  delay(1000);  delay(1000);  delay(1000);
  /*************系统故障****************/
  for(int j=0; j < 10; j++){
  for(int i=0; i < 3; i++){
    myframe[1].data.byte[i] = Color[1][i];
  }
  sendData(myframe[1]); 
  myframe[2].data.byte[0] = 1;
  sendData(myframe[2]); 
  delay(1000);
  delay(1000);
  for(int i=0; i < 3; i++){
    myframe[1].data.byte[i] = Color[4][i];
  }
  sendData(myframe[1]); 
  myframe[2].data.byte[0] = 0;
  sendData(myframe[2]); 
  delay(1000);
  delay(1000);
  }
  //延时
  delay(1000);  delay(1000);  delay(1000);  delay(1000);
  /*************正常状态****************/
  for(int i=0; i < 3; i++){
    myframe[1].data.byte[i] = Color[0][i];
  }
  sendData(myframe[1]); 
  myframe[2].data.byte[0] = 1;
  sendData(myframe[2]); 
  delay(1000);
  delay(1000);

  //延时
  delay(1000);  delay(1000);  delay(1000);  delay(1000);
  /*************左侧有障碍****************/
    for(int i=0; i < NUM_LEDS/3; i++){
    myframe[0].data.byte[0] = i;
    myframe[0].data.byte[1] = Color[3][0];
    myframe[0].data.byte[2] = Color[3][1];
    myframe[0].data.byte[3] = Color[3][2]; 
  }
  sendData(myframe[1]); 
  myframe[2].data.byte[0] = 1;
  sendData(myframe[2]); 
  delay(1000);
  delay(1000);
  
  //延时
  delay(1000);  delay(1000);  delay(1000);  delay(1000);
  /*************右侧有障碍****************/
  for(int i=0; i < NUM_LEDS/3; i++){
    myframe[0].data.byte[0] = (NUM_LEDS/3*2)+i;
    myframe[0].data.byte[1] = Color[3][0];
    myframe[0].data.byte[2] = Color[3][1];
    myframe[0].data.byte[3] = Color[3][2]; 
  }
  sendData(myframe[1]); 
  myframe[2].data.byte[0] = 1;
  sendData(myframe[2]); 
  delay(1000);
  delay(1000);
  
  //延时
  delay(1000);  delay(1000);  delay(1000);  delay(1000);
  /*************正前方有障碍****************/
    for(int i=0; i < NUM_LEDS/3+1; i++){
    myframe[0].data.byte[0] = (NUM_LEDS/3-1)+i;
    myframe[0].data.byte[1] = Color[3][0];
    myframe[0].data.byte[2] = Color[3][1];
    myframe[0].data.byte[3] = Color[3][2]; 
  }
  sendData(myframe[1]); 
  myframe[2].data.byte[0] = 1;
  sendData(myframe[2]); 
  delay(1000);
  delay(1000);
  
  //延时
  delay(1000);  delay(1000);  delay(1000);  delay(1000);
}


void loop() {
  // put your main code here, to run repeatedly:
  while(1)
  {
    /*
    for(int g=0; g<2; g++)
    {
     sendData(myframe[g]); 
     delay(100);
     sendData(myframe[2]); 
     delay(100);
    }
    */

    Application_Demo();
    delay(200);
  }
}








