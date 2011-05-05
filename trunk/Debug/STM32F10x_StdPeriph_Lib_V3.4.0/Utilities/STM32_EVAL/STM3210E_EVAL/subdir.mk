################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/STM3210E_EVAL/stm3210e_eval.c \
../STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/STM3210E_EVAL/stm3210e_eval_fsmc_nand.c \
../STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/STM3210E_EVAL/stm3210e_eval_fsmc_nor.c \
../STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/STM3210E_EVAL/stm3210e_eval_fsmc_sram.c \
../STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/STM3210E_EVAL/stm3210e_eval_lcd.c 

OBJS += \
./STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/STM3210E_EVAL/stm3210e_eval.o \
./STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/STM3210E_EVAL/stm3210e_eval_fsmc_nand.o \
./STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/STM3210E_EVAL/stm3210e_eval_fsmc_nor.o \
./STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/STM3210E_EVAL/stm3210e_eval_fsmc_sram.o \
./STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/STM3210E_EVAL/stm3210e_eval_lcd.o 

C_DEPS += \
./STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/STM3210E_EVAL/stm3210e_eval.d \
./STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/STM3210E_EVAL/stm3210e_eval_fsmc_nand.d \
./STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/STM3210E_EVAL/stm3210e_eval_fsmc_nor.d \
./STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/STM3210E_EVAL/stm3210e_eval_fsmc_sram.d \
./STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/STM3210E_EVAL/stm3210e_eval_lcd.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/STM3210E_EVAL/%.o: ../STM32F10x_StdPeriph_Lib_V3.4.0/Utilities/STM32_EVAL/STM3210E_EVAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I"C:\ARM_workspace\ONYKS\STM32F10x_StdPeriph_Lib_V3.4.0\Libraries\STM32F10x_StdPeriph_Driver\inc" -I"C:\ARM_workspace\ONYKS\STM32F10x_StdPeriph_Lib_V3.4.0\Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x" -I"C:\ARM_workspace\ONYKS\STM32F10x_StdPeriph_Lib_V3.4.0\Libraries\CMSIS\CM3\CoreSupport" -Os -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


