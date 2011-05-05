################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := cs-rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/subdir.mk
-include fatfs/subdir.mk
-include STM32F10x_StdPeriph_Lib_V3.4.0/Libraries/STM32F10x_StdPeriph_Driver/src/subdir.mk
-include STM32F10x_StdPeriph_Lib_V3.4.0/Libraries/CMSIS/CM3/CoreSupport/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
ONYKS.hex \

SECONDARY_LIST += \
ONYKS.lst \

SECONDARY_SIZE += \
ONYKS.siz \


# All Target
all: ONYKS.elf secondary-outputs

# Tool invocations
ONYKS.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Sourcery Windows GCC C Linker'
	arm-none-eabi-gcc -T"C:\ARM_workspace\ONYKS\stm32f10x_flash_md.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,ONYKS.map -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o"ONYKS.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ONYKS.hex: ONYKS.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex ONYKS.elf "ONYKS.hex"
	@echo 'Finished building: $@'
	@echo ' '

ONYKS.lst: ONYKS.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Listing'
	arm-none-eabi-objdump -h -S ONYKS.elf >"ONYKS.lst"
	@echo 'Finished building: $@'
	@echo ' '

ONYKS.siz: ONYKS.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Print Size'
	arm-none-eabi-size  --format=berkeley ONYKS.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(EXECUTABLES)$(SECONDARY_LIST)$(S_UPPER_DEPS) ONYKS.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
