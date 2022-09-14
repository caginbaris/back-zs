#ifndef __functionPrototypes_H
#define __functionPrototypes_H

void busChecks(void);
//adc
void init_ADC(void);
//protection
void initProtections(void);
void initControlRoutines(void);


void initReferences(void);

void LEDs(void);
void initialization(void);

void mainLoopCommPart(void);
void sysTickCommPart(void);
void initComm(void);

#endif
