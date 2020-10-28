#include <msp430.h>
#include "stateMachines.h"
#include "led.h"

char toggle_red()		/* always toggle! */
{
  static char state = 0;

  switch (state) {
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
    break;
  }
  return 1;			/* always changes an led */
}

char toggle_green()	/* only toggle green if red is on!  */
{
  char changed = 0;
  if (red_on) {
    green_on ^= 1;
    changed = 1;
  }
  return changed;
}


void state_advance()		/* alternate between toggling red & green */
{
  char changed = 0;  

  /*static enum {R=0, G=1} color = G;
  switch (color) {
  case R: changed = toggle_red(); color = G; break;
  case G: changed = toggle_green(); color = R; break;
  }*/

  led_changed = toggle_red();
  led_update();
}

void up_state()
{
  sb = 1;
  toggle_green();
}

void down_state()
{
  sb = 2;
  toggle_red();
}

void buzzer_advance()
{
  if(sb == 1) x+=225;
  else{
}

void main_state_advance()
{
  static int state = 0;

  switch(state){
  case 0:
  case 1: up_state(); state++; break;
  case 2: down_state(); state = 0;
  default: break;
  }
}

