obj-m += hello1.o hello2.o

ccflags-y := -I$(src)/inc

KDIR ?= /home/vboxuser/repos/linux-stable

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
