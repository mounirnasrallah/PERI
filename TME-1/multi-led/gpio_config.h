#ifndef _GPIO_CONFIG_H_
#define _GPIO_CONFIG_H_

#define GPIO_INPUT_PIN      1
#define GPIO_OUTPUT_PIN     2

/*
 * Configure the GPIO pin as input or output.
 * Return -1 in case of error, 0 otherwise.
 */

int
gpio_config ( int gpio, int value );

#endif

