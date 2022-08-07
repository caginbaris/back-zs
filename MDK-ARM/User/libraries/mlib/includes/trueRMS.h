#ifndef __trueRMS_h
#define __trueRMS_h

#include <stdint.h>


typedef struct trueRMS_sampled_parameters{

    double sum;
    double out;
    uint16_t  sequence;


}trueRMS_sampled_parameters;

void trueRMS_sampled(double input,trueRMS_sampled_parameters* rms,uint16_t seq);



#endif


