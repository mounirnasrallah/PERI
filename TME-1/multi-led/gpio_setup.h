#ifndef _GPIO_SETUP_H_
#define _GPIO_SETUP_H_

/*
 * Set up the GPIO memory mapping.
 *
 * Returns -1 in case of error, 0 otherwise.
 *
 * Note: this function must be called before any other
 * code related to GPIO.
 */

int
gpio_setup ( void );

/*
 * Tear down the GPIO memory mapping.
 */

void
gpio_teardown ( void );

#endif

