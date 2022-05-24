#include "altramset.h"

//#define EXXOS // comment in for EXXOS booster

#ifdef EXXOS
const char* name = "EXXOSRAM";

//  start       end    
//  finish with 0,0
uint32_t altram_blocks[] = { 
    0x400000,   0x600000,
    0x640000,   0x800000,
    0
};

uint32_t rom_start =    0xe00000;
uint32_t rom_size =     0x040000;
// 0 to disable
uint32_t altrom_start = 0x600000;

uint32_t altram_enable = 0xfffe00;
uint32_t altrom_enable = 0xfffe0e;

#elif ROM

const char* name = "DSTB1";
//  start       end    
//  finish with 0,0
uint32_t altram_blocks[] = { 
    0x400000,   0xb00000,
    0xb40000,   0xc00000,
    0,0
};

uint32_t rom_start =    0xe00000;
uint32_t rom_size =     0x040000;

uint32_t altrom_start = 0xb00000; // 0 to disable
uint32_t altram_enable = 0xfffe00;
uint32_t altrom_enable = 0xfffe0e;

#else

const char* name = "DSTB1";
//  start       end    
//  finish with 0,0
uint32_t altram_blocks[] = { 
    0x400000,   0xc00000,
    0,0
};

uint32_t rom_start =    0xe00000;
uint32_t rom_size =     0x040000;

uint32_t altrom_start = 0; // 0 to disable
uint32_t altram_enable = 0xfffe00;
uint32_t altrom_enable = 0xfffe0e;

#endif





typedef struct
{
    LONG id;             /* Identification code */
    LONG value;          /* Value of the cookie */
} COOKJAR;


short set_cookie( void *frb ) {
    static WORD use_ssystem = -1;
    COOKJAR *cookiejar;
    LONG    val = -1l;
    int max;
    WORD    i=0;
    LONG cookie = '_FRB';
/*    void *frb; */

    /* Get pointer to cookie jar */
    cookiejar = (COOKJAR *)(Setexc(0x05A0/4,(const void (*)(void))-1));
    if( cookiejar ) {
        for( i=0 ; cookiejar[i].id ; i++ ) {
            //printf("%x\r\n", cookiejar[i].id );
            if( cookiejar[i].id==cookie ) {
                return 1;
            }
        }
        // not found, make it at offset i
        max = (int)cookiejar[i].value;
        //printf("Maximum number of cookie entires=%d, in use=%d\r\n", max, i);
        if( max <= i ) {
            // no more room
            printf( "Can't add any more cookies. Jar is full. Exiting.\r\n");
            exit(20);
        }


        cookiejar[i+1].id = 0x0;
        cookiejar[i+1].value = max;
        cookiejar[i].id = cookie;
        cookiejar[i].value = (LONG)frb;
    }
    else {
        printf("Cookiejar not available. Exiting\r\n");
        exit(10);
    }
    return 0;
}

/*
void doverify() {
    uint32_t offset;
    uint16_t *val1;
    uint16_t *val2;
    for( offset = 0x0 ; offset <= 0x080000 ; offset += 2 ) {
        val1 = (uint16_t*)(0xe00000+offset);
        val2 = (uint16_t*)(0xb00000+offset);
        if( *val1 != *val2 ) {
            printf("Verification error at offset %x (%x:%x)\r\n", offset, *val1, *val2);
        }
    }
}
*/

int main( int argc, char *argv[] ) {
    int rc;
    char has_cookie;
    uint16_t value;
    
    if( altram_blocks[0] == 0x0 || altram_blocks[1]-altram_blocks[0] == 0 ) { // no altram
        return 5;
    }
    
    /* first check if we can read first block, if so do nothing */
    rc = check_read_byte(altram_blocks[0]);
    if( rc ) {
        printf("AltRAM already enabled. Exiting.\r\n");
        exit(1);
    }

    /* try to enable the board */
    rc = check_write_byte( altram_enable, 0xff);
    if( !rc ) {
        printf("%s not detected. Exiting.\r\n", name);
        exit(2);
    }
    rc = check_read_byte(altram_blocks[0]);
    if( !rc ) {
        printf("Failed to activate %s AltRAM. Exiting.\r\n", name);
        exit(3);
    }

    if( altrom_start > 0 ) {
        /* copy TOS to RAM -- 256k at E00000 for TOS 2.06 */
        uint16_t *src =    (uint16_t*)rom_start;
        uint16_t *dst =    (uint16_t*)altrom_start;

        void *buf = memcpy( dst, src, (size_t)rom_size );
        if( !buf ) {
            printf("memcpy() of TOS to AltRAM failed. Exiting.\r\n");
            exit(5);
        }
        printf("Successfully copied TOS to SDRAM.\r\n");

        /* enable TOS redirection */
        int redir_active = 0;

        redir_active = check_write_byte( altrom_enable, 0xff);

        if( !redir_active ) {
            printf("%s TOS redirection failed.\r\n", name);
        }
        else {
            printf("%s TOS redirection active.\r\n", name);
        }
    }

    printf("Enabled %s AltRAM\r\n", name);


    // Use the RAM I (this program) was allocated as the FRB [hacky nasty]
    has_cookie = set_cookie(_base->p_tbase);
    if( has_cookie ) {
        printf("_FRB cookie already set.\r\n");
    }
    else {
        printf( "_FRB cookie and 64kB DMA buffer allocated\r\n");
    }

    long sizereq = 64000 + ( _base->p_tbase - _base->p_lowtpa );

    /* register AltRAM */
    
    int i;
    for( i = 0 ; altram_blocks[i] > 0 ; i +=2 ) {
        if( altram_blocks[i+1] > altram_blocks[i] ) {
            rc = Maddalt( (void*)altram_blocks[i], (altram_blocks[i+1]-altram_blocks[i]) ); // allocate each block
        }
    }
    
    if( rc ) {
        printf("Failed to allocate (all) AltRAM to the system pool. Exiting.\r\n");
        exit(4);
    }

    Ptermres( sizereq, rc);
    return 99;
}
