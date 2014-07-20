CROSS_COMPILE ?= bcm2708hardfp-

CFLAGS=-Wall -Wfatal-errors -O2 -I.
LDFLAGS=-static -L. -lgpio

all: lab2.x

lab2.x: lab2.o
	$(CROSS_COMPILE)gcc -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CROSS_COMPILE)gcc -o $@ -c $(CFLAGS) $<

clean:
	rm -f *.o *~

distclean: clean
	rm -f lab2.x

