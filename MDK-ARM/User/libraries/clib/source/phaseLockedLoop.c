
#include "clib.h"
#include "arm_math.h"

#define _pi 3.1415926535897932384626433832795
#define _2pi 6.283185307179586476925286766559
#define wt (_2pi*50.0)
#define p_Kp 200 //12.5
#define p_Ki 20000.0 //100
#define p_fs 50000.0
#define p_ts 1.0/(p_fs)
#define p_comp  1.0*_2pi/(p_fs*0.02)
#define p_fc_num 0.006244035046343
#define p_fc_den -0.987511929907314

void dq2b(double* beta,double d,double q, double theta){
	
		float sinVal,cosVal;

		arm_sin_cos_f32(theta*57.2957,(&sinVal),(&cosVal));

    *beta  = -cosVal*d +sinVal*q;
}
void ab2dq(double alpha,double beta,double* d,double* q, double theta){
	
		float sinVal,cosVal;

		arm_sin_cos_f32(theta*57.2957,(&sinVal),(&cosVal));
		

    *d=alpha*sinVal-beta*cosVal;
    *q=alpha*cosVal+beta*sinVal;


}





void PLL(double alpha,pll_parameters* pll){
 
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
		
		
		
    pll->theta_comp=pll->theta-1.5*_pi;
    if(pll->theta_comp>=_2pi){pll->theta_comp=pll->theta_comp-_2pi;}
    if(pll->theta_comp<=0){pll->theta_comp=pll->theta_comp+_2pi;}
		
		
		
		

	}
