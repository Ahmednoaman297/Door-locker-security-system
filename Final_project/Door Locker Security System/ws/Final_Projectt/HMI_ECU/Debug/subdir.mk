################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HMI_ECU.c \
../LCD.c \
../TIMER1.c \
../UART.c \
../displayer.c \
../gpio.c \
../keypad_flasha.c 

OBJS += \
./HMI_ECU.o \
./LCD.o \
./TIMER1.o \
./UART.o \
./displayer.o \
./gpio.o \
./keypad_flasha.o 

C_DEPS += \
./HMI_ECU.d \
./LCD.d \
./TIMER1.d \
./UART.d \
./displayer.d \
./gpio.d \
./keypad_flasha.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


