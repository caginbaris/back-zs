#include "plib.h"


void on_delay(uint8_t input, delay_parameters* p){

    if (input == 1 && p->output == 0){

        p->count++;

        if (p->count == p->qualSample){
            p->output = 1;
            p->count = 0;
        }

    }

    else{
        p->count = 0;
    }

    if (input == 0){
        p->output = 0;
        p->count = 0;
    }


}
void off_delay(uint8_t input, delay_parameters* p){

    if (input == 0 && p->output == 1){

        p->count++;

        if (p->count == p->qualSample){
            p->output = 0;
            p->count = 0;
        }

    }

    else{
        p->count = 0;
    }

    if (input == 1){
        p->output = 1;
        p->count = 0;
    }


}
void on_off_delay(uint8_t input, delay_parameters* p){

    if (input  ^ p->output ){

        p->count++;

        if (p->count == p->qualSample){
            p->output = input;
            p->count = 0;
        }

    }

    else{
        p->count = 0;
    }


}
void on_off_delay2(uint8_t input, delay_parameters2* p){


    if (input==1 && p->output==0 ){
        p->count++;

        if (p->count == p->onQualSample){
            p->output = 1;

        }

    }


    if (input == 0 && p->output==1){
        p->count++;

        if ((p->count) == p->offQualSample){
            p->output = 0;
        }

    }


    if(!(input^p->output)){p->count=0;}


}
void low2highTransition(uint8_t input, transition_parameters* p){

    if(p->back==0 && input==1){

        p->output=1;

    }else{

        p->output=0;
    }

    p->back=input;
}
void high2lowTransition(uint8_t input, transition_parameters* p){

    if(p->back==1 && input==0){

        p->output=1;

    }else{

        p->output=0;
    }

    p->back=input;


}
void fToggle(uint8_t input, delay_parameters* p) {

    if (input == 1) {
    p->count++;

    if (p->count == p->qualSample) {

        p->output ^= 1;
        p->count = 0;
    }

    }
}


void ui_limiter(uint16_t* parameter,uint16_t downLimit,uint16_t upLimit){


	if((*parameter)<=downLimit){*parameter=downLimit;}
	if((*parameter)>  upLimit){*parameter=  upLimit;}


}



void f_limiter(float* parameter,float downLimit,float upLimit){


	if((*parameter)<=downLimit){*parameter=downLimit;}
	if((*parameter)>  upLimit){*parameter=  upLimit;}


}


void d_limiter(double* parameter,double downLimit,double upLimit){


	if((*parameter)<=downLimit){*parameter=downLimit;}
	if((*parameter)>  upLimit){*parameter=  upLimit;}


}

