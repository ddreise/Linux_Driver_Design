#before Make, check the most current version number using "uname -r"
#then, update all by "apt-get update"
#next, obtain the path to the header file folder of the most updates Linux version.
#In my case, it's 5.0.0.36-generic.  This is Distro- and Version-dependent.

ifneq (${KERNELRELEASE},)
	obj-m += kmembuff.o
else
	KERNEL_SOURCE := /usr/src/linux-headers-5.0.0-37-generic
	PWD := $(shell pwd)

default:
	${MAKE} -C ${KERNEL_SOURCE} M=$(PWD) modules

clean:
	${MAKE} -C ${KERNEL_SOURCE} M=$(PWD) clean
endif
