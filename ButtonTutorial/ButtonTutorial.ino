#define baudrate 9600
#define pin 3

void keypressed(){
  static unsigned long ms = 0;
  
  if((millis() - ms) > 500)
  {
    Serial.print("Key pressed: ");
    Serial.println(millis());
    ms = millis();
  }
}

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(baudrate);
  pinMode(pin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(pin), keypressed, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!digitalRead(pin)){ /// 0 equals key pressed
    
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else{
    digitalWrite(LED_BUILTIN, LOW); 
  }
}
