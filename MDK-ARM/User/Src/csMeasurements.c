#include "mlib.h"
#include "adcHandling.h"

static phase_cs_in cs_Ain, cs_Bin, cs_Cin;
phase_cs_out cs_Aout={0},cs_Bout={0},cs_Cout={0};

static sos_parameters sos_pDQ[12]={0};
sym_out sym={0};


//50khz k=0.5 SGI


static float sosCoefficentsD[]={
	
	0.003135012930297,  -0.000006559091378,  -0.003128453838918,
 -1.993697158102402,   0.993736512624778

};


static float sosCoefficentsQ[]={
	
	0.0000065694008554209,   0.0000262363266723440,   0.0000065487948485740,
	-1.993697158102402,   0.993736512624778
};





void csMeasurement(void){
	
	static uint8_t periodCounter=0;
	
	
	
	SOS(adc.ch.Van,cs_Ain.Vc,sosCoefficentsD,sos_pDQ[0]);
	SOS(adc.ch.Vbn,cs_Bin.Vc,sosCoefficentsD,sos_pDQ[1]);
	SOS(adc.ch.Vcn,cs_Cin.Vc,sosCoefficentsD,sos_pDQ[2]);
	
	SOS(adc.ch.Van,cs_Ain.Vs,sosCoefficentsQ,sos_pDQ[3]);
	SOS(adc.ch.Vbn,cs_Bin.Vs,sosCoefficentsQ,sos_pDQ[4]);
	SOS(adc.ch.Vcn,cs_Cin.Vs,sosCoefficentsQ,sos_pDQ[5]);
	
	
	SOS(adc.ch.Ia,cs_Ain.Ic,sosCoefficentsD,sos_pDQ[6]);
	SOS(adc.ch.Ib,cs_Bin.Ic,sosCoefficentsD,sos_pDQ[7]);
	SOS(adc.ch.Ic,cs_Cin.Ic,sosCoefficentsD,sos_pDQ[8]);
	
	SOS(adc.ch.Ia,cs_Ain.Is,sosCoefficentsQ,sos_pDQ[9]);
	SOS(adc.ch.Ib,cs_Bin.Is,sosCoefficentsQ,sos_pDQ[10]);
	SOS(adc.ch.Ic,cs_Cin.Is,sosCoefficentsQ,sos_pDQ[11]);
	

	
	if(++periodCounter==3){periodCounter=0;}
	if(periodCounter==0){cs_computations(cs_Ain,&cs_Aout);	}
	if(periodCounter==1){cs_computations(cs_Bin,&cs_Bout);	}
	if(periodCounter==2){cs_computations(cs_Cin,&cs_Cout);	}
	

	sym_comp(cs_Ain,cs_Bin,cs_Cin,&sym);
	
	

}