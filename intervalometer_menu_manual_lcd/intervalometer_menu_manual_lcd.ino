/*
  LiquidCrystal Library - Hello World
 
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the 
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
 This sketch prints "Hello World!" to the LCD
 and shows the time.
 
 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7,8,9,10,11,12);

#define B_UP 1
#define B_RIGHT 2
#define B_DOWN 3
#define B_LEFT 4
#define B_SELECT 5

#define M_INTERVAL 1
#define M_IMAGES 2
#define M_START 3

#define S_INTERVAL 4
#define S_IMAGES  5

#define D_STATUS  6


int key_in;
int state;
byte arrow[8] = {
  B00000,
  B00000,
  B01000,
  B01100,
  B01110,
  B01100,
  B01000,
  B00000
};

byte updown[8] = {
  B00100,
  B01110,
  B11111,
  B00000,
  B00000,
  B11111,
  B01110,
  B00100
  };

  int interval;
  int images;

void setup() {
  // set up the LCD's number of columns and rows: 
  key_in = 0;
  interval =1;
  images = 0;
  lcd.begin(16, 2);  
  lcd.createChar(0, arrow);
  lcd.createChar(1, updown);
  state = M_INTERVAL;
  Serial.begin(9600);
}

void loop() {
  key_in = analogRead(0); // read the value from the sensor
  int key = get_key(key_in);
   
 lcd.clear();
  switch(state){
    case M_INTERVAL:
      drawLine(1, "Interval", interval,  0, 0); 
      drawLine(0, "Images", images,  0, 1); 
      switch(key){
        case B_DOWN:
          state = M_IMAGES;
          break;
        case B_RIGHT:
          state = S_INTERVAL;
          break;
      }
      key = 0;
      break;
    case M_IMAGES:
      
      drawLine(0, "Interval", interval, 0,0);
      drawLine(1, "Images", images, 0,1);
      
      switch(key){
        case B_UP:
          state = M_INTERVAL;
          break;
        case B_RIGHT:
          state = S_IMAGES;
          break;
        case B_DOWN:
          state = M_START;
          break;
     }
      key = 0;
      break;
    case M_START:
        drawLine(1, "Start", -1, 0,0) ;
   
      switch(key){
        case B_UP:
          state = M_IMAGES;
          break; 
        
      }
      
      break;
    case S_INTERVAL:
      drawLine(0, "Interval", interval,  1,0);
      drawLine(0, "Images", images, 0,  1);
      switch(key){
         case B_LEFT:
          state = M_INTERVAL;
          break; 
         case B_UP:
          interval++;
          break;
          case B_DOWN:
          if(interval > 0)
            interval--;
            break;
        
      }
      break;
    case S_IMAGES:
      drawLine(0, "Interval", interval,  0,0);
      drawLine(0, "Images", images,  1, 1);
      switch(key){
         case B_LEFT:
        state = M_IMAGES;
       break; 
      }
      break;
      
    case D_STATUS:
    
      break;
   
  }
delay(200);
}

int get_key(int key_in){
  if(key_in < 10){
    return 0;
  }
  if(key_in<100){
    Serial.println("Down");
    return B_DOWN;
  }
  else if(key_in<600){
    Serial.println("Up");
    return B_UP; 
  }
  else if(key_in<700){
    Serial.println("Select");
    return B_SELECT;
  }
  else if(key_in<1000){
    Serial.println("Right");
    return B_RIGHT;
  }
  else if(key_in<1024){
    Serial.println("Left");
    return B_LEFT;
  }
  else{
    return 0;
  }
  
}

  void drawLine(boolean pointer,String text, int value,  boolean edit, int row){

     if(pointer){
       lcd.setCursor(0,row);
       lcd.write(byte(0));
     }
     else{
       lcd.setCursor(1,row);
     }
     lcd.print(text);
       Serial.println(value);
     if(value > -1){
       lcd.print(":");
        lcd.setCursor(11,row);
        if(value < 10)
        lcd.print("00");
       if(value >= 10 && value < 100)
        lcd.print("0");
       if(value >=100 && value < 1000)
        lcd.print("");
         
         
       
       
       lcd.print(value);
       }
     if(edit){
       lcd.setCursor(15,row);
       lcd.write(byte(1));
     }
       
    
  }
   

  
  
