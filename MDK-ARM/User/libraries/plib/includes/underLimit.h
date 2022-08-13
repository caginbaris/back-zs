
#ifndef __underLimit_h
#define __underLimit_h

#include "plib.h"

typedef struct underLimit_inputParameters {

    float level;
    float delay;
    float dropout_ratio;
    float dropout_time;
    float comm_pick_on_delay;
    float comm_pick_off_delay;

    uint32_t fs;


}underLimit_inputParameters;


typedef struct underLimit_outputParameters {

    delay_parameters pick_up;
    delay_parameters2 comm_pick_up;
    delay_parameters trip;

    uint32_t initial_pick_up:1;
    uint32_t trip_latch:1;
    uint32_t initialized:1;


}underLimit_outputParameters;

void underLimitInitialization(underLimit_inputParameters in, underLimit_outputParameters *out);
void underLimit(float rms,underLimit_inputParameters underLimit_in, underLimit_outputParameters *underLimit_out,uint8_t inhibit,uint8_t reset);



#endif


