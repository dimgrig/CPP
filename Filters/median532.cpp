#include "median532.h"
#include "limits.h"

void median5_Reset(median5_t* arg)
{    
    arg->idx = 2;
//    arg->input[0] = 0x8000;
//    arg->input[1] = 0x8001;
//    arg->input[2] = 0;
//    arg->input[3] = 0x7FFE;
//    arg->input[4] = 0x7FFF;
    arg->input[0] = INT_MAX;
    arg->input[1] = INT_MAX;
    arg->input[2] = 0;
    arg->input[3] = INT_MIN;
    arg->input[4] = INT_MIN;
}

int32_t median5_Get(median5_t* arg, int32_t val)
{
    arg->input[arg->idx] = val;
    
    if(arg->input[4] < arg->input[0])
    {
        arg->sorted[0] = arg->input[4];
        arg->sorted[4] = arg->input[0];
    }else{
        arg->sorted[0] = arg->input[0];
        arg->sorted[4] = arg->input[4];
    }
    
    if(arg->input[3] < arg->input[1])
    {
        arg->sorted[1] = arg->input[3];
        arg->sorted[3] = arg->input[1];
    }else{
        arg->sorted[1] = arg->input[1];
        arg->sorted[3] = arg->input[3];
    }       
    
    if(arg->sorted[1] < arg->sorted[0])
    {
        int32_t t;
        t = arg->sorted[1]; 
        arg->sorted[1] = arg->sorted[0]; 
        arg->sorted[0] = t;
        
        t = arg->sorted[4];
        arg->sorted[4] = arg->sorted[3];
        arg->sorted[3] = t;
    }               
    
    //now: a[0]<=a[4], a[0]<=a[1]<=a[3]
    //insert a[2] into a[0]<=a[1]<=a[3]
    if(arg->input[2] < arg->sorted[1])
    {
        arg->sorted[2] = arg->sorted[1];
        if(arg->input[2] < arg->sorted[0])
        {
            arg->sorted[1] = arg->sorted[0];
            arg->sorted[0] = arg->input[2];
        }else{
            arg->sorted[1] = arg->input[2];
        }            
    }else{
        if(arg->sorted[3] < arg->input[2])
        {
            arg->sorted[2] = arg->sorted[3]; 
            arg->sorted[3] = arg->input[2];
        }else{
            arg->sorted[2] = arg->input[2];
        }
    }        
    //now: a[0]<=a[4], a[0]<=a[1]<=a[2]<=a[3]
    //insert a[4] into a[0]<=a[1]<=a[2]<=a[3]
    if(arg->sorted[4] < arg->sorted[2])
    {       
        int32_t t;            
        t = arg->sorted[4]; 
        arg->sorted[4] = arg->sorted[3]; 
        arg->sorted[3] = arg->sorted[2];
        if(t < arg->sorted[1])
        {
            arg->sorted[2] = arg->sorted[1]; 
            arg->sorted[1] = t;                
        }else{ 
            arg->sorted[2] = t;
        }
    }else{ 
        if(arg->sorted[4] < arg->sorted[3])
        {
            int32_t t;
            t = arg->sorted[4]; 
            arg->sorted[4] = arg->sorted[3]; 
            arg->sorted[3] = t;           
        }
    }    
    
    arg->idx++;
    if(arg->idx >= 5)
    {
        arg->idx = 0;
    }
    if ((arg->sorted[4] == INT_MAX) || (arg->sorted[0] == INT_MIN)) {
        return val;
    } else {
        return arg->sorted[2];
    }
    //return arg->sorted[2];
}
