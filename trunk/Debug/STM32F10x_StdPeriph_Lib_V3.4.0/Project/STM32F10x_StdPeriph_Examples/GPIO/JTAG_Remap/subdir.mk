################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32F10x_StdPeriph_Lib_V3.4.0/Project/STM32F10x_StdPeriph_Examples/GPIO/JTAG_Remap/main.c \
../STM32F10x_StdPeriph_Lib_V3.4.0/Project/STM32F10x_StdPeriph_Examples/GPIO/JTAG_Remap/stm32f10x_it.c \
../STM32F10x_StdPeriph_Lib_V3.4.0/Project/STM32F10x_StdPeriph_Examples/GPIO/JTAG_Remap/system_stm32f10x.c 

OBJS += \
./STM32F10x_StdPeriph_Lib_V3.4.0/Project/STM32F10x_StdPeriph_Examples/GPIO/JTAG_Remap/main.o \
./STM32F10x_StdPeriph_Lib_V3.4.0/Project/STM32F10x_StdPeriph_Examples/GPIO/JTAG_Remap/stm32f10x_it.o \
./STM32F10x_StdPeriph_Lib_V3.4.0/Project/STM32F10x_StdPeriph_Examples/GPIO/JTAG_Remap/system_stm32f10x.o 

C_DEPS += \
./STM32F10x_StdPeriph_Lib_V3.4.0/Project/STM32F10x_StdPeriph_Examples/GPIO/JTAG_Remap/main.d \
./STM32F10x_StdPeriph_Lib_V3.4.0/Project/STM32F10x_StdPeriph_Examples/GPIO/JTAG_Remap/stm32f10x_it.d \
./STM32F10x_StdPeriph_Lib_V3.4.0/Project/STM32F10x_StdPeriph_Examples/GPIO/JTAG_Remap/system_stm32f10x.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F10x_StdPeriph_Lib_V3.4.0/Project/STM32F10x_StdPeriph_Examples/GPIO/JTAG_Remap/%.o: ../STM32F10x_StdPeriph_Lib_V3.4.0/Project/STM32F10x_StdPeriph_Examples/GPIO/JTAG_Remap/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I"C:\ARM_workspace\ONYKS\STM32F10x_StdPeriph_Lib_V3.4.0\Libraries\STM32F10x_StdPeriph_Driver\inc" -I"C:\ARM_workspace\ONYKS\STM32F10x_StdPeriph_Lib_V3.4.0\Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x" -I"C:\ARM_workspace\ONYKS\STM32F10x_StdPeriph_Lib_V3.4.0\Libraries\CMSIS\CM3\CoreSupport" -Os -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


