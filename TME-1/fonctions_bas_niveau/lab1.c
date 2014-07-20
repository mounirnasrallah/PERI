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

int
main ( int argc, char **argv )
{
    int period, half_period;
    int btn0, btn1;
    int count;

    /* Retreive the mapped GPIO memory. */

    /* COMPLETE... */

    period = 1000; /* default = 1Hz */
    if ( argc > 1 ) {
        period = atoi ( argv[1] );
    }
    half_period = period / 2;

    /* Setup GPIO of LED0 to output. */

    /* COMPLETE... */

    printf ( "-- info: start blinking @ %f Hz.\n", ( 1000.0f / period ) );

    /* Blink led at frequency of 1Hz. */
    count = 20;
    while ( --count > 0 ) {
    	/* COMPLETE... */
    }

    /* Reset state of GPIO. */

    /* COMPLETE... */

    /* Release the GPIO memory mapping. */

    /* COMPLETE... */
    
    return 0;
}

