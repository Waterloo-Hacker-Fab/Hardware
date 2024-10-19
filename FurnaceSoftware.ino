#include <Wire.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include <LiquidCrystal_I2C.h> // Library required for LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

int LEDS[3] = {A0, A1, A2};
int LEDcounter = 0; 
int LastLED = 0;
int TDelay = 10;

byte EN_cnt = 0;
byte SW_cnt = 0;

int CLK = 2;
int DT = 4;
int SW = 3;

word D_Counter = 0;
word Old_D_Counter = 0;
//////////////////////////////////////////////////////////////////////////////////////////////

void LCD() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("Hello World!");
  lcd.setCursor(2,1);
  lcd.print("Counter: ");
}

void updateLCD() {
  lcd.setCursor(11, 1);
  lcd.print("     "); 
  lcd.setCursor(11, 1);
  lcd.print(D_Counter); 
}


void EncoderSW(){
  SW_cnt = 2; //delay for Switch
}

void EncoderCLK(){
  EN_cnt = 2; //delay for CLK and DT
  //D_Counter += 100;
}
//////////////////////////////////////////////////////////////////////////////////////////////
void setup() {

  Serial.begin(9600);

  pinMode(SW, INPUT);
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);

  LCD();
 
 cli();

  attachInterrupt(digitalPinToInterrupt(CLK), EncoderCLK, RISING); 
  attachInterrupt(digitalPinToInterrupt(SW), EncoderSW, FALLING); 

 for(int j = 0; j < 3; j++) {
    pinMode(LEDS[j], OUTPUT);
 }

 //cli();
  TCCR1A = 0;
  TCCR1B = 0; //setting all bits in register to 0 because they all start at 1

  OCR1A = TDelay; // setting overflow time
  TIMSK1 |= (1 << OCIE1A); //comparison rather than overflow

  TCCR1B |= (1 << CS12);
  TCCR1B |= (1 << CS10); 
  TCCR1B |= (1 << WGM12); //prescalar settings (sets specifc bits in timer register corresponding to prescalar)
  // or: TCCR1B |= 5;
 sei();
}
//////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  if (Old_D_Counter != D_Counter){
    updateLCD(); 
    Old_D_Counter = D_Counter; 
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////

ISR(TIMER1_COMPA_vect){
  
  if (SW_cnt >> 0){
    SW_cnt--;
      if (SW_cnt == 0) {
        int c = 0;
        c += digitalRead(SW);
        c += digitalRead(SW);
        c += digitalRead(SW);
         D_Counter += 100; //Use button for select on GUI
        }
      } // Swtich on Encoder

  if (EN_cnt >> 0) {
    EN_cnt--;
     if (EN_cnt == 0) {
      int b = 0;
      b += digitalRead(CLK);
      b += digitalRead(CLK);
      b += digitalRead(CLK);
      if (b == 3){
        if (digitalRead(DT)){
          D_Counter--;
        }
        else {
          D_Counter++;
        }
        D_Counter = min(1200, max(0, D_Counter));
      }
    } 
  }

  LEDcounter++;
  LastLED = LEDcounter - 1; 
  if (LEDcounter == 3){
    LEDcounter = 0;
    LastLED = 2;
  }
  digitalWrite(LEDS[LastLED], 0);
  digitalWrite(LEDS[LEDcounter], 1);
  TCNT1 = 0;
}
