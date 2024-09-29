#define PIN_LED 9

void setup() {
  pinMode(PIN_LED, OUTPUT);
  
  Serial.begin(57600);
}

void loop() {
  digitalWrite(PIN_LED, 0);
  delay(1000);

  for (int i = 0; i < 5; ++i){
    digitalWrite(PIN_LED, 1);
    delay(100);
    digitalWrite(PIN_LED, 0);
    delay(100);
  }

  digitalWrite(PIN_LED, 1);

  while(1) {
    ;
  }
}
