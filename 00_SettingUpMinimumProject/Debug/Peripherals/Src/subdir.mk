################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Peripherals/Src/RCC.c 

OBJS += \
./Peripherals/Src/RCC.o 

C_DEPS += \
./Peripherals/Src/RCC.d 


# Each subdirectory must supply rules for building sources it contributes
Peripherals/Src/%.o Peripherals/Src/%.su Peripherals/Src/%.cyclo: ../Peripherals/Src/%.c Peripherals/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -c -I"D:/Escritorio/Proyectos/STM32Projects/STM32F103MutexEmbeddedIO/STM32F103CXTX/00_SettingUpMinimumProject/Core/Inc" -I"D:/Escritorio/Proyectos/STM32Projects/STM32F103MutexEmbeddedIO/STM32F103CXTX/00_SettingUpMinimumProject/CMSIS/Include" -I"D:/Escritorio/Proyectos/STM32Projects/STM32F103MutexEmbeddedIO/STM32F103CXTX/00_SettingUpMinimumProject/Peripherals/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Peripherals-2f-Src

clean-Peripherals-2f-Src:
	-$(RM) ./Peripherals/Src/RCC.cyclo ./Peripherals/Src/RCC.d ./Peripherals/Src/RCC.o ./Peripherals/Src/RCC.su

.PHONY: clean-Peripherals-2f-Src

