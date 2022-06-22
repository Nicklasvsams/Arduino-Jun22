#include "sketch.h"
#include <MsTimer2.h>
#define pi 3.14

void test(){
  Serial.println("500 ms passed");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  Serial.println(pi);
  Serial.print("Beregn function = ");
  Serial.println(beregn(1500,2000));
  MsTimer2::set(500, test);
  MsTimer2::start();
}

void loop() {
  // put your main code here, to run repeatedly:

}
