
#include "clib.h"


#define _pi 3.1415926535897932384626433832795f
#define _2pi 6.283185307179586476925286766559f
#define wt (_2pi*50.0f)
#define p_Kp 200.0f //12.5
#define p_Ki 20000.0f //100
#define p_fs 50000.0f
#define p_ts 1.0f/(p_fs)
#define p_comp  1.0f*_2pi/(p_fs*0.02f)
#define p_fc_num 0.006244035046343f
#define p_fc_den -0.987511929907314f

void dq2b(float* beta,float d,float q, float theta){
	
    *beta  = -cosf(theta)*d +sinf(theta)*q;
}
void ab2dq(float alpha,float beta,float* d,float* q, float theta){
	
		float sinVal,cosVal;

		sinVal=sinf(theta);
		cosVal=cosf(theta);

    *d=alpha*sinVal-beta*cosVal;
    *q=alpha*cosVal+beta*sinVal;

}





void PLL(float alpha,pll_parameters* pll){
 
    pll->Pout=-pll->df*p_Kp;
    pll->Iout+=-pll->df*p_Ki*p_ts;

    if(pll->Iout>wt){pll->Iout = wt;}
    if(pll->Iout<-wt){pll->Iout = -wt;}

    pll->PIout=pll->Pout+pll->Iout+wt;
    pll->theta+=p_ts*pll->PIout;

    if(pll->theta>=_2pi){pll->theta=0;};
		if(pll->theta<0){pll->theta=0;};
		
		
		
    ab2dq(alpha,pll->beta,&(pll->d),&(pll->q),pll->theta-p_comp);
		
		

    pll->df=(pll->d+pll->dz)*p_fc_num-pll->df*p_fc_den;
    pll->dz=pll->d;

    pll->qf=(pll->q+pll->qz)*p_fc_num-pll->qf*p_fc_den;
    pll->qz=pll->q;
		
		

    dq2b(&(pll->beta),pll->df,pll->qf,pll->theta);
		
		
		
    pll->theta_comp=pll->theta-1.5f*_pi;
    if(pll->theta_comp>=_2pi){pll->theta_comp=pll->theta_comp-_2pi;}
    if(pll->theta_comp<=0){pll->theta_comp=pll->theta_comp+_2pi;}
		
		
		
		

	}
