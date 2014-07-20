CROSS_COMPILE ?= bcm2708hardfp-

CFLAGS=-Wall -Wfatal-errors -O2
LDFLAGS=-static -L. -lgpio

all: lab1-exo3.x

lab1-exo3.x: lab1.c libgpio.a
	$(CROSS_COMPILE)gcc -o $@ $^ $(LDFLAGS)

libgpio.a: gpio_value.o gpio_config.o gpio_setup.o
	$(CROSS_COMPILE)ar -rcs $@ $^

%.o: %.c
	$(CROSS_COMPILE)gcc -o $@ -c $(CFLAGS) $<

clean:
	rm -f *.o *.x *~

distclean: clean
	rm -f *.a

