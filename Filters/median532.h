#ifndef MED5
#define MED5

#include "stdint.h"

typedef struct
{
    int32_t input[5];
    uint8_t idx;
    int32_t sorted[5];
} median5_t;

void median5_Reset(median5_t* arg);
int32_t median5_Get(median5_t* arg, int32_t val);

#endif
