obj-m += procfsmodtwo.o

all:
	make -C /lib/modules/`uname -r`/build M=$(PWD) modules
clean:
	make -C /lib/modules/`uname -n`/build M=$(PWD) clean

