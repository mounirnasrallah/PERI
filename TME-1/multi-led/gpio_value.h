#ifndef _GPIO_VALUE_H_
#define _GPIO_VALUE_H_

/*
 * Read the value of a given GPIO.
 */

int
gpio_value ( int gpio, int * value );

/*
 * Update the value of the GPIO (if output).
 * Output value if zero if 'value' == 0, 1 otherwise.
 */

int
gpio_update ( int gpio, int value );

#endif

