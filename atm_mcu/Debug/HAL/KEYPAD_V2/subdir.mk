################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/KEYPAD_V2/keypad_cfg_v2.c \
../HAL/KEYPAD_V2/keypad_src_v2.c 

OBJS += \
./HAL/KEYPAD_V2/keypad_cfg_v2.o \
./HAL/KEYPAD_V2/keypad_src_v2.o 

C_DEPS += \
./HAL/KEYPAD_V2/keypad_cfg_v2.d \
./HAL/KEYPAD_V2/keypad_src_v2.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/KEYPAD_V2/%.o: ../HAL/KEYPAD_V2/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


