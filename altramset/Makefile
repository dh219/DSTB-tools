LIBCMINI=/usr/libcmini
OPT=-Wno-multichar

altramset: 
	m68k-atari-mint-gcc $(OPT) -nostdlib -o altram.prg  -L$(LIBCMINI)/lib -I$(LIBCMINI)/include $(LIBCMINI)/lib/crt0.o  altramset.c buserror.c -lcmini -lgcc

clean:
	rm -f *.o altram.prg
