
#ifndef __automata_h
#define __automata_h

#include <stdint.h>



typedef struct delay_parameters {

    uint8_t output;
    uint32_t qualSample;
    uint32_t count;

}delay_parameters;

typedef struct delay_parameters2 {

    uint8_t output;
    uint32_t onQualSample;
    uint32_t offQualSample;
    uint32_t count;

}delay_parameters2;



typedef struct transition_parameters {

    uint8_t output;
    uint8_t back;

}transition_parameters;


void on_delay(uint8_t input, delay_parameters* p);
void off_delay(uint8_t input, delay_parameters* p);
void on_off_delay(uint8_t input, delay_parameters* p);
void on_off_delay2(uint8_t input, delay_parameters2* p);
void low2highTransition(uint8_t input, transition_parameters* p);
void high2lowTransition(uint8_t input, transition_parameters* p);
void fToggle(uint8_t input, delay_parameters* p); 
	

void ui_limiter(uint16_t* parameter,uint16_t downLimit,uint16_t upLimit);
void f_limiter(float* parameter,float downLimit,float upLimit);



//macros
#define ui_LIMITER(x,down,up)								ui_limiter(&x,down,up)
#define f_LIMITER(x,down,up)								f_limiter(&x,down,up)

#endif

