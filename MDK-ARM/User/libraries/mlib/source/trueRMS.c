
#include "mlib.h"

#define frequency 50.0f
#define period (1.0/frequency)
#define N (samplingFrequency/frequency)
#define invN 1.0f/(N)


// True RMS half cycle
// delayLineArray contains full period circular data of input
// delayLineCounter global counter for true rms calculation
// length of delayLineArray - mult. inverse can be u

float trueRMS_windowed(float rtInput, float *delayLineArray, uint16_t delayLineCounter, uint16_t arrayLength){

	uint16_t i=0;
	float rms = 0.0, rms_sum = 0.0, rms_data=0.0;

	*(delayLineArray+delayLineCounter) = rtInput;

	for (i = 0; i < arrayLength; i++)
	{

		rms_data=*delayLineArray ++;
		rms_sum+=rms_data*rms_data;
		
	}

	rms = sqrt(rms_sum / arrayLength);

	return rms;

}

void trueRMS_sampled(float input,trueRMS_sampled_parameters* rms,uint16_t seq){

    rms->sum+=input*input;

    if(seq==rms->sequence){

        rms->out=sqrt(rms->sum*invN);
        rms->sum=0.0f;

    }


}

