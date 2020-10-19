################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/MCAL/SysTick.c \
../source/MCAL/gpio.c 

OBJS += \
./source/MCAL/SysTick.o \
./source/MCAL/gpio.o 

C_DEPS += \
./source/MCAL/SysTick.d \
./source/MCAL/gpio.d 


# Each subdirectory must supply rules for building sources it contributes
source/MCAL/%.o: ../source/MCAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DCPU_MK64FN1M0VLL12_cm4 -DCPU_MK64FN1M0VLL12 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I../source/startup -I../source/FSM/States -I../source/FSM -I../source/MCAL -I../source/drivers -I../source/board -I../source -I../ -I../CMSIS -I../source/database -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


