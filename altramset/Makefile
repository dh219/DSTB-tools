LIBCMINI=/usr/libcmini
OPT=-Wno-multichar

all: altram altrom mhz16 mhz8

altram: 
	m68k-atari-mint-gcc $(OPT) -nostdlib -o dstb1ram.prg  -L$(LIBCMINI)/lib -I$(LIBCMINI)/include $(LIBCMINI)/lib/crt0.o  altramset.c buserror.c -lcmini -lgcc

altrom:
	m68k-atari-mint-gcc $(OPT) -nostdlib -o dstb1rom.prg  -L$(LIBCMINI)/lib -I$(LIBCMINI)/include $(LIBCMINI)/lib/crt0.o  altramset.c buserror.c -lcmini -lgcc -DROM

mhz16:
	m68k-atari-mint-gcc $(OPT) -nostdlib -o dstb1_16.prg  -L$(LIBCMINI)/lib -I$(LIBCMINI)/include $(LIBCMINI)/lib/crt0.o  speed.c buserror.c -lcmini -lgcc

mhz8:
	m68k-atari-mint-gcc $(OPT) -nostdlib -o dstb1_8.prg  -L$(LIBCMINI)/lib -I$(LIBCMINI)/include $(LIBCMINI)/lib/crt0.o  speed.c buserror.c -lcmini -lgcc


clean:
	rm -f *.o *.prg
