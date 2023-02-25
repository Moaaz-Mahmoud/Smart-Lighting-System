#include "protothreads.h"

#define LED_1 2
#define LED_2 13

pt ptSlowBlink;
pt ptFastBlink;

int fastBlinkThread(struct pt* pt)
{
  PT_BEGIN(pt);
 
  while(true)
  {
  digitalWrite(LED_1, HIGH);
  PT_SLEEP(pt, 500);
  digitalWrite(LED_1, LOW);
  PT_SLEEP(pt, 500);
  }

  PT_END(pt);
}

int slowBlinkThread(struct pt* pt)
{
  PT_BEGIN(pt);
 
  while(true)
  {
  digitalWrite(LED_2, HIGH);
  PT_SLEEP(pt, 100);
  digitalWrite(LED_2, LOW);
  PT_SLEEP(pt, 100);
  }

  PT_END(pt);
}

void setup()
{
  PT_INIT(&ptSlowBlink);
  PT_INIT(&ptFastBlink);
 
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
}

void loop()
{
  PT_SCHEDULE(slowBlinkThread(&ptSlowBlink));
  PT_SCHEDULE(fastBlinkThread(&ptFastBlink));
}
