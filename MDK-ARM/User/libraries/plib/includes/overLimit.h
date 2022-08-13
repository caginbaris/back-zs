
#ifndef __overLimit_h
#define __overLimit_h

#include "plib.h"


typedef struct overLimit_inputParameters {

    float level;
    float delay;
    float dropout_ratio;
    float dropout_time;
    float comm_pick_on_delay;
    float comm_pick_off_delay;

    uint32_t fs;


}overLimit_inputParameters;


typedef struct overLimit_outputParameters {

    delay_parameters pick_up;
    delay_parameters2 comm_pick_up;
    delay_parameters trip;

    uint32_t initial_pick_up:1;
    uint32_t trip_latch:1;
    uint32_t initialized:1;


}overLimit_outputParameters;


void overLimitInitialization(overLimit_inputParameters in, overLimit_outputParameters *out);
void overLimit(float rms,overLimit_inputParameters overLimit_in, overLimit_outputParameters *overLimit_out,uint8_t inhibit,uint8_t reset);



#endif


