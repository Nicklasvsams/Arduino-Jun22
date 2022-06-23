#include "Button.h"
#include "Led.h"
#include <MsTimer2.h>

#define LED_1_PIN 3
#define LED_2_PIN 5
#define BUTTON_PIN 4
#define KEY_THRESHOLD 1500
#define BAUD_RATE 9600
#define LED_DELAY 1000
#define INTERVAL 2
#define TIMES_TO_TEST 5
#define DEBOUNCE_DELAY 50

Led Led1(LED_1_PIN);
Led Led2(LED_2_PIN);
Button Button1(BUTTON_PIN);

int reactionTimeArray[TIMES_TO_TEST];
unsigned long timeOfClick = 0;
int intervalCount = 0;

void buttonCheck() {
  if (millis() > 1500) {
    if (Button1.isPressed()) {
      intervalCount++;
    }
    else {
      intervalCount = 0;
    }
  }
}

int getAverageReactionTime() {
  float sumOfReactionTimes = 0;
  for (int i = 0; i < (TIMES_TO_TEST); i++) {
    sumOfReactionTimes += reactionTimeArray[i];
  }

  return (sumOfReactionTimes / TIMES_TO_TEST);
};

int doTest() {
  int timesTested = 0;
  unsigned long startTime = 0;
  int startNext = 0;
  int randomDelay = 0;
  bool buttonPressed = false;

  while (timesTested < TIMES_TO_TEST) {
    Led1.off();
    Led2.off();
    startTime = millis();
    randomDelay = random(1, 5000);

    do {
      buttonPressed = false;
      if (millis() - startTime >= randomDelay) {
        Led1.on();
        
        if (Button1.isPressed()) {
          buttonPressed = true;
          reactionTimeArray[timesTested] = (millis() - startTime);
          
          timesTested++;
          Led1.off();
          delay(500);
        }
      }

      if (Button1.isPressed() && millis() - startTime < randomDelay){
        buttonPressed = true;
        Led2.on();
        return 0;
      }
    }  while (!buttonPressed);
  }
  
  Led2.blinkLed();

  return getAverageReactionTime();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUD_RATE);
  MsTimer2::set(INTERVAL, buttonCheck);
  MsTimer2::start();
}

void loop() {
  if (intervalCount >= KEY_THRESHOLD && intervalCount < KEY_THRESHOLD + 300) {
    Led2.blinkLed();
    int result = doTest();

    if(result == 0){
      Serial.println(F("You pressed the button at the wrong time, try again."));
    }
    else{
      Serial.print(F("Reaction time: "));
      Serial.println(result);
    }
  }
}
