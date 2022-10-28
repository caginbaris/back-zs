#include "mlib.h"
#include "adcHandling.h"
#include "controlRoutines.h"

static phase_cs_in cs_Ain, cs_Bin, cs_Cin;
phase_cs_out cs_Aout={0},cs_Bout={0},cs_Cout={0};

static sos_parameters sos_pDQ[12]={0};
sym_out sym={0};


//10khz k=0.5 SGI

phase Pst={0},Qst={0},Ist={0};
float Qstatcom=0;

static float sosCoefficentsD[]={
	
	0.015543477936186f,  -0.000161925742641f,  -0.015381552193546f,
 -1.968100887830134f,   0.969072426304811f,

};


static float sosCoefficentsQ[]={
	
	0.000163201520801795f,   0.000647678998529623f,   0.000160657955344680f,
	-1.968100887830134f,   0.969072426304811f
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
	
	//Pst.a=cs_Aout.P;
	//Pst.b=cs_Bout.P;
	//Pst.c=cs_Cout.P;
	
	Qst.a=cs_Aout.Q;
	Qst.b=cs_Bout.Q;
	Qst.c=cs_Cout.Q;
	
	
	Ist.a=cs_Aout.I;
	Ist.b=cs_Bout.I;
	Ist.c=cs_Cout.I;
	
	Qstatcom=Qst.a+Qst.b+Qst.c;
	
	
	

}
