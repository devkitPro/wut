// Defines needed to compile libgcc2.c
#define BITS_PER_UNIT 8
#define LONG_DOUBLE_TYPE_SIZE 64
#define MIN_UNITS_PER_WORD 4
typedef unsigned int size_t;

// Unsigned 64 bit division:
#define L_udivdi3
