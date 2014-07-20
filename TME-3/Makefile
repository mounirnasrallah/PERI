CROSS_COMPILE ?= bcm2708hardfp-

ifneq ($(KERNELRELEASE),)
	obj-m := bcm2708_lcd.o
else
	KERNELDIR ?= /users/enseig/jpeeters/m1.peri/linux-rpi-3.11.y-build
	PWD := $(shell pwd)

default:
	make -C $(KERNELDIR) \
		ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) M=$(PWD) modules

clean:
	make -C $(KERNELDIR) \
		ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) M=$(PWD) clean

endif
