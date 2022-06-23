class Button {
  private:
    byte _pin;
    byte _state;
    byte _lastReading;
    unsigned long _lastDebounceTime = 0;
    unsigned long _debounceDelay = 25;
    int _baudrate = 9600;
  public:
    Button(byte pin) {
      _pin = pin;
      _lastReading = LOW;
      init();
    }

    void init(){
      pinMode(_pin, INPUT_PULLUP);
      update();
    }

    void update(){
      byte newReading = digitalRead(_pin);
      if (newReading != _lastReading) {
        _lastDebounceTime = millis();
      }

      if (millis() - _lastDebounceTime > _debounceDelay) {
        _state = newReading;
      }

      _lastReading = newReading;
    }

    byte getState() {
      update();
      return _state;
    }

    bool isPressed() {
      return (getState() == LOW);
    }
};
