#ifndef __trueRMS_h
#define __trueRMS_h

#include <stdint.h>


typedef struct trueRMS_sampled_parameters{

    float sum;
    float out;
    uint16_t  sequence;


}trueRMS_sampled_parameters;

void trueRMS_sampled(float input,trueRMS_sampled_parameters* rms,uint16_t seq);



#endif


