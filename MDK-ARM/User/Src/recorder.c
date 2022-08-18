#include "measurements.h"
#include "adcHandling.h"

recordedVariables rec={0};


void recorder(){
	
	rec.rec_rmsIa=tRMS[rms_Ia].out;
	rec.rec_rmsIb=tRMS[rms_Ib].out;
	rec.rec_rmsIc=tRMS[rms_Ic].out;
	
	rec.rec_csIa=cs_Aout.I;
	rec.rec_csIb=cs_Bout.I;
	rec.rec_csIc=cs_Cout.I;
	
	
	rec.rec_Ia=adc.ch.Ia;
	rec.rec_Ib=adc.ch.Ib;
	rec.rec_Ic=adc.ch.Ic;
	
	
	
	rec.rec_mIa=meanValueIa;
	rec.rec_mIb=meanValueIb;
	rec.rec_mIc=meanValueIc;
	
	
	
	rec.rec_rmsVa=tRMS[rms_Van].out;
	rec.rec_rmsVb=tRMS[rms_Vbn].out;
	rec.rec_rmsVc=tRMS[rms_Vcn].out;
	
	rec.rec_Vdc=adc.ch.Vdc;
	
	rec.rec_pid=pidf;
	rec.rec_piq=piqf;
	rec.rec_pidc=pidcf;
	
	rec.rec_pI=pI;
	rec.rec_pV=pV;
	
	rec.rec_final.a=tRMS[17].out;
	rec.rec_final.b=tRMS[18].out;
	rec.rec_final.c=tRMS[19].out;
	
	
	rec.rec_cOut.a=tRMS[20].out;
	rec.rec_cOut.b=tRMS[21].out;
	rec.rec_cOut.c=tRMS[22].out;
	
	


}
