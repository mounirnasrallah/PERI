#include "gpio_setup.h"




int gpio_setup(void){

addr_gpio = mmap(NULL,
       4096,
       PROT_READ | PROT_WRITE,
       MAP_PRIVATE,
       "/dev/meme",
       0x20200000
    );

}


void gpio_teardown(void){

  munmap(addr_gpio,4096);

}
