#ifndef RUNNING_AVERAGE_H
#define RUNNING_AVERAGE_H

#define worktype int32_t

#define AVERAGING_SIZE 10
#define BYPASS 1
#define NOBYPASS 0

#include "stdint.h"
#include "string.h"

typedef struct
{
    uint8_t Ready;
    uint16_t Counter;
    worktype Array[AVERAGING_SIZE];
    worktype Sum;        
    worktype Result;
}Averager_t;

void InitAverage(Averager_t* arg)
{
    arg->Ready = 0;    
    arg->Sum = 0;
    arg->Counter = 0;
}

worktype GetAverage(Averager_t* arg1, worktype arg2, uint8_t bypass)
{    
    if(bypass == BYPASS)
    {
        arg1->Ready = 0;        
        arg1->Array[0] = arg2;
        arg1->Sum = arg2;
        arg1->Counter = 0;
        arg1->Result = arg2;
    }else{
        if (++arg1->Counter >= AVERAGING_SIZE)
        {
            arg1->Counter = 0;
            arg1->Ready = 1;
        }
//        if(arg1->Ready) {
//            if (++arg1->Counter >= AVERAGING_SIZE)
//            {
//                arg1->Counter = 0;
//                arg1->Ready = 1;
//            }
//        } else {
//            if (++arg1->Counter > AVERAGING_SIZE)
//            {
//                arg1->Counter = 0;
//                arg1->Ready = 1;
//            }
//        }
        if(arg1->Ready)
        {
            arg1->Sum -= arg1->Array[arg1->Counter];
            arg1->Sum += arg2;
            arg1->Array[arg1->Counter] = arg2;
            arg1->Result = arg1->Sum / AVERAGING_SIZE;
        }else{
            if(arg1->Counter <= 1)
            {
                arg1->Sum = 2 * arg2;
                arg1->Array[0] = arg2;
                arg1->Array[1] = arg2;
                arg1->Result = arg2;
            }else{
                arg1->Sum += arg2;
                arg1->Array[arg1->Counter] = arg2;
                arg1->Result = arg1->Sum / (arg1->Counter + 1);
            }
//            arg1->Sum += arg2;
//            arg1->Array[arg1->Counter - 1] = arg2;
//            arg1->Result = arg1->Sum / (arg1->Counter);
        }        
    }
    return arg1->Result;
}

#endif //RUNNING_AVERAGE_H
