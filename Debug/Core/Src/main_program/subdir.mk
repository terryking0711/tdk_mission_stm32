################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/main_program/arm_test.cpp \
../Core/Src/main_program/dc_driver_oop.cpp \
../Core/Src/main_program/encoder_dc.cpp \
../Core/Src/main_program/pid.cpp \
../Core/Src/main_program/servo.cpp \
../Core/Src/main_program/servo_monitor.cpp \
../Core/Src/main_program/servo_oop.cpp 

C_SRCS += \
../Core/Src/main_program/rtos_main.c 

C_DEPS += \
./Core/Src/main_program/rtos_main.d 

OBJS += \
./Core/Src/main_program/arm_test.o \
./Core/Src/main_program/dc_driver_oop.o \
./Core/Src/main_program/encoder_dc.o \
./Core/Src/main_program/pid.o \
./Core/Src/main_program/rtos_main.o \
./Core/Src/main_program/servo.o \
./Core/Src/main_program/servo_monitor.o \
./Core/Src/main_program/servo_oop.o 

CPP_DEPS += \
./Core/Src/main_program/arm_test.d \
./Core/Src/main_program/dc_driver_oop.d \
./Core/Src/main_program/encoder_dc.d \
./Core/Src/main_program/pid.d \
./Core/Src/main_program/servo.d \
./Core/Src/main_program/servo_monitor.d \
./Core/Src/main_program/servo_oop.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/main_program/%.o Core/Src/main_program/%.su Core/Src/main_program/%.cyclo: ../Core/Src/main_program/%.cpp Core/Src/main_program/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I"/home/hsuanjung/STM32CubeIDE/tdk_mission/tdk_mission_stm32/Core/Src/main_program/mission_2" -I"/home/hsuanjung/STM32CubeIDE/tdk_mission/tdk_mission_stm32/Core/Src/main_program" -I"/home/hsuanjung/STM32CubeIDE/tdk_mission/tdk_mission_stm32/Core/Inc/uros" -I"/home/hsuanjung/STM32CubeIDE/tdk_mission/tdk_mission_stm32/micro_ros_stm32cubemx_utils/microros_static_library_ide/libmicroros/include" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/main_program/%.o Core/Src/main_program/%.su Core/Src/main_program/%.cyclo: ../Core/Src/main_program/%.c Core/Src/main_program/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I"/home/hsuanjung/STM32CubeIDE/tdk_mission/tdk_mission_stm32/Core/Src/main_program/mission_2" -I"/home/hsuanjung/STM32CubeIDE/tdk_mission/tdk_mission_stm32/Core/Inc/uros" -I"/home/hsuanjung/STM32CubeIDE/tdk_mission/tdk_mission_stm32/micro_ros_stm32cubemx_utils/microros_static_library_ide/libmicroros/include" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-main_program

clean-Core-2f-Src-2f-main_program:
	-$(RM) ./Core/Src/main_program/arm_test.cyclo ./Core/Src/main_program/arm_test.d ./Core/Src/main_program/arm_test.o ./Core/Src/main_program/arm_test.su ./Core/Src/main_program/dc_driver_oop.cyclo ./Core/Src/main_program/dc_driver_oop.d ./Core/Src/main_program/dc_driver_oop.o ./Core/Src/main_program/dc_driver_oop.su ./Core/Src/main_program/encoder_dc.cyclo ./Core/Src/main_program/encoder_dc.d ./Core/Src/main_program/encoder_dc.o ./Core/Src/main_program/encoder_dc.su ./Core/Src/main_program/pid.cyclo ./Core/Src/main_program/pid.d ./Core/Src/main_program/pid.o ./Core/Src/main_program/pid.su ./Core/Src/main_program/rtos_main.cyclo ./Core/Src/main_program/rtos_main.d ./Core/Src/main_program/rtos_main.o ./Core/Src/main_program/rtos_main.su ./Core/Src/main_program/servo.cyclo ./Core/Src/main_program/servo.d ./Core/Src/main_program/servo.o ./Core/Src/main_program/servo.su ./Core/Src/main_program/servo_monitor.cyclo ./Core/Src/main_program/servo_monitor.d ./Core/Src/main_program/servo_monitor.o ./Core/Src/main_program/servo_monitor.su ./Core/Src/main_program/servo_oop.cyclo ./Core/Src/main_program/servo_oop.d ./Core/Src/main_program/servo_oop.o ./Core/Src/main_program/servo_oop.su

.PHONY: clean-Core-2f-Src-2f-main_program

