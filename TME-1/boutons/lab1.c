/*
 * This file is a template for the first Lab in the SESI-PERI module.
 *
 * It draws inspiration from Dom & Gert code on ELinux.org.
 *
 * Authors:
 *   Julien Peeters <julien.peeters@lip6.fr>
 */

#include <stdio.h>
#include <stdlib.h>

#include "gpio.h"

static
void
delay ( unsigned int milisec )
{
    struct timespec ts, dummy;
    ts.tv_sec  = ( time_t ) milisec / 1000;
    ts.tv_nsec = ( long ) ( milisec % 1000 ) * 1000000;
    nanosleep ( &ts, &dummy );
}

/*
 * Main program.
 */

#define GPIO_BTN0   18
#define GPIO_BTN1   23


int
main ( int argc, char **argv )
{
    int period, half_period;
    int btn0, btn1,btn_tmp;
    int count;

    /* Retreive the mapped GPIO memory. */
    if(gpio_setup()==-1){
      return -1;
    }

    period = 1000; /* default = 1Hz */
    if ( argc > 1 ) {
        period = atoi ( argv[1] );
    }
    half_period = period / 2;

    /* Setup GPIO of BTN'X' to input. */
    if(gpio_config(GPIO_BTN0,GPIO_INPUT_PIN)==-1 || gpio_config(GPIO_BTN1,GPIO_INPUT_PIN)==-1 ){
      return -1;
    }

    printf ( "-- info: start blinking @ %f Hz.\n", ( 1000.0f / period ) );

    /* Blink led at frequency of 1Hz. */
    btn_tmp=0;


    while (btn1!=1){
      if( (gpio_value(GPIO_BTN0,&btn0)!=-1) && (gpio_value(GPIO_BTN1,&btn1)!=-1)){
        if( btn_tmp != btn0){
          printf("Changement de valeur : %d \n",btn0);
        }
        btn_tmp=btn0;
      }
      else{
        return -1;
      }
    }


/* Release the GPIO memory mapping. */
    gpio_teardown();

    return 0;
}

