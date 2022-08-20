#include "main.h"
#include "ios.h"
#include "flagHandling.h"
#include "states.h"
flags flag={0};

//cau should be called at the end of funcs

void flagHandling(void){
	
// reset handling	

if(flag.ch.reset==1){flag.ch.reset=0;}
	
if(panelInput.ch.reset==1 && flag.ch.reset==0 && currentState==fault){flag.ch.reset=1;}



}
