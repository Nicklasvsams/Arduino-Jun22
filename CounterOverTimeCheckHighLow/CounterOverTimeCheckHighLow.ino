#include <MsTimer2.h>
#include <SimpleFIFO.h>

#define sampleInterval 2
#define keyPin 3
#define keyThreshold 20
#define holdKeyThreshold 35
#define holdMinimumCount 300
#define baudRate 9600
SimpleFIFO<char, 10> keyboardBuffer;

void interruptCheck(){
  static int intervalCount = 0;
  
  if(!digitalRead(keyPin)) /// If key is pressed
  {
    intervalCount = intervalCount + 1;
  }
  else
  {
    intervalCount = 0;
  }

  if(intervalCount == keyThreshold)
  {
    keyboardBuffer.enqueue('X');
  }

  if(intervalCount > holdMinimumCount && (intervalCount % holdKeyThreshold) == 0)
  {
    keyboardBuffer.enqueue('X');
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(baudRate);
  pinMode(keyPin, INPUT_PULLUP);
   
  MsTimer2::set(sampleInterval, interruptCheck);
  MsTimer2::start();  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(keyboardBuffer.count())
  {
    Serial.print(keyboardBuffer.dequeue());
  }  
}
