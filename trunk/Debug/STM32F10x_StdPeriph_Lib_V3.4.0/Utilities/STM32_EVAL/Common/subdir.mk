################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/Common/fonts.c \
../STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/Common/stm32_eval_i2c_ee.c \
../STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/Common/stm32_eval_i2c_tsensor.c \
../STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/Common/stm32_eval_sdio_sd.c \
../STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/Common/stm32_eval_spi_flash.c \
../STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/Common/stm32_eval_spi_sd.c 

OBJS += \
./STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/Common/fonts.o \
./STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/Common/stm32_eval_i2c_ee.o \
./STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/Common/stm32_eval_i2c_tsensor.o \
./STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/Common/stm32_eval_sdio_sd.o \
./STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/Common/stm32_eval_spi_flash.o \
./STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/Common/stm32_eval_spi_sd.o 

C_DEPS += \
./STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/Common/fonts.d \
./STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/Common/stm32_eval_i2c_ee.d \
./STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/Common/stm32_eval_i2c_tsensor.d \
./STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/Common/stm32_eval_sdio_sd.d \
./STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/Common/stm32_eval_spi_flash.d \
./STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/Common/stm32_eval_spi_sd.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/Common/%.o: ../STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/Common/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I"C:\ARM_workspace\ONYKS\STM32F10x_StdPeriph_Lib_V3.4.0\Libraries\STM32F10x_StdPeriph_Driver\inc" -I"C:\ARM_workspace\ONYKS\STM32F10x_StdPeriph_Lib_V3.4.0\Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x" -I"C:\ARM_workspace\ONYKS\STM32F10x_StdPeriph_Lib_V3.4.0\Libraries\CMSIS\CM3\CoreSupport" -Os -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


