#ifndef __computations_h
#define __computations_h

#define i2     0.5
#define isqrt2 0.7071067811865475

#define sym_i3 						0.333333333333333
#define sym_r  						-0.5
#define sym_i  						0.8660254037844386
#define sym_rms_scale  		7.9577471545947667884441881686257


typedef struct phase_cs_in{

		double  Vc;
		double  Vs;
		double  Ic;
		double  Is;
	
}phase_cs_in;

typedef struct phase_cs_out{

		double  V;
		double  I;
		double  P;
		double  Q;

}phase_cs_out;


typedef struct sym_out{

	double  V1;
	double  V2;
	double  V0;

	double  I1;
	double  I2;
	double  I0;

}sym_out;


typedef struct thermal_parameters{

	double  Inom; // 0.1 to 4*Inom- def 1.1 k-factor*Inom_obj
	double  k;
	double  tau;
	double  ts;

}thermal_parameters;


//prototypes
void cs_computations(phase_cs_in p_in,phase_cs_out *p_out );
void sym_comp(phase_cs_in pa, phase_cs_in pb,phase_cs_in pc,sym_out*sym);
void sym_mag(sym_out sym, sym_out *sym_back, sym_out *sym_rms  );
double thermal_status(double rms,thermal_parameters therm, double mem);
double max3p(double p1, double p2, double p3);
double min3p(double p1, double p2, double p3);
//macros

#define THERMAL_STATUS(rms,thermalData,out) out=thermal_status(rms,thermalData,out);





#endif

