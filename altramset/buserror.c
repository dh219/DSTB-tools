#include "altramset.h"
#include <setjmp.h>

/* bus error detection code courtesy of mfro                    */
/* https://www.atari-forum.com/viewtopic.php?p=414128&#p414128  */

static volatile bool available;
static unsigned char *address;
static uint8_t value;
static jmp_buf env;

void exception_handler(short sr)
{
//    Cconws("Buserror!\r\n");
    available = false;
    longjmp(env, 1);
}

void check_read_byte_real(void)
{
    void (*v_save)(void);

    available = true;
    v_save = Setexc(2, exception_handler);
    if (!setjmp(env))
        value = * (volatile unsigned char *) address;
    Setexc(2, v_save);

    //printf("address %p is %savailable and reads %x\r\n", address, available ? "" : "not ", value );
}
void check_write_byte_real(void)
{
    void (*v_save)(void);

    available = true;
    v_save = Setexc(2, exception_handler);
    if (!setjmp(env))
        * (volatile unsigned char *) address = value;
    Setexc(2, v_save);

    //printf("address %p is %savailable for write\r\n", address, available ? "" : "not ");
}

int check_read_byte( long add )
{
//    unsigned char var;

    address = (unsigned char *) add;
    Supexec(check_read_byte_real);
    return available;
}

int check_write_byte( long add, uint8_t val )
{
//    unsigned char var;

    address = (unsigned char *) add;
    value = val;
    Supexec(check_write_byte_real);
    return available;
}
