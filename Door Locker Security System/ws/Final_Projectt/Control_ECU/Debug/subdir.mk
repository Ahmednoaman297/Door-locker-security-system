################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Buzzer.c \
../Control_ECU.c \
../DC_motor.c \
../EEPROM.c \
../I2C.c \
../TIMER0.c \
../TIMER1.c \
../UART.c \
../gpio.c 

OBJS += \
./Buzzer.o \
./Control_ECU.o \
./DC_motor.o \
./EEPROM.o \
./I2C.o \
./TIMER0.o \
./TIMER1.o \
./UART.o \
./gpio.o 

C_DEPS += \
./Buzzer.d \
./Control_ECU.d \
./DC_motor.d \
./EEPROM.d \
./I2C.d \
./TIMER0.d \
./TIMER1.d \
./UART.d \
./gpio.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


