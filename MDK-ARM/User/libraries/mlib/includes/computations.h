#ifndef __computations_h
#define __computations_h

#define i2     0.5f
#define isqrt2 0.7071067811865475f

#define sym_i3 						0.333333333333333f
#define sym_r  						-0.5f
#define sym_i  						0.8660254037844386f
#define sym_rms_scale  		7.9577471545947667884441881686257f


typedef struct phase_cs_in{

		float  Vc;
		float  Vs;
		float  Ic;
		float  Is;
	
}phase_cs_in;

typedef struct phase_cs_out{

		float  V;
		float  I;
		float  P;
		float  Q;

}phase_cs_out;


typedef struct sym_out{

	float  V1;
	float  V2;
	float  V0;

	float  I1;
	float  I2;
	float  I0;

}sym_out;


typedef struct thermal_parameters{

	float  Inom; // 0.1 to 4*Inom- def 1.1 k-factor*Inom_obj
	float  k;
	float  tau;
	float  ts;

}thermal_parameters;


//prototypes
void cs_computations(phase_cs_in p_in,phase_cs_out *p_out );
void sym_comp(phase_cs_in pa, phase_cs_in pb,phase_cs_in pc,sym_out*sym);
void sym_mag(sym_out sym, sym_out *sym_back, sym_out *sym_rms  );
float thermal_status(float rms,thermal_parameters therm, float mem);
float max3p(float p1, float p2, float p3);
float min3p(float p1, float p2, float p3);
//macros

#define THERMAL_STATUS(rms,thermalData,out) out=thermal_status(rms,thermalData,out);





#endif

