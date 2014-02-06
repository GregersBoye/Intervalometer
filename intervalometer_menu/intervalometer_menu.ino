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
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

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
  interval = 0;
  images = 0;
  lcd.begin(16, 2);  
  lcd.clear();
  lcd.createChar(0, arrow);
  lcd.createChar(1, updown);
  state = M_INTERVAL;
  Serial.begin(9600);
}

void loop() {
  key_in = analogRead(0); // read the value from the sensor
  int key = get_key(key_in);
   
  lcd.clear();
  lcd.write(key_in);
 
  switch(state){
    case M_INTERVAL:
      drawLine("Interval", interval, 1, 0, 0); 
      drawLine("Images", interval, 0, 0, 1); 
      switch(key){
        case B_DOWN:
          state = M_IMAGES;
          break;
        case B_RIGHT:
          state = S_IMAGES;
          break;
      }
      key = 0;
      break;
    case M_IMAGES:
      drawLine("Images", images, 1,0,1);
      drawLine("Interval", inteval, 0,0,0);
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
        drawLine("Start", -1, 1,0,0)    ;
      
   
      switch(key){
        case B_UP:
          state = M_IMAGES;
          break; 
        
      }
      
      break;
    case S_INTERVAL:
      drawLine("Interval", interval, 0, 1,0);
      drawLine("Images", images, 0, 0, 1);
      
      break;
    case S_IMAGES:
      drawLine("Interval", interval, 0, 0,0);
      drawLine("Images", images, 0, 1, 1);
      break;
      
    case D_STATUS:
    
      break;
   
  }
delay(150);
}

int get_key(int key_in){
  if(key_in<100){
    return B_RIGHT;
  }
  else if(key_in<200){
    return B_UP; 
  }
  else if(key_in<400){
    return B_DOWN;
  }
  else if(key_in<600){
    return B_LEFT;
  }
  else if(key_in<800){
    return B_SELECT;
  }
  else{
    return 0;
  }
  
}

  void drawLine(String text, unsigned int value, boolean pointer, boolean edit, int row){
     lcd.clear();
     if(pointer){
       lcd.setCursor(0,row);
       lcd.write(byte(0));
     }
     else{
       lcd.setCursor(1,row);
     }
     lcd.print(text);
       
     if(value > -1){
       lcd.print(": ");
       lcd.print(value);
       }
     if(edit){
       lcd.setCursor(15,row);
       lcd.write(byte(1));
     }
       
    
  }
   

  
  
