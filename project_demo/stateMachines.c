#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

static char stateCheck = 0;
static char state      = 0;

void red25()             /* %25 brightness */
{
  switch (state) {
  case 0:
    red_on = 0;
    state  = 1;
    break;
  case 1:
    red_on = 0;
    state  = 2;
    break;
  case 2:
    red_on = 1;
    state  = 0;
    break;
  }
  led_update();
}

void red50()		/* %50 brightness */
{
  switch (state) {
  case 0:
    red_on = 1;
    state  = 1;
    break;
  case 1:
    red_on = 0;
    state  = 0;
    break;
  }
  led_update();			/* always changes an led */
}

void red75()              /* %75 brightness */
{
  switch (state) {
  case 0:
    red_on = 1;
    state  = 1;
    break;
  case 1:
    red_on = 1;
    state  = 2;
    break;
  case 2:
    red_on = 0;
    state  = 0;
    break;
  }
  led_update();
}
    
void only_red()          /* toggles only red led  */
{
  red_on = 1;
  green_on = 0;
  led_update();
}

void only_green()          /* toggles only green led */
{
  green_on = 1;
  red_on   = 0;
  led_update();
}

void state_one()          /* states for siren state machine */
{
  stateCheck = 1;
  only_green();
}

void state_two()
{
  stateCheck = 0;
  only_red();
}

void siren_state_machine()          /* siren state machine for leds */
{
  static char sirenState = 0;
  switch (sirenState) {
  case 0:
  case 1:
    state_one();
    sirenState++;
    break;
  case 2:
    state_two();
    sirenState = 0;
  default:
    break;
  }
}

void buzzer_advance()          /* buzzer for siren */
{
  static int n = 0;
  if(stateCheck) n = 700;
  else n = 1000;

  short cycles = 2000000/n;
  buzzer_set_period(cycles);
}
