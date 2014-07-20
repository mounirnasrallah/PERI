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

#define GPIO_LED0   4
#define GPIO_LED1   17
#define GPIO_LED2   27
#define GPIO_LED3   22


int
main ( int argc, char **argv )
{
    int period, half_period;
    int btn0, btn1;
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

    /* Setup GPIO of LED0 to output. */
    if(gpio_config(GPIO_LED0,GPIO_OUTPUT_PIN)==-1 || gpio_config(GPIO_LED1,GPIO_OUTPUT_PIN)==-1 || gpio_config(GPIO_LED2,GPIO_OUTPUT_PIN)==-1 ||  gpio_config(GPIO_LED3,GPIO_OUTPUT_PIN)==-1 ){
      return -1;
    }

    printf ( "-- info: start blinking @ %f Hz.\n", ( 1000.0f / period ) );

    /* Blink led at frequency of 1Hz. */
    count = 20;
    while ( --count > 0 ) {
      gpio_update(GPIO_LED0,count%2);
      delay(100);
      gpio_update(GPIO_LED1,count%2);
      delay(100);
      gpio_update(GPIO_LED2,count%2);
      delay(100);
      gpio_update(GPIO_LED3,count%2);
      delay(100);
    }

    /* Reset state of GPIO. */
    gpio_update(GPIO_LED0,0);
    gpio_update(GPIO_LED1,0);
    gpio_update(GPIO_LED2,0);
    gpio_update(GPIO_LED3,0);


    gpio_config(GPIO_LED0,GPIO_INPUT_PIN);
    gpio_config(GPIO_LED1,GPIO_INPUT_PIN);
    gpio_config(GPIO_LED2,GPIO_INPUT_PIN);
    gpio_config(GPIO_LED3,GPIO_INPUT_PIN);

/* Release the GPIO memory mapping. */
    gpio_teardown();

    return 0;
}

