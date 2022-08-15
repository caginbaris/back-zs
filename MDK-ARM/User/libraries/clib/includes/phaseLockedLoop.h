#include <math.h>
#include <stdint.h>

#ifndef __phaseLockedLoop_h
#define __phaseLockedLoop_h


#define _pi 3.1415926535897932384626433832795f
#define _2pi 6.283185307179586476925286766559f
#define wt (_2pi*50.0f)
#define p_Kp 100f //12.5
#define p_Ki 1000.0f //100
#define p_fs 10000.0f
#define p_ts 1.0f/(p_fs)
#define p_comp  1.0f*_2pi/(p_fs*0.02f) //cau
#define p_fc_num 0.059190703818405f
#define p_fc_den -0.881618592363189f

//pll sogi parameters

#define numd0 0.015543477936186f
#define numd1 -0.000161925742641f
#define numd2 -0.015381552193546f


#define dend1 -1.968100887830134f
#define dend2 0.969072426304811f


#define numq0 0.000163201520801795f
#define numq1 0.000647678998529626f
#define numq2 0.000160657955344682f


#define denq1 -1.968100887830134f
#define denq2 0.969072426304811f

#define pts 0.0001f //for 10khz
#define pw (2*3.14159*50)

//pll comp
#define numy11 0.0f
#define numy12 13.922355179431557f
#define numy13 0.0f

#define deny11 1.0f
#define deny12 -0.939116505787091f
#define deny13 0.0f


#define numy21 1.0f
#define numy22 -1.991976296933364f
#define numy23 0.991992388700795f

#define deny21 1.0f
#define deny22 -1.884687779838775f
#define deny23 0.888001781189238f

#define numy31 1.0f
#define numy32 -1.983570692570230f
#define numy33 0.987492089040489f

#define deny31 1.0f
#define deny32 -1.945572929181945f
#define deny33 0.945572929184555f


typedef struct pll_parameters {

    float yd;
    float xdz1;
    float xdz2;
    float ydz1;
    float ydz2;


    float yq;
    float xqz1;
    float xqz2;
    float yqz1;
    float yqz2;

    float q;

    float y1;

    float y1z1;
    float y1z2;

    float x1z1;
    float x1z2;


    float y2;

    float y2z1;
    float y2z2;

    float x2z1 ;
    float x2z2 ;


    float y3 ;

    float y3z1 ;
    float y3z2 ;

    float x3z1 ;
    float x3z2 ;

    float out;

		float theta; 
    float theta_unc; //uncompansated theta


}pll_parameters;


void PLL(float alpha, pll_parameters *pll);

#endif


