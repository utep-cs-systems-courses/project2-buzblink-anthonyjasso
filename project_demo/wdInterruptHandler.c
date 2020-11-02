#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"


char buttonState = 0;
void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char buzzBlinkCount = 0;
  if (++buzzBlinkCount == 60 && buttonState == 0) { /* button 1: flashing red led */
    buzzer_set_period(0);
    only_red();
  }
  else if (buzzBlinkCount == 120 && buttonState == 0) {
    red75();
  }
  else if (buzzBlinkCount == 180 && buttonState == 0) {
    red50();
    buzzBlinkCount = 0;
  }
  else if ((buzzBlinkCount % 25) == 0 && buttonState == 1) { /* button 2: siren w/ red and green leds */
    buzzer_advance();
  }
  else if ((buzzBlinkCount == 30) && buttonState == 1) {
    siren_state_machine();
    buzzBlinkCount = 0;
  }
  else if ((buzzBlinkCount == 2) && buttonState == 2) { /* button 3: dimmed red led to %25 brightness */
    red25();
    buzzer_set_period(0);
    buzzBlinkCount = 0;
  }
  else if (buttonState == 3) { /* button 4: toggles green led */
    buzzer_set_period(0);
    only_green();
  }
}
