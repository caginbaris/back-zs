#include "plib.h"


void overLimitInitialization(overLimit_inputParameters in, overLimit_outputParameters *out){

    if( ( in.level>0.0)  &&
        ( in.delay>0.0)  &&
        ( (in.dropout_ratio>0.0) &&  (in.dropout_ratio<=1.0)) &&
        ( (in.dropout_time >=0.0)    &&  (in.dropout_time<=in.delay))    &&
        ( (in.comm_pick_on_delay >0.0) &&  (in.comm_pick_on_delay<=in.delay))  &&
        ( in.comm_pick_off_delay >0.0 ) &&
        ( in.fs >0 ) &&
        ( out->initial_pick_up==0   &&
          out->pick_up.output==0    &&
          out->trip.output==0   &&
          out->trip_latch==0)){


        out->pick_up.qualSample=in.fs*in.dropout_time;
        out->comm_pick_up.onQualSample=in.fs*in.comm_pick_on_delay;
        out->comm_pick_up.offQualSample=in.fs*in.comm_pick_off_delay;
        out->trip.qualSample=in.fs*in.delay;

        out->initialized=1;


    }else{

        out->initialized=0;
    }
}
void overLimit(float rms,overLimit_inputParameters overLimit_in, overLimit_outputParameters *overLimit_out,uint8_t inhibit,uint8_t reset){

    if (overLimit_out->initialized){

        if (rms > overLimit_in.level){
            overLimit_out->initial_pick_up = 1;
        }

        if (rms < (overLimit_in.level * overLimit_in.dropout_ratio) || inhibit==1){
            overLimit_out->initial_pick_up = 0;
        }


        off_delay(overLimit_out->initial_pick_up, &(overLimit_out->pick_up));

        on_off_delay2(overLimit_out->pick_up.output,&(overLimit_out->comm_pick_up));

        on_delay (overLimit_out->pick_up.output, &(overLimit_out->trip));


        if (overLimit_out->trip.output == 1){

            overLimit_out->trip_latch = 1;

        }


        if(overLimit_out->initial_pick_up==0 && reset==1){

            overLimit_out->trip_latch=0;

        }

    }

}


