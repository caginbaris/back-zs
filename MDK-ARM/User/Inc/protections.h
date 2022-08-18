#ifndef __protections_H__
#define __protections_H__

#include "plib.h"


//current
extern overLimit_inputParameters overCurrentRMS_Config;
extern overLimit_outputParameters overCurrentRMS_L1,overCurrentRMS_L2,overCurrentRMS_L3;

extern overLimit_inputParameters overCurrentCS_Config;
extern overLimit_outputParameters overCurrentCS_L1,overCurrentCS_L2,overCurrentCS_L3;

extern overLimit_inputParameters overCurrentPeak_Config;
extern overLimit_outputParameters overCurrentPeak_L1,overCurrentPeak_L2,overCurrentPeak_L3;

//voltage

extern overLimit_inputParameters overVoltageDC_Config,overVoltageAC_Config;
extern overLimit_outputParameters overVoltageDC, overVoltageAC;

extern underLimit_inputParameters underVoltageDC_Config,underVoltageAC_Config;
extern underLimit_outputParameters underVoltageDC, underVoltageAC;




void overCurrent(void);
void voltageProtections(void);
void miscProtections(void);

void protection(void);

#endif
