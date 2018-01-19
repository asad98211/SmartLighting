//////////////////////////////////////////////////////////////////////////Pin Connections/////////////////////////////////////////////////////////////////////////////////////
//    IR recieve pin =13                                                                                  //
//    I2C SDA pin = A4                                                              
//    I2C SCL pin =A5
//    RGB1 Red Pin = 11
//    RGB1 Green Pin=10
//    RGB1 Blue Pin=9
//    RGB2 Red Pin=6
//    RGB2 Green Pin=5
//    RGB2 Blue Pin=3
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>
int RECV_PIN = 13;
int room,color;
int RGB1Red= 11,RGB1Green=10,RGB1Blue=9;
int RGB2Red=6,RGB2Green=5,RGB2Blue=3;
int red,green,blue,intensity;
char arr[9][100]={"White","Yellow","Green","Cyan","Blue","Magenta","Red","Off"};
uint8_t zeroblock[8]  = {0xe, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0xe};
IRrecv irrecv(RECV_PIN);
decode_results results;
LiquidCrystal_I2C lcd(0x3F, 16, 2);
void setColor(){
  switch(room){
    case 1:
        analogWrite(RGB1Red,red);
        analogWrite(RGB1Green,green);
        analogWrite(RGB1Blue,blue);
        break;
    case 2:
        analogWrite(RGB2Red,red);
        analogWrite(RGB2Green,green);
        analogWrite(RGB2Blue,blue);
        break;
  }
}
void displayColor(){
    switch(color){
       case 0:
         lcd.clear();
         lcd.print("Room ");
         lcd.print(room);
         lcd.setCursor(0,1);
         lcd.print("Color White");
         red=255;
         green=255;
         blue=255;
         intensity=8;
         setColor();
         break;
       case 1:
         lcd.clear();
         lcd.print("Room ");
         lcd.print(room);
         lcd.setCursor(0,1);
         lcd.print("Color Yellow");
         red=255;
         green=255;
         blue=0;
         intensity=8;
         setColor();
         break;
       case 2:
         lcd.clear();
         lcd.print("Room ");
         lcd.print(room);
         lcd.setCursor(0,1);
         lcd.print("Color Red");
         red=255;
         green=0;
         blue=0;
         intensity=8;
         setColor();
         break;
       case 3:
         lcd.clear();
         lcd.print("Room ");
         lcd.print(room);
         lcd.setCursor(0,1);
         lcd.print("Color Green");
         red=0;
         green=255;
         blue=0;
         intensity=8;
         setColor();
         break;
       case 4:
         lcd.clear();
         lcd.print("Room ");
         lcd.print(room);
         lcd.setCursor(0,1);
         lcd.print("Color Cyan");
         red=0;
         green=255;
         blue=255;
         intensity=8;
         setColor();
         break;
       case 5:
         lcd.clear();
         lcd.print("Room ");
         lcd.print(room);
         lcd.setCursor(0,1);
         lcd.print("Color Blue");
         red=0;
         green=0;
         blue=255;
         intensity=8;
         setColor();
         break;
       case 6:
         lcd.clear();
         lcd.print("Room ");
         lcd.print(room);
         lcd.setCursor(0,1);
         lcd.print("Color Magenta");
         red=255;
         green=0;
         blue=255;
         intensity=8;
         setColor();
         break;
    }
}
void event(int x){
  static int flag1=1,flag2=1,value=0;
  int i;
  if(x==15328){
    room=1;
    lcd.clear();
    lcd.print("Room ");
    lcd.setCursor(0,1);
    lcd.print(room);
  }
  else if(x==15312){
    room=2;
    lcd.clear();
    lcd.print("Room 2");
    //lcd.setCursor(0,1);
   // lcd.print(room);
  }
  else if(x==15346){
    color++;
    color=color%7;
    displayColor();
  }
  else if(x==15324){
    color--;
    if(color==-1){
      color=6;
    }
    displayColor();
  }
  else if(x==15314){
    if(!flag1&&room==1){
      red=0;
      green=0;
      blue=0;
      intensity=0;
      setColor();
      lcd.clear();
      lcd.print("Room ");
      lcd.print(room);
      flag1=1;
      lcd.setCursor(0,1);
      lcd.print("Status=");
      lcd.print(arr[7]);
    }
    else if(flag1&&room==1){
      color=0;
      flag1=0;
      displayColor();
    }
    if(!flag2&&room==2){
      red=0;
      green=0;
      blue=0;
      intensity=0;
      setColor();
      lcd.clear();
      lcd.print("Room ");
      lcd.print(room);
      flag2=1;
      lcd.setCursor(0,1);
      lcd.print("Status=");
      lcd.print(arr[7]);
    }
    else if(flag2&&room==2){
      color=0;
      flag2=0;
      displayColor();
    }
  }
  else if(x==15298){
    if(intensity<8){
      intensity++;
      if(red){
        red+=32;
        constrain(red,0,255);
      }
      if(green){
        green+=32;
        constrain(green,0,255);
      }
      if(red){
        blue+=32;
        constrain(blue,0,255);
      }
      }
      constrain(intensity,0,8);
      setColor();
      lcd.clear();
      lcd.print("Intensity");
      lcd.setCursor(0,1);
      //lcd.print(intensity);/*
      for(i=0;i<intensity;i++){
        lcd.write(0);
        lcd.write(0);
      }
  }
  else if(x==15306){
    if(intensity>0){
      intensity--;
      if(red){
        red-=32;
        constrain(red,0,255);
      }
      if(green){
        green-=32;
        constrain(green,0,255);
      }
      if(red){
        blue-=32;
        constrain(blue,0,255);
      }
      
    }
    setColor();
    lcd.clear();
    lcd.print("Intensity");
    lcd.setCursor(0,1);
    constrain(intensity,0,8);
    //lcd.print(intensity);/*
    for(i=0;i<intensity;i++){
      lcd.write(0);
      lcd.write(0);
    }
  }
//  lcd.print(x);

}
void setup() {
  pinMode(RGB1Red,OUTPUT);
  pinMode(RGB1Green,OUTPUT);
  pinMode(RGB1Blue,OUTPUT);
  pinMode(RGB2Green,OUTPUT);
  pinMode(RGB2Red,OUTPUT);
  pinMode(RGB2Blue,OUTPUT);
  lcd.begin();
  lcd.backlight();
  lcd.createChar(0, zeroblock);
  lcd.home();
  lcd.print("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  delay(1000);
  lcd.clear();
  lcd.println("Ready.");
}

void loop(){
  lcd.setCursor(0, 1);
  if (irrecv.decode(&results)){
    event(results.value);
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}
