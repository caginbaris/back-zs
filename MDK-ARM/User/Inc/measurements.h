#ifndef __measurement_H__
#define __measurement_H__

#include "mlib.h"
#include "clib.h"


void frequencyMeasurement(void);
void rmsMeasurement(void);
void csMeasurement(void);
void dcMeasurement(void);


void measurement(void);


typedef enum rmsChannel {   rms_Ia=0,
                            rms_Ib=1,
                            rms_Ic=2,
														rms_Van=3,
                            rms_Vbn=4,
                            rms_Vcn=5,
														rms_Vab=6,
                            rms_Vbc=7,
                            rms_Vca=8,
														rms_Vdc=9,
                            rms_V0=10,
														rms_V1=11,
	                          rms_V2=12,
														rms_I0=13,
														rms_I1=14,
	                          rms_I2=15,
														rms_dcr=16

                       
}rmsChannel_Type;

extern rmsChannel_Type rmsSeq;
extern trueRMS_sampled_parameters tRMS[28];
extern phase_cs_out cs_Aout,cs_Bout,cs_Cout;
extern sym_out sym;
extern float dcRipple, dcAverage,Vdcf;

extern float fofCoefficents1e3[2];
extern float fofCoefficents1e2[2];
extern float fofCoefficents1e0[2];





extern uint16_t calculationCounter;


typedef struct recordedVariables{
	

		float rec_rmsIa;
		float rec_rmsIb;
		float rec_rmsIc;
	
		float rec_csIa;
		float rec_csIb;
		float rec_csIc;
	
		float rec_Ia;
		float rec_Ib;
		float rec_Ic;
	
		float rec_mIa;
		float rec_mIb;
		float rec_mIc;

		float rec_rmsVa;
		float rec_rmsVb;
		float rec_rmsVc;
	
		float rec_Vdc;
		
		piData rec_pid;
		piData rec_piq;
		piData rec_pidc;
		
		park rec_pV;
		park rec_pI;
		
		phase rec_final;
		phase rec_pos;
		phase rec_neg;
		
		float thirdHarm;
		
	
}recordedVariables; 

void measurements(void);
void recorder(void);

extern float meanValueIa;
extern float meanValueIb;
extern float meanValueIc;


extern piData pidf,piqf,pidcf;
extern park  pV,pI;
extern phase  cOut,final;



#endif

