#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0); 


#include <Keypad.h>

#define role 13             

          
String sifre="0101";
String girilen="";
int buzzer=10;
int hane = 8;

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns


char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {8, 7, 6, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup(){
  
 pinMode(role, OUTPUT);    
 pinMode(buzzer,OUTPUT); 
 pinMode(11,OUTPUT);
 pinMode(12,OUTPUT);
 Wire.begin();
 u8g2.begin();

  
  
}

void loop(){
  
  digitalWrite(role,HIGH);  
  char basilan=keypad.getKey();
  if (basilan!= NO_KEY)
  {
      if(basilan=='#')
        {
              if(girilen==sifre)
              {u8g2.clearBuffer();         
   u8g2.setFont(u8g2_font_BitTypeWriter_tr); 
   u8g2.drawStr(4,29,"Dogru");
   u8g2.sendBuffer();        
  
                digitalWrite(role,LOW); 
                digitalWrite(11,LOW); 
                digitalWrite(12,HIGH); 
                delay(3000);
                analogWrite(buzzer,240);
                delay(100);
                analogWrite(buzzer,200);
                delay(100);
                analogWrite(buzzer,180);
                delay(100);
                analogWrite(buzzer,250);
                delay(100);
                analogWrite(buzzer,LOW); 
                for(int i=0;i<16;i++)
                  {
                 u8g2.clearBuffer();   
        u8g2.drawStr(4,29," "); 
   u8g2.sendBuffer(); 
 
                  
                  }
                  girilen="";
                  hane=8;
                  delay(1000);
                  digitalWrite(12,LOW); 
                }
              
               else if(girilen!=sifre)
              {
               u8g2.clearBuffer();        
   u8g2.setFont(u8g2_font_logisoso28_tr); 
   u8g2.drawStr(4,29,"Hatali"); 
   u8g2.sendBuffer();       
   delay(2000);
                digitalWrite(role,HIGH);

                digitalWrite(12,LOW); 
                 digitalWrite(11,HIGH); 
                analogWrite(buzzer,150);
                delay(1000);
                analogWrite(buzzer,LOW);
                for(int i=0;i<16;i++)
                {
                  u8g2.clearBuffer(); 
                   u8g2.drawStr(4,29," ");  
   u8g2.sendBuffer(); // clear the internal memory
  
                  
                  }
                  girilen="";
                  hane=8;
                  digitalWrite(11,LOW); 
                 digitalWrite(12,LOW); 
                }   
  
        }

    else{
   
   


   u8g2.setFont(u8g2_font_logisoso28_tr);  
   u8g2.drawStr(hane,40,"*"); 
   u8g2.sendBuffer();      
   
    girilen=girilen+basilan;
    hane=hane+15;
  
        }
    }

}
