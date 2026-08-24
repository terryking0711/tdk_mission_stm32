################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Inc/uros/uros_init.cpp 

OBJS += \
./Core/Inc/uros/uros_init.o 

CPP_DEPS += \
./Core/Inc/uros/uros_init.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/uros/%.o Core/Inc/uros/%.su Core/Inc/uros/%.cyclo: ../Core/Inc/uros/%.cpp Core/Inc/uros/subdir.mk

clean: clean-Core-2f-Inc-2f-uros

clean-Core-2f-Inc-2f-uros:
	-$(RM) ./Core/Inc/uros/uros_init.cyclo ./Core/Inc/uros/uros_init.d ./Core/Inc/uros/uros_init.o ./Core/Inc/uros/uros_init.su

.PHONY: clean-Core-2f-Inc-2f-uros

