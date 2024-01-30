################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/pwm/subdir.mk
-include MCAL/UART/subdir.mk
-include MCAL/Timer/subdir.mk
-include MCAL/SPI/subdir.mk
-include MCAL/IIC/subdir.mk
-include MCAL/ExtInt/subdir.mk
-include MCAL/DIO/subdir.mk
-include HAL/LED/subdir.mk
-include HAL/KEYPAD_V2/subdir.mk
-include HAL/HUART/subdir.mk
-include HAL/HTimer/subdir.mk
-include HAL/HSPI/subdir.mk
-include HAL/HLCD/subdir.mk
-include HAL/HExtInt/subdir.mk
-include HAL/EEPROM/subdir.mk
-include HAL/Button/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
ATM_MCU.lss \

FLASH_IMAGE += \
ATM_MCU.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: ATM_MCU.elf secondary-outputs

# Tool invocations
ATM_MCU.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,ATM_MCU.map -mmcu=atmega32 -o "ATM_MCU.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ATM_MCU.lss: ATM_MCU.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ATM_MCU.elf  >"ATM_MCU.lss"
	@echo 'Finished building: $@'
	@echo ' '

ATM_MCU.hex: ATM_MCU.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex ATM_MCU.elf  "ATM_MCU.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ATM_MCU.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 ATM_MCU.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) ATM_MCU.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
