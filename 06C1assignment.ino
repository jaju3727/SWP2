#define LED_PIN 7

int PERIOD;
int DUTY = 0;
int changingValue;
int stage;

void set_period(int period) {
  PERIOD = constrain(period, 100, 10000); // period 값 제한 100 to 10000 (unit: us)

  /* 
  triangle패턴이 1초마다 반복 되기 위한 값 설정
  1s == 100000us
  최소 - 최대 - 최소 이 사이클의 단계는 200단계 (b.c [0,100), [100,0))
  loop 하나마다 5000us의 시간을 소비해야 하므로 다음과 같이 변수 설정
  */
  if (period < 5000) {
    changingValue = 1;
    stage = 5000/period;
  } else {
    changingValue = period/5000;
    stage = 1;
  }
}

void set_duty(int duty) {
  duty = constrain(duty, 0, 100); // duty 값 제한 0 to 100 (unit: %)
  int onTime = (int) PERIOD * (duty / 100.0);
  int offTime = PERIOD - onTime;

  if (duty != 0) { // 더 정확한 밝기를 위해 추가한 조건
    digitalWrite(LED_PIN, 0);
    delayMicroseconds(onTime);
  }
  if (duty != 100) { // 더 정확한 밝기를 위해 추가한 조건
    digitalWrite(LED_PIN, 1);
    delayMicroseconds(offTime);
  }
}

void setup() {
  pinMode(LED_PIN, OUTPUT);

  set_period(10000); // 주기 설정

  Serial.begin(57600);
}

void loop() {
  DUTY += changingValue;

  if (DUTY <= 0 || DUTY >= 100) {
    changingValue *= -1;
  }

  for (int i = 0; i < stage; ++i) {
    set_duty(DUTY);
  }

  Serial.print(DUTY);
  Serial.print(" : ");
  Serial.println(millis());
}
