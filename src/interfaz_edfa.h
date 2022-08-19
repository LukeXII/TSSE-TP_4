#ifndef INTERFAZ_EDFA_H
#define INTERFAZ_EDFA_H

#include <stdint.h>

#define OUTPUT_POW_MAX_VALUE	40.0
#define INPUT_POW_MAX_VALUE	    10.0
#define INPUT_POW_MIN_VALUE	    -50.0
#define SAMPLES_NUMBER		    20

void setMaxOutputPower(float maxPower);
int8_t setInputPowerRange(float minPower, float maxPower);
uint8_t isAnyAlarmOn(void);
void disableEDFAOutput(void);
void disableEDFA(void);
uint8_t enableEDFA(void);
void resetEDFA(void);
float getMaxOutputPower(void);
float getMaxInputPower(void);
float getMinInputPower(void);
float getInputPower(void);
float getOutputPower(void);

#endif