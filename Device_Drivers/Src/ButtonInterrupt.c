/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "stm32f303RE.h"


// STM32F303RE is having internal LED connected on PA5, Button is connected on PC13

void delay(void)
{
	for(uint32_t i = 0; i<300000; i++);
}

int main(void)
{
	// Feed the data
	GPIO_Handle_t GPIOA_Handle;
	GPIO_Handle_t GPIOC_Handle;

	GPIOA_Handle.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GPIOA_Handle.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOA_Handle.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIOA_Handle.GPIO_PinConfig.GPIO_PinSpeed = GPOI_SPEED_HIGH;
	GPIOA_Handle.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;

	GPIOC_Handle.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIOC_Handle.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;

	GPIOA_Handle.pGPIOx = GPIOA;
	GPIOC_Handle.pGPIOx = GPIOC;

	// Enable the clock
	GPIO_PeriClockControl(GPIOA, ENABLE);
	GPIO_PeriClockControl(GPIOC, ENABLE);

	// Init call
	GPIO_Init(&GPIOA_Handle);
	GPIO_Init(&GPIOC_Handle);


	//IRQ configuration
	GPIO_IRQInterruptConfig(IRQ_NO_EXTI15_10, ENABLE);
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI15_10, 15);


	 //main operation
	while(1);


}


void EXTI15_10_IRQHandler(void)
{

	GPIO_IRQ_Handle(GPIO_PIN_NO_13);
	GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
}
