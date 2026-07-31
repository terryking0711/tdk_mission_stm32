/*
 * dc_driver_monitor.cpp
 *
 *  Created on: Jul 29, 2026
 *      Author: hsuanjung
 */

#include "dc_driver_oop.hpp"
#include "stm32h7xx.h"
#include "stm32h7xx_hal.h"
#include "cmsis_os2.h"

#include "dc_driver_monitor.hpp"

extern TIM_HandleTypeDef htim4;
extern volatile bool limsw;

dc_driver screen(&htim4, TIM_CHANNEL_1, GPIOA, GPIO_PIN_4, 10, 700);

void screen_dc_init(){
    screen.init_dc_driver();
}
