#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#ifndef __linux__
#include <osbind.h>
#endif

#define TRUE 1
#define FALSE 0

typedef uint32_t LONG;
typedef uint16_t WORD;

int check_read_byte( long add );