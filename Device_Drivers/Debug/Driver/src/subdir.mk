################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/src/stm32f303RE_SPI_driver.c \
../Driver/src/stm32f303RE_gpio_driver.c 

OBJS += \
./Driver/src/stm32f303RE_SPI_driver.o \
./Driver/src/stm32f303RE_gpio_driver.o 

C_DEPS += \
./Driver/src/stm32f303RE_SPI_driver.d \
./Driver/src/stm32f303RE_gpio_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/src/%.o Driver/src/%.su Driver/src/%.cyclo: ../Driver/src/%.c Driver/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F3 -DSTM32F303RETx -DNUCLEO_F303RE -c -I"E:/Learn/Embedde-C/My_workspace/Target/Device_Drivers/Driver/inc" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Driver-2f-src

clean-Driver-2f-src:
	-$(RM) ./Driver/src/stm32f303RE_SPI_driver.cyclo ./Driver/src/stm32f303RE_SPI_driver.d ./Driver/src/stm32f303RE_SPI_driver.o ./Driver/src/stm32f303RE_SPI_driver.su ./Driver/src/stm32f303RE_gpio_driver.cyclo ./Driver/src/stm32f303RE_gpio_driver.d ./Driver/src/stm32f303RE_gpio_driver.o ./Driver/src/stm32f303RE_gpio_driver.su

.PHONY: clean-Driver-2f-src

