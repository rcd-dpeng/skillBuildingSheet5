obj-m+=power_shutdown.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
install:
	mkdir /lib/modules/$(uname -r)/kernel/drivers/power_shutdown
	sudo cp power_shutdown.ko /lib/modules/$(uname -r)/kernel/drivers/power_shutdown
	cd /lib/modules/$(uname -r)/kernel/drivers/power_shutdown
	sudo depmod
	cd
	sudo su
	echo power_shutdown >> /etc/modules-load.d/modules.conf
