#include "LEDs.h"
#include "ios.h"
#include "states.h"
#include "faultHandling.h"
#include "pllHandling.h"
#include "references.h"
#include "measurements.h"
#include "protections.h"
#include "ios.h"
#include "controlRoutines.h"

void mainFlow(void){

		//measurements();
		//protection();
		//pllHandling();
		ios();
		state_chart();
		//faultHandling();
		//references();
		//controlRoutines();


}
