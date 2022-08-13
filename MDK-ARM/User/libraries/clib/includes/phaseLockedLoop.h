#ifndef __phaseLockedLoop_h
#define __phaseLockedLoop_h


typedef struct pll_parameters{

    float d;
    float df;
    float dz;
    float q;
    float qf;
    float qz;
    float beta;
    float Pout;
    float Iout;
    float PIout;
    float theta;
    float theta_comp;
		
}pll_parameters;


void PLL(float alpha,pll_parameters* pll);


#endif


