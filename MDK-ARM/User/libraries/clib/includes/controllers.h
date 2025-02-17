#ifndef __controllers_h
#define __controllers_h

#include <stdint.h>

typedef struct piInit{
	
	struct{
		
		float Kp;
		float Ki;
		float ts;
		float atRest;

	}parameter;


	struct{
		
		float refLimitUp;
		float refLimitDown;
		
		float rateLimit;
		
		float outputLimitUp;
		float outputLimitDown;

	}limit;
	
	
	struct{
		
		
		uint32_t refLimitEnable:1;
		uint32_t outputLimitEnable:1;
		uint32_t feedBackReversal:1;
		uint32_t outputReversal:1;
		
		uint32_t rem:28;
		
	}flag;


}piInit;



typedef struct piData{

	struct{	

		float ref;
		float ref_rateLimited;
		float feedback;	
		float controllerOutput;
		float atRestOutput;

	}signal;

	struct{
		
		float error;
		float Pout;
		float Iout;

	}state;


	struct{
		
		float Kp;
		float Ki;
		float ts;

	}parameter;


	struct{
		
		float refLimitUp;
		float refLimitDown;
		
		float rateLimit;
		
		float outputLimitUp;
		float outputLimitDown;

	}limit;
	

	struct{
		
		uint32_t enable:1;
		
		uint32_t refLimitEnable:1;
		uint32_t outputLimitEnable:1;
		
		uint32_t feedBackReversal:1;
		uint32_t outputReversal:1;
		
		uint32_t refLimiting:1;
		uint32_t outputLimiting:1;


		uint32_t rem:25;
		
	}flag;


}piData;



void piControllerInitialization(piData* pi,piInit init);
void piControllerImplementation(piData* pi);





#endif


