
#include "mlib.h"


double filtering(double rtInput,  double *coeff, uint16_t coeffLength, double *zValues){

	uint16_t i;
  double *z1_ptr,*z2_ptr,*coeff_ptr;
  double output;

	z1_ptr=zValues; 		//background data
	z2_ptr=z1_ptr; 		//data update
	coeff_ptr=coeff+coeffLength-1;  //last element


	output=(*z1_ptr++) *(*coeff_ptr--);

	for(i=2;i<coeffLength;i++){
	
	*z2_ptr++ =*z1_ptr;
	output+=(*z1_ptr++) *(*coeff_ptr--);

	}


	output+=rtInput *(*coeff_ptr);
	*z2_ptr=rtInput;

	return(output);

}


//def first order section filter implementations 
//1 	coeff is sequenced fof coefficents suxh --> b1,a1 in array
//2.0 function invocation shown below  

double fof_implementation(double rtInput,double* xz,double yz,  double *coeffs)
{
	double y;
	
	y=(*coeffs)*(rtInput+(*xz))-(*(coeffs+1)*(yz));
		
	(*xz)=rtInput;
	
	return y;
	
};





//def second order section filter implementations 
//1 	coeff is sequenced sos coefficents suxh --> b1,b2,b3,a2,a3 order in array
//2.0 function invocation shown below  
//2.1 "output=sos_implementation(input(real-time),output(lef-side),coeff_data(array_name),SOS2data(different for all parameters ));

double sos_implementation(double x ,double yBack,   double *coeffs, sos_parameters *back){

	double y;

	
	y=x*(*coeffs)	+	(back->xz1)	*(*(coeffs+1))		+	(back->xz2)*(*(coeffs+2))
								- (yBack)			*(*(coeffs+3))		-	(back->yz2)*(*(coeffs+4));

	
	back->yz2=yBack;
	back->xz2=back->xz1;
	back->xz1=x;
	
	return y;
	
}








