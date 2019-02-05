obj-m+=power_shutdown.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
install:
	mkdir -p /lib/modules/$(shell uname -r)/kernel/drivers/power/
	cp power_shutdown.ko /lib/modules/$(shell uname -r)/kernel/drivers/power/
	echo "power_shutdown" >> /etc/modules
	depmod
	modprobe power_shutdown
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
