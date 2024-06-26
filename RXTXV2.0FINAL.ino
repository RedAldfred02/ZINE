//ch1 and ch2 orientation and motion of car
//ch3 throttle gripper up down
//ch5 switch gripper open close
//ch6 mode switch


#include <string.h>
#define IBUS_BUFFSIZE 32   
#define IBUS_MAXCHANNELS 10 
#include <Servo.h>
static uint8_t ibusIndex = 0;
static uint8_t ibus[IBUS_BUFFSIZE] = {0};
static uint16_t rcValue[IBUS_MAXCHANNELS];
                  
static boolean rxFrameDone;
                  
int ch_width_1;int ch_width_2;int ch_width_3;int ch_width_4;int ch_width_5;int ch_width_6;int ch_width_7;int ch_width_8;int ch_width_9;int ch_width_10;
                  
Servo ch1;
Servo ch2;
Servo ch3;
Servo ch4;
Servo ch5;
Servo ch6;
Servo ch7;
Servo ch8;
Servo ch9;
Servo ch10;

                  
void setup()
{
  Serial.begin(115200);
  ch1.attach(2);
  ch2.attach(3);
  ch3.attach(4);
  ch4.attach(5);
  ch5.attach(6);
  ch6.attach(7);
  ch7.attach(8);
  ch8.attach(9);
  ch9.attach(10);
  ch10.attach(11);

  pinMode(4,OUTPUT); pinMode(5,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(9,OUTPUT);
  
  pinMode(6,OUTPUT); pinMode(8,OUTPUT);
}
                  
void loop()
{
  readRx();

                   
}
                  
void readRx()
{
  rxFrameDone = false;
                   
  if (Serial.available())
  {
    uint8_t val = Serial.read();
    // Look for 0x2040 as start of packet
    if (ibusIndex == 0 && val != 0x20)
    {
      ibusIndex = 0;
      return;
    }
    if (ibusIndex == 1 && val != 0x40)
    {
      ibusIndex = 0;
      return;
    }
                  
    if (ibusIndex == IBUS_BUFFSIZE)
    {
      ibusIndex = 0;
      int high=3;
      int low=2;
      for(int i=0;i<IBUS_MAXCHANNELS; i++)
      {
        rcValue[i] = (ibus[high] << 8) + ibus[low];
        high += 2;
        low += 2;
      }
      ch_width_1 = map(rcValue[0], 1000, 2000, 1000, 2000);
      ch1.writeMicroseconds(ch_width_1);
                  
      Serial.print(ch_width_1);
      Serial.print("     ");
                  
      ch_width_2 = map(rcValue[1], 1000, 2000, 1000, 2000);
      ch2.writeMicroseconds(ch_width_2);
                  
      Serial.print(ch_width_2);
      Serial.print("     ");
                  
      ch_width_3 = map(rcValue[2], 1000, 2000, 1000, 2000);
      ch3.writeMicroseconds(ch_width_3);
                  
      Serial.print(ch_width_3);
      Serial.print("     ");
                  
      ch_width_4 = map(rcValue[3], 1000, 2000, 1000, 2000);
      ch4.writeMicroseconds(ch_width_4);
                  
      Serial.print(ch_width_4);
      Serial.print("     ");
                                    
      ch_width_5 = map(rcValue[4], 1000, 2000, 1000, 2000);
      ch5.writeMicroseconds(ch_width_5);
                  
      Serial.print(ch_width_5);
      Serial.print("      ");
                  
      ch_width_6 = map(rcValue[5], 1000, 2000, 1000, 2000);
      ch6.writeMicroseconds(ch_width_6);
                  
      Serial.print(ch_width_6);
      Serial.print("      ");
                  
      ch_width_7 = map(rcValue[6], 1000, 2000, 1000, 2000);
      ch7.writeMicroseconds(ch_width_7);
                  
      Serial.print(ch_width_7);
      Serial.print("      ");
                       
                       
      ch_width_8 = map(rcValue[7], 1000, 2000, 1000, 2000);
      ch8.writeMicroseconds(ch_width_8);
      Serial.print(ch_width_8);
      Serial.print("     ");
                       
      ch_width_9 = map(rcValue[8], 1000, 2000, 1000, 2000);
      ch9.writeMicroseconds(ch_width_9);
                  
      Serial.print(ch_width_9);
      Serial.print("     ");
                  
      ch_width_10 = map(rcValue[9], 1000, 2000, 1000, 2000);
      ch10.writeMicroseconds(ch_width_10);
                  
      Serial.print(ch_width_10);
      Serial.println("     ");
                                                  
      rxFrameDone = true;
      return;
    }
      else
    {
      ibus[ibusIndex] = val;
      ibusIndex++;
    }
  }

  
  
    if ((ch_width_1>1450 && ch_width_1<1550)&&(ch_width_2>1450 && ch_width_2<1550))
    {     
      digitalWrite(4,LOW); digitalWrite(5,LOW);
      digitalWrite(6,LOW);digitalWrite(8,LOW);
      analogWrite(3,255);
      analogWrite(9,255);
    }
    else if((ch_width_1>1550))
    {     
      digitalWrite(4,HIGH); digitalWrite(5,LOW);
      digitalWrite(6,LOW);digitalWrite(8,HIGH);
      analogWrite(3,255); 
    }

    else if((ch_width_1<1450))
    {     
      digitalWrite(4,LOW); digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);digitalWrite(8,LOW);
      analogWrite(9,255);
    }


    else if((ch_width_2<1450))
    { 
      digitalWrite(4,LOW); digitalWrite(5,HIGH);
      digitalWrite(6,LOW);digitalWrite(8,HIGH);
      analogWrite(9,255);    
    }

    else if((ch_width_2>1550))
    {
      digitalWrite(4,HIGH); digitalWrite(5,LOW);
      digitalWrite(6,HIGH);digitalWrite(8,LOW);
      analogWrite(9,255);
    }

    else
    {     
      digitalWrite(4,LOW); digitalWrite(5,LOW);
      digitalWrite(6,LOW);digitalWrite(8,LOW);
      analogWrite(3,255);
      analogWrite(9,255);
    }

  
  
}

