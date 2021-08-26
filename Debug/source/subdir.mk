################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Final.c \
../source/freertos_spi.c \
../source/fsl_dspi.c \
../source/nokiaLCD.c \
../source/semihost_hardfault.c 

OBJS += \
./source/Final.o \
./source/freertos_spi.o \
./source/fsl_dspi.o \
./source/nokiaLCD.o \
./source/semihost_hardfault.o 

C_DEPS += \
./source/Final.d \
./source/freertos_spi.d \
./source/fsl_dspi.d \
./source/nokiaLCD.d \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSDK_OS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\elite\Documents\MCUXpressoIDE_11.3.1_5262\workspace\Final\board" -I"C:\Users\elite\Documents\MCUXpressoIDE_11.3.1_5262\workspace\Final\source" -I"C:\Users\elite\Documents\MCUXpressoIDE_11.3.1_5262\workspace\Final\freertos\freertos_kernel\include" -I"C:\Users\elite\Documents\MCUXpressoIDE_11.3.1_5262\workspace\Final\freertos\template\ARM_CM4F" -I"C:\Users\elite\Documents\MCUXpressoIDE_11.3.1_5262\workspace\Final\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"C:\Users\elite\Documents\MCUXpressoIDE_11.3.1_5262\workspace\Final\drivers" -I"C:\Users\elite\Documents\MCUXpressoIDE_11.3.1_5262\workspace\Final\utilities" -I"C:\Users\elite\Documents\MCUXpressoIDE_11.3.1_5262\workspace\Final\component\serial_manager" -I"C:\Users\elite\Documents\MCUXpressoIDE_11.3.1_5262\workspace\Final\component\uart" -I"C:\Users\elite\Documents\MCUXpressoIDE_11.3.1_5262\workspace\Final\component\lists" -I"C:\Users\elite\Documents\MCUXpressoIDE_11.3.1_5262\workspace\Final\CMSIS" -I"C:\Users\elite\Documents\MCUXpressoIDE_11.3.1_5262\workspace\Final\device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

