
#include "mlib.h"
#include "arm_math.h"

void cs_computations(phase_cs_in p_in, phase_cs_out *p_out ){

  //p_out->V =sqrt((p_in.Vc)*(p_in.Vc) + (p_in.Vs)*(p_in.Vs))*isqrt2;
  p_out->I =sqrt((p_in.Ic)*(p_in.Ic) + (p_in.Is)*(p_in.Is))*isqrt2;
	

	//p_out->P	=((p_in.Vc)*(p_in.Ic) +(p_in.Vs)*(p_in.Is))*i2;
	//p_out->Q	=((p_in.Vs)*(p_in.Ic) -(p_in.Vc)*(p_in.Is))*i2;

}



void sym_comp( phase_cs_in pa,  phase_cs_in pb, phase_cs_in pc, sym_out*sym){

	float temp_r,temp_i;

	temp_r=pa.Vc + pb.Vc*sym_r +   pc.Vc*sym_r;
	temp_i=pb.Vs*sym_i - pc.Vs*sym_i;
	
	sym->V0  =(pa.Vc + pb.Vc + 	pc.Vc)*sym_i3;
	sym->V1  =(temp_r - temp_i)*sym_i3;
	sym->V2 =(temp_r + temp_i)*sym_i3;


	temp_r=pa.Ic + pb.Ic*sym_r +   pc.Ic*sym_r;
	temp_i=pb.Is*sym_i - pc.Is*sym_i;

	sym->I0  =(pa.Ic + pb.Ic + 	pc.Ic)*sym_i3;
	sym->I1  =(temp_r -   temp_i)*sym_i3;
	sym->I2 =(temp_r +   temp_i)*sym_i3;
	
	
}

void sym_mag( sym_out sym,  sym_out *sym_back,  sym_out *sym_rms  ){

	float temp;

	temp = -(sym.V0-sym_back->V0)*sym_rms_scale;
	sym_rms->V0=sqrt(temp*temp+sym.V0*sym.V0)*isqrt2;
	sym_back->V0=sym.V0;

	temp = -(sym.V1-sym_back->V1)*sym_rms_scale;
	sym_rms->V1=sqrt(temp*temp+sym.V1*sym.V1)*isqrt2;
	sym_back->V1=sym.V1;

	temp = -(sym.V2-sym_back->V2)*sym_rms_scale;
	sym_rms->V2=sqrt(temp*temp+sym.V2*sym.V2)*isqrt2;;
	sym_back->V2=sym.V2;


	temp =- (sym.I0-sym_back->I0)*sym_rms_scale;
	sym_rms->I0=sqrt(temp*temp+sym.I0*sym.I0)*isqrt2;;
	sym_back->I0=sym.I0;

	temp = -(sym.I1-sym_back->I1)*sym_rms_scale;
	sym_rms->I1=sqrt(temp*temp+sym.I1*sym.I1)*isqrt2;;
	sym_back->I1=sym.I1;

	temp = -(sym.I2-sym_back->I2)*sym_rms_scale;
	sym_rms->I2=sqrt(temp*temp+sym.I2*sym.I2)*isqrt2;;
	sym_back->I2=sym.I2;


}




float thermal_status(float rms, thermal_parameters therm, float mem){

	float temp;
	float t_constant;

	if(therm.tau>1.0) {t_constant = therm.ts / therm.tau;}else{t_constant=0.0;}

	if(therm.Inom * therm.k>1.0) {
			
		temp = t_constant * (rms*rms) / (therm.Inom * therm.Inom * therm.k * therm.k) + mem * (1.0 - t_constant);
			
	}
	
	mem = temp;

	return temp;

}




float max3p(float p1, float p2, float p3){

	float max=p1;
	
	if(p2>max){max=p2;}
	if(p3>max){max=p3;}


return max;
	
}


float min3p(float p1, float p2, float p3){

	float min=p1;
	
	if(p2<min){min=p2;}
	if(p3<min){min=p3;}


return min;
	
}




