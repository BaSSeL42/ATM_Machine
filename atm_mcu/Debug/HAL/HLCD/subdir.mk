################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/HLCD/HLCD_Configure.c \
../HAL/HLCD/HLCD_Source.c 

OBJS += \
./HAL/HLCD/HLCD_Configure.o \
./HAL/HLCD/HLCD_Source.o 

C_DEPS += \
./HAL/HLCD/HLCD_Configure.d \
./HAL/HLCD/HLCD_Source.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/HLCD/%.o: ../HAL/HLCD/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


