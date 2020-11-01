# makfile configuration
COMMON_OBJECTS  =
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS         = -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = mps430-elf-gcc
AS              = msp430-elf-as

all: toy.elf

#additional rules for files
toy.elf: ${COMMON_OBJECTS} demoMain.o switches.o stateMachines.o buzzer.o led.o wdInterruptHandler.o p2_interrupt_handler.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: toy.elf
	msp430loader.sh toy.elf

clean:
	rm -f *.o *.elf

led.o: led.c led.h

wdInterruptHandler.o: stateMachines.h led.h switches.h buzzer.h

stateMachines.o: led.h stateMachines.h buzzer.h

buzzer.o: buzzer.h

p2_interrupt_handler.o: switches.h

switches.o: switches.h led.h

demoMain.o: led.h switches.h buzzer.h
