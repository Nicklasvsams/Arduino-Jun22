#include "Button.h"
#include "Led.h"
#include <MsTimer2.h>
#define LED_1_PIN 7
#define LED_2_PIN 6
#define LED_3_PIN 5
#define BUTTON_PIN 3
#define KEY_THRESHOLD 40
#define BAUD_RATE 9600
#define LED_DELAY 1000
#define INTERVAL 2

Led Led1(LED_1_PIN);
Led Led2(LED_2_PIN);
Led Led3(LED_3_PIN);
Button Button1(BUTTON_PIN);
unsigned long timeOfClick = 0;

void buttonCheck(){
  static int intervalCount = 0;
  
  if (Button1.isPressed()){
    intervalCount++;
  }
  else{
    intervalCount = 0;
  }

  if(intervalCount == KEY_THRESHOLD){
    timeOfClick = millis();
    Led1.on();
    Led2.off();
    Led3.off();
  }

  if(timeOfClick > 0){
    if(millis() - timeOfClick > LED_DELAY && millis() - timeOfClick < LED_DELAY*2){
      Led1.off();
      Led2.on();
    }
    if(millis() - timeOfClick > LED_DELAY*2 && millis() - timeOfClick < LED_DELAY*3){
      Led2.off();
      Led3.on();
    }
    if(millis() - timeOfClick >  LED_DELAY*3){
      Led3.off();
      timeOfClick = 0;
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUD_RATE);
  MsTimer2::set(INTERVAL, buttonCheck);
  MsTimer2::start();
}

void loop() {
}
