#include <Arduino.h>
#define FREQ 10000
volatile int count;
hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

#define testPin GPIO_NUM_21
#define inputPin GPIO_NUM_32
#define outputPin GPIO_NUM_25

#define M 3

const float bconst = 0.25;

static float xbuff[M+1];
static float b[M+1];

void IRAM_ATTR onTime()
{
  portENTER_CRITICAL_ISR(&timerMux);
  count++;
  portEXIT_CRITICAL_ISR(&timerMux);
}

void setup()
{
  pinMode(inputPin, INPUT_PULLUP);
  pinMode(outputPin, OUTPUT);
  pinMode(testPin, OUTPUT);
  Serial.begin(9600);
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTime, true);

  // Sets an alarm to sound every second
  timerAlarmWrite(timer, 1000000 / FREQ, true);
  timerAlarmEnable(timer);

  for(int i = 0; i <= M; i++) {
    xbuff[i] = 0;
    b[i] = bconst;
  }
}

void loop()
{
  if (count > 0)
  {
    // Comment out enter / exit to deactivate the critical section
    portENTER_CRITICAL(&timerMux);
    count--;
    portEXIT_CRITICAL(&timerMux);
    float tempinvalue = (float)analogRead(inputPin);
    
    digitalWrite(testPin, HIGH);

    for(int i = M; i >0; i--) {
      xbuff[i]= xbuff[i-1];
    }
    xbuff[0] = tempinvalue;

    float outvalue = 0;
    for(int i = 0; i <=M; i++) {
      outvalue += b[i]*xbuff[i];
    }

    dacWrite(DAC1, (uint32_t)outvalue / 16);

    digitalWrite(testPin, LOW);


  }
}
