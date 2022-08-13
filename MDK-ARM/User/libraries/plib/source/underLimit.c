#include "plib.h"


void underLimitInitialization(underLimit_inputParameters in, underLimit_outputParameters *out){

    if( ( in.level>0.0f)  &&
        ( in.delay>0.0f)  &&
        ( in.dropout_ratio>=1.0f)&&
        ( (in.dropout_time >=0.0f)    &&  (in.dropout_time<=in.delay))    &&
        ( (in.comm_pick_on_delay >0.0f) &&  (in.comm_pick_on_delay<=in.delay))  &&
        ( in.comm_pick_off_delay >0.0f ) &&
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
void underLimit(float rms,underLimit_inputParameters underLimit_in, underLimit_outputParameters *underLimit_out,uint8_t inhibit,uint8_t reset){

    if (underLimit_out->initialized){

        if (rms < underLimit_in.level){
            underLimit_out->initial_pick_up = 1;
        }

        if (rms > (underLimit_in.level * underLimit_in.dropout_ratio) || inhibit==1){
            underLimit_out->initial_pick_up = 0;
        }


        off_delay(underLimit_out->initial_pick_up, &(underLimit_out->pick_up));

        on_off_delay2(underLimit_out->pick_up.output,&(underLimit_out->comm_pick_up));

        on_delay (underLimit_out->pick_up.output, &(underLimit_out->trip));


        if (underLimit_out->trip.output == 1){

            underLimit_out->trip_latch = 1;

        }


        if(underLimit_out->initial_pick_up==0 && reset==1){

            underLimit_out->trip_latch=0;

        }

    }

}


