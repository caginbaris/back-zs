#include "adcHandling.h"
#include "measurements.h"
#include "clib.h"
#include "plib.h"
#include "mlib.h"
#include "faultHandling.h"
#include "pllHandling.h"
#include "references.h"
#include "controlRoutines.h"

#define fs 10000.0f
#define pi_ts 1.0f/(fs)
#define wL (3.14159f*0.0008f)

phase V,I;

park  pV,pI;
park  pVn,pIn;

park  pVf,pIf;
park  pVnf,pInf;
park  pVnf_lp,pInf_lp;

dqFilterBuffers vBuf={0},iBuf={0};
dqFilterBuffers vnBuf={0},inBuf={0};

clarke cV,cI;
clarke cVn,cIn;

sincosValues scVal;
sincosValues scValn;


piInit pidInit={0},piqInit={0},pidcInit={0};
piData pidf={0},piqf={0},pidcf={0};
piData pidnf={0},piqnf={0};

clarke icV;
park   ipV;

clarke icVn;
park   ipVn;

phase  posOut,negOut,final;

decouplingTerms dec={0};

float fofBuffer4NegSeq[4]={0};



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
piControllerInitialization(&pidnf,pidInit);// limits can be different

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
piControllerInitialization(&piqnf,pidInit); // limits can be different



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
	
	
	tCalculations(pll.theta,&scVal);
	
	//neg seq thetas //cau check for transform block
	scValn.sinVal=-scVal.sinVal; 
	scValn.cosVal= scVal.cosVal;
	
	clarkeParkTransform(V,&cV,&pV,scVal);
	clarkeParkTransform(I,&cI,&pI,scVal);
	
	clarkeParkTransform(V,&cVn,&pVn,scValn); // rotating with negative sign
	clarkeParkTransform(I,&cIn,&pIn,scValn); // rotating with negative sign	
	
	//dq filtering
	
	dqFiltering(pV,&pVf,&vBuf);
	dqFiltering(pI,&pIf,&iBuf);
	
	dqFiltering(pVn,&pVnf,&vnBuf);
	dqFiltering(pIn,&pInf,&inBuf);
	
	// additional lp for neg seq.
	FOF(pVnf.d,fofBuffer4NegSeq[0],pVnf_lp.d,fofCoefficents1e2);
	FOF(pVnf.q,fofBuffer4NegSeq[1],pVnf_lp.q,fofCoefficents1e2);
	
	FOF(pInf.d,fofBuffer4NegSeq[2],pInf_lp.d,fofCoefficents1e2);
	FOF(pInf.q,fofBuffer4NegSeq[3],pInf_lp.q,fofCoefficents1e2);
	
	//cau check for pi init
	
	//*****for positive squence -start
	//***d-side
	//dc pi
	pidcf.signal.ref=ref.Vdc_opt;
	pidcf.signal.feedback=Vdcf;
	piControllerImplementation(&pidcf);
	
	//d-pi
	pidf.signal.ref=pidcf.signal.controllerOutput; //cau check for sign
	pidf.signal.feedback=pIf.d;
	piControllerImplementation(&pidf);

	//***q-side
	
	//q-pi
	piqf.signal.ref=ref.I;
	piqf.signal.feedback=pIf.q;
	piControllerImplementation(&piqf);
	
	//*****for positive squence -end
	
	
	//*****for negative squence -start
	//***d-side
	//d-pi
	pidnf.signal.ref=0;
	pidnf.signal.feedback=pInf_lp.d;//cau
	piControllerImplementation(&pidnf);

	//***q-side
	
	//q-pi
	piqnf.signal.ref=0;
	piqnf.signal.feedback=pInf_lp.q;
	piControllerImplementation(&piqnf);
	
	//*****for negative squence -end

	//decoupling terms (sign included)
	
	dec.Pd= -pIf.q*wL;
	dec.Pq=  pIf.d*wL;
	
	dec.Nd=  pInf_lp.q*wL; 
	dec.Nq= -pInf_lp.d*wL;
	
	//sum of references
	
	ipV.d=pidf.signal.controllerOutput + dec.Pd + pVf.d;
	ipV.q=piqf.signal.controllerOutput + dec.Pq + pVf.q;
	
	ipVn.d=pidnf.signal.controllerOutput + dec.Nd + pVnf_lp.d;
	ipVn.q=piqnf.signal.controllerOutput + dec.Nq + pVnf_lp.q;

	inverseClarkeParkTransform(ipV,&icV,&posOut,scVal);
	inverseClarkeParkTransform(ipVn,&icVn,&negOut,scValn); //rotating with negative sign
	
	
	final.a	=	posOut.a	+	negOut.a  +	ref.thirdHarmOut;
	final.b	=	posOut.b	+	negOut.b	+	ref.thirdHarmOut;
	final.c	=	posOut.c	+	negOut.c  + ref.thirdHarmOut;
	

	
	


}



