/*
 * main_SPI.c
 *
 *  Created on: Apr 21, 2024
 *      Author: Ram
 *
 * PB14 --> SPI2_MISO
 * PB15 --> SPI2_MOSI
 * PB13 -> SPI2_SCLK
 * PB12 --> SPI2_NSS
 * ALT function mode : 5
 * PC13 --> Button
 *
 */


#include <stdint.h>
#include "stm32f303RE.h"


void delay(void){
	for(uint32_t i; i < 30000; i++);
}


void GPIO_button_init()
{
	GPIO_Handle_t GPIOC_Handle;

	GPIOC_Handle.pGPIOx = GPIOC;
	GPIOC_Handle.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIOC_Handle.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIOC_Handle.GPIO_PinConfig.GPIO_PinSpeed = GPOI_SPEED_HIGH;
	GPIOC_Handle.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOC_Handle.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;

	// Init call
	GPIO_Init(&GPIOC_Handle);
}

void SPI_GPIO_init()
{
	GPIO_Handle_t GPIOB_Handle;

	GPIOB_Handle.pGPIOx = GPIOB;

	GPIOB_Handle.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	GPIOB_Handle.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	GPIOB_Handle.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIOB_Handle.GPIO_PinConfig.GPIO_PinSpeed = GPOI_SPEED_HIGH;
	GPIOB_Handle.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;

	//NSS init
	GPIOB_Handle.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GPIO_Init(&GPIOB_Handle);

	//SCK init
	GPIOB_Handle.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&GPIOB_Handle);

//	//MISO init
//	GPIOB_Handle.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
//	GPIO_Init(&GPIOB_Handle);

	//MOSI init
	GPIOB_Handle.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&GPIOB_Handle);
}


void SPI_init()
{
	SPI_Handle_t SPI2_Handle;

	SPI2_Handle.pSPIx = SPI2;

	SPI2_Handle.SPI_Config.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2_Handle.SPI_Config.SPI_BusConfig = SPI_BUS_FD;
	SPI2_Handle.SPI_Config.SPI_Speed = SPI_SCLK_SPEED_DIV64;
	SPI2_Handle.SPI_Config.SPI_CPOL = SPI_CPOL_LOW;
	SPI2_Handle.SPI_Config.SPI_CPHA = SPI_CPHA_LOW;
	SPI2_Handle.SPI_Config.SPI_SSM = SPI_SSM_DI;  // Enabling hardware SS by disabling Software SS


	SPI_Init(&SPI2_Handle);
}


int main()
{
	char Data[] = "Hello Slave!\n";
	//Initialize GPIO button
	GPIO_button_init();

	//Init of SPI gpio in Alternte fun mode
	SPI_GPIO_init();

	//SPI initialization with handle
	SPI_init();

	//Enable SSOE
	SPI_SSOEConfig(SPI2, ENABLE);


	while(1)
	{
		//wait until button pressed
		while(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13));

		//debounce time delay
		delay();

		//Enable SPI2 pheripheral
		SPI_PeripheralControl(SPI2, ENABLE);

		//Transmitting data over MOSI line
		SPI_TransmitData(SPI2, (uint8_t*)Data, sizeof(Data));

		//Hang Until SPI gets free after sending data
		while(SPI_GetFlagStatus(SPI2 , SPI_BUSY_FLAG));


		//Disable SPI2 pheripheral
		SPI_PeripheralControl(SPI2, DISABLE);
	}
	return 0;
}
