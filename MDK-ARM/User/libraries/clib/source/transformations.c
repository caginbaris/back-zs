
#include "clib.h"


void tCalculations(float theta,sincosValues* tVal){
	
	float sinValue,cosValue;
	
	sinValue=sinf(theta);
	cosValue=cosf(theta);
	
	tVal->sinVal=sinValue;
	tVal->cosVal=cosValue;


}

void clarkeParkTransform(phase x, clarke* c, park* p ,sincosValues tVal){
	
	c->alpha=sqrt_2over3_*(x.a-i2*(x.b+x.c));
	c->beta =sqrt_1over2_*(x.b-x.c);
	
	p->d=c->alpha*tVal.sinVal-c->beta*tVal.cosVal;
	p->q=c->alpha*tVal.cosVal+c->beta*tVal.sinVal;
	
}



void inverseClarkeParkTransform(park p, clarke* c, phase* x ,sincosValues tVal){
	
	c->alpha =  tVal.sinVal*p.d +tVal.cosVal*p.q;
	c->beta  = -tVal.cosVal*p.d +tVal.sinVal*p.q;

	x->a  =  sqrt_2over3_ *c->alpha;
	x->b  = -sqrt_2over12_*c->alpha + sqrt_1over2_*c->beta;
	x->c  = -sqrt_2over12_*c->alpha - sqrt_1over2_*c->beta;
	
}



