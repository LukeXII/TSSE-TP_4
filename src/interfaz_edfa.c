#include "interfaz_edfa.h"
#include "stm32f4xx_hal_adc.h"
#include "stm32f4xx_hal_gpio.h"

ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;

static float maxOutputPower = 0;
static float minInputPower = 0;
static float maxInputPower = 0;

GPIO_TypeDef * GPIOF;

void setMaxOutputPower(float maxPower)
{
	if(maxPower > OUTPUT_POW_MAX_VALUE)
		maxOutputPower = OUTPUT_POW_MAX_VALUE;
	else
		maxOutputPower = maxPower;
}

float getMaxOutputPower(void)
{
	return maxOutputPower;
}

int8_t setInputPowerRange(float minPower, float maxPower)
{
	if(minPower < maxPower)
	{
		if(maxPower > INPUT_POW_MAX_VALUE)
			maxInputPower = INPUT_POW_MAX_VALUE;
		else
			maxInputPower = maxPower;
			
		if(minPower < INPUT_POW_MIN_VALUE)
			minInputPower = INPUT_POW_MIN_VALUE;
		else
			minInputPower = minPower;

		return 0;
	}
	else
		return -1;
}

float getMaxInputPower(void)
{
	return maxInputPower;
}

float getMinInputPower(void)
{
	return minInputPower;
}

float getInputPower(void)
{
	float accValue = 0;
	uint8_t i;
	
	for(i = 0;i < SAMPLES_NUMBER;i++)
	{
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 1);
		accValue += HAL_ADC_GetValue(&hadc1);;
	}
	
	accValue /= SAMPLES_NUMBER;

	accValue = accValue*(INPUT_POW_MAX_VALUE - INPUT_POW_MIN_VALUE)/4095 - 50;

	return accValue;
}

float getOutputPower(void)
{
	float accValue = 0;
	uint8_t i;
	
	for(i = 0;i < SAMPLES_NUMBER;i++)
	{
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 1);
		accValue += HAL_ADC_GetValue(&hadc1);;
	}
	
	accValue /= SAMPLES_NUMBER;

	accValue = accValue*(OUTPUT_POW_MAX_VALUE)/4095;

	return accValue;
}

uint8_t isAnyAlarmOn(void)
{
	if(HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_7) ||
		HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_8) ||
		HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_9) ||
		HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_10) == GPIO_PIN_SET)
		return 1;
	else
		return 0;
	
}

void disableEDFAOutput(void)
{
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, GPIO_PIN_SET);
}

void disableEDFA(void)
{
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_2, GPIO_PIN_SET);
}

uint8_t enableEDFA(void)
{
	float inputPower = getInputPower();

	if((inputPower >= minInputPower) &&
		(inputPower <= maxInputPower) &&
		!isAnyAlarmOn())
	{
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_2, GPIO_PIN_RESET);
		return 0;
	}
	else
		return -1;
	
}

void resetEDFA(void)
{
	disableEDFAOutput();
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3, GPIO_PIN_SET);
}

void clearControlSignals(void)
{
	disableEDFA();
	resetEDFA();
}
