LIBCMINI=/usr/libcmini
OPT=-Wno-multichar

all: altram altrom

altram: 
	m68k-atari-mint-gcc $(OPT) -nostdlib -o altram.prg  -L$(LIBCMINI)/lib -I$(LIBCMINI)/include $(LIBCMINI)/lib/crt0.o  altramset.c buserror.c -lcmini -lgcc

altrom:
	m68k-atari-mint-gcc $(OPT) -nostdlib -o altrom.prg  -L$(LIBCMINI)/lib -I$(LIBCMINI)/include $(LIBCMINI)/lib/crt0.o  altramset.c buserror.c -lcmini -lgcc -DROM

exxosram:
	m68k-atari-mint-gcc $(OPT) -nostdlib -o exxosram.prg  -L$(LIBCMINI)/lib -I$(LIBCMINI)/include $(LIBCMINI)/lib/crt0.o  altramset.c buserror.c -lcmini -lgcc

clean:
	rm -f *.o *.prg
