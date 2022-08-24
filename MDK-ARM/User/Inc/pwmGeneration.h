#ifndef __modulator_H
#define __modulator_H

#include <stdint.h>

#define wscale 16799 //cau check for it at home

void modulatorDisable(void);
void modulatorEnable(void);
void modulator(void);

extern uint16_t sw_count_a;
extern uint16_t sw_count_b;
extern uint16_t sw_count_c;

#endif

