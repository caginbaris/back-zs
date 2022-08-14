#include "adcHandling.h"
#include "measurements.h"
#include "clib.h"
#include "plib.h"
#include "mlib.h"
#include "faultHandling.h"
#include "pllHandling.h"
#include "references.h"

#define fs 10000.0f
#define pi_ts 1.0f/(fs)



phase V,I;
park  pV,pI;
clarke cV,cI;
sincosValues scVal;


piInit pidInit={0},piqInit={0},pidcInit={0};
piData pidf={0},piqf={0},pidcf={0};

clarke icV;
park   ipV,ipVz;
phase  cOut,final;
phase filteredV={0},filteredVz={0};


//0.5e4 filter
float fofCoefficents5e3[2]={

0.245237275252786,
-0.509525449494429

};

void initControlRoutines(void){
	

	
//**************************************
//**************************************
	
pidInit.parameter.ts=pi_ts;
pidInit.parameter.Kp=0.2f;	
pidInit.parameter.Ki=0.000108f/pi_ts;
pidInit.parameter.atRest=0.0f;	
	
pidInit.limit.refLimitUp=20.0f;
pidInit.limit.refLimitDown=-20.0f;
		

pidInit.limit.rateLimit=2000.0f;
	
pidInit.limit.outputLimitUp=20.0f;	
pidInit.limit.outputLimitDown=-20.0f;

pidInit.flag.refLimitEnable=active;
pidInit.flag.outputLimitEnable=active;
pidInit.flag.feedBackReversal=passive;
pidInit.flag.outputReversal=active;

piControllerInitialization(&pidf,pidInit);


//**************************************
//**************************************
	
piqInit.parameter.ts=pi_ts;
piqInit.parameter.Kp=0.2f;	
piqInit.parameter.Ki=0.000108f/pi_ts;
piqInit.parameter.atRest=0.0f;

piqInit.limit.refLimitUp=20.0f;
piqInit.limit.refLimitDown=-20.0f;
	
piqInit.limit.rateLimit=1.732f;

piqInit.limit.outputLimitUp=20.0f;	
piqInit.limit.outputLimitDown=-20.0f;

piqInit.flag.refLimitEnable=active;
piqInit.flag.outputLimitEnable=active;
piqInit.flag.feedBackReversal=passive;
piqInit.flag.outputReversal=active;

piControllerInitialization(&piqf,piqInit);



//**************************************
//**************************************
	
pidcInit.parameter.ts=pi_ts;
pidcInit.parameter.Kp=0.1f;	
pidcInit.parameter.Ki=0.005f/pi_ts;;
pidcInit.parameter.atRest=0.0;

pidcInit.limit.refLimitUp=200.0f;
pidcInit.limit.refLimitDown=30.0f;

pidcInit.limit.rateLimit=10.0f;
	
pidcInit.limit.outputLimitUp=20.0f;	
pidcInit.limit.outputLimitDown=-20.0f;

pidcInit.flag.refLimitEnable=active;
pidcInit.flag.outputLimitEnable=active;
pidcInit.flag.feedBackReversal=passive;
pidcInit.flag.outputReversal=passive;

piControllerInitialization(&pidcf,pidcInit);



//**************************************	
	



}


void controlRoutines(void){
	


	V.a=adc.ch.Van;
	V.b=adc.ch.Vbn;
	V.c=adc.ch.Vcn;
	
	I.a=adc.ch.Ia;
	I.b=adc.ch.Ib;
	I.c=adc.ch.Ic;
	
	
	tCalculations(pll.theta_comp,&scVal);
	
	clarkeParkTransform(V,&cV,&pV,scVal);
	clarkeParkTransform(I,&cI,&pI,scVal);
	
	
	//d-side
	
	pidcf.signal.ref=ref.Vdc;
	pidcf.signal.feedback=Vdcf;
	piControllerImplementation(&pidcf);
	
	pidf.signal.ref=pidcf.signal.controllerOutput;
	pidf.signal.feedback=pI.d;
	piControllerImplementation(&pidf);

	//q-side
	
	piqf.signal.ref=ref.I;
	piqf.signal.feedback=pI.q;
	piControllerImplementation(&piqf);
	
	//current direction is reverse 
	
	
	FOF(pidf.signal.controllerOutput,ipVz.d,ipV.d,fofCoefficents1e2);
	FOF(piqf.signal.controllerOutput,ipVz.q,ipV.q,fofCoefficents1e2);

	
	//ipV.d=	ipV.d-ref.decouplingTermQ;			
	//ipV.q=	ipV.d+ref.decouplingTermD;
					
					
	inverseClarkeParkTransform(ipV,&icV,&cOut,scVal);

	FOF(adc.ch.Van,filteredVz.a,filteredV.a,fofCoefficents5e3); 
	FOF(adc.ch.Vbn,filteredVz.b,filteredV.b,fofCoefficents5e3); 
	FOF(adc.ch.Vcn,filteredVz.c,filteredV.c,fofCoefficents5e3); 
	
	
	final.a=cOut.a+filteredV.a+ref.thirHarmOut;
	final.b=cOut.b+filteredV.b+ref.thirHarmOut;
	final.c=cOut.c+filteredV.c+ref.thirHarmOut;
	
	//final.a=cOut.a-adc.ch.Van;
	//final.b=cOut.b-adc.ch.Vbn;
	//final.c=cOut.c-adc.ch.Vcn;
	
	


}



