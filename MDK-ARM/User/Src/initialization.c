#include "functionPrototypes.h"


void initialization(void){
	
init_ADC();
initProtections();
initControlRoutines(); //cau check for correct initialization	
initReferences();
initComm();	

// add pi inits

}