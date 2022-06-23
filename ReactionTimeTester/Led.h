#include <MsTimer2.h>
#define BLINK_TIME 1500
#define BLINK_ON_INTERVAL 100
#define BLINK_OFF_INTERVAL 50

class Led {
  private:
    byte _pin;
  public:
    Led(byte pin) {
      _pin = pin;
      init();
    }

    void init(){
      pinMode(_pin, OUTPUT);
      
      off();
    }

    void on(){
      digitalWrite(_pin, HIGH);
    }

    void off(){
      digitalWrite(_pin, LOW);
    }

    bool isLit(){
      return (digitalRead(_pin) == HIGH);
    }

   void blinkLed(){
      unsigned long startMillis = millis();
      
      while(millis() - startMillis < BLINK_TIME){
        if((millis() - startMillis) % BLINK_ON_INTERVAL == 0){
          on();
        }

        if((millis() - startMillis) % BLINK_OFF_INTERVAL == 0) {
          off();
        }
      }
   }
    
};
