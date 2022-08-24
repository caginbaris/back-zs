#include "protections.h"

void initProtections(void){

overCurrentInit();
voltageProtectionsInit();
	
}


void protection(void){

overCurrent();
voltageProtections();
miscProtections();	


}

