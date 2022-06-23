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
};
