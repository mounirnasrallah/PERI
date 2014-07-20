

all: helloworld.x

helloworld.x: helloworld.c
	bcm2708hardfp-gcc -o $@ $< -O2 -static

clean:
	rm -f *.x
