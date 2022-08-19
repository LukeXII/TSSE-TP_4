#include "stm32f4xx_hal_adc.h"

HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef* hadc)
{
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ADC_PollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout)
{
    return HAL_OK;
}

uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef* hadc)
{
    time_t t;

    srand((unsigned) time(&t));

    return (rand() % 4095);
}
