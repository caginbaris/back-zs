#ifndef __modulator_H
#define __modulator_H

#include <stdint.h>

#define wscale 8399

void modulatorDisable(void);
void modulatorEnable(void);
void modulator(void);

extern uint16_t sw_count_a;
extern uint16_t sw_count_b;
extern uint16_t sw_count_c;

#endif

