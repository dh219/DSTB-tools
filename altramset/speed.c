#include "altramset.h"

const char* name = "DSTB1";

uint32_t enable16mhz = 0xfffe1c;
uint32_t enable8mhz  = 0xfffe1a;

int main( int argc, char *argv[] ) {
    int rc;
    char fname[128];
    char *ptr;
    int mhz16 = 1;

    if( argc < 1 || strlen( argv[0] ) == 0 )
        exit(1);
    
    strncpy( fname, argv[0],sizeof(fname)-1);
    fname[sizeof(fname)-1] = 0;
    ptr = strstr( fname, ".");
    if( ptr )
        ptr[0] = 0; // filename without extension

    if( fname[strlen(fname)-1] == '8' )
        mhz16 = 0;

    rc = check_read_byte( mhz16 ? enable16mhz : enable8mhz );
    if( rc ) {
        printf("DSTB1 not responding.\r\n");
        exit(2);
    }

    printf("DSTB1 set to %s MHz\r\n", mhz16 ? "16.5" : "8" );

    return 0;
}
