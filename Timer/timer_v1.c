#include <reg52.h>

/*------------------------------------------------
Timer 0 Interrupt Service Routine.

Set a breakpoint on 'overflow_count++' and run the
program in the debugger.  You will see this line
executes every 65536 clock cycles.
------------------------------------------------*/

static unsigned char outer = 0;
static unsigned char inner = 0;
static unsigned char count = 0;
static unsigned char status = 0;

sbit LED_OUT = P0^1;
sbit LED_OUT2 = P0^2;

void timer0_ISR (void) interrupt 1
{
outer++;

if(outer % 200 == 0)
		{
		inner++;
		outer = 0;
				if(inner % 200 == 0)
				{
				count++;
				inner = 0;
						if(count % 200 == 0)
						{
							count = 0;
							
							if(status == 0)
							{
								status = 1;
								LED_OUT = 1;
							}
							else if(status == 1)
							{
								status = 0;
								LED_OUT = 0;
							}
						
						}
				}
		}
}
/*------------------------------------------------
MAIN C function
------------------------------------------------*/
void main (void)
{
/*--------------------------------------
Set Timer0 for 16-bit timer mode.  The
timer counts to 65535, overflows, and
generates an interrupt.

Set the Timer0 Run control bit.
--------------------------------------*/
TMOD = (TMOD & 0xF0) | 0x01;  /* Set T/C0 Mode */
ET0 = 1;                      /* Enable Timer 0 Interrupts */
TR0 = 1;                      /* Start Timer 0 Running */
EA = 1;                       /* Global Interrupt Enable */

/*--------------------------------------
Do Nothing.  Actually, the timer 0
interrupt will occur every 65536 clocks.
--------------------------------------*/
while (1)
  {
  LED_OUT2 = 0;
  }
}

