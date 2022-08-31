#ifndef __STM32F4xx_ADC_H
#define __STM32F4xx_ADC_H

#include <stdint.h>
#include <stdlib.h>
#include <time.h>

// Mock de la HAL del ADC

typedef enum 
{
  HAL_OK       = 0x00U,
  HAL_ERROR    = 0x01U,
  HAL_BUSY     = 0x02U,
  HAL_TIMEOUT  = 0x03U
} HAL_StatusTypeDef;

typedef uint8_t ADC_HandleTypeDef;

HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef HAL_ADC_PollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout);
uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef* hadc);

#endif
