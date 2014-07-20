#include "gpio_setup.h"
#include "gpio_config.h"

int gpio_config( int gpio, int value){

  *(addr_gpio) |= ( 0x1 << ( 3 * gpio ));

}
