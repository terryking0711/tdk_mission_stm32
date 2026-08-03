/*
 * dc_control.c
 *
 *  Created on: Jul 20, 2026
 *      Author: hsuanjung
 */

#include "dc_control.h"
#include "stm32h7xx_hal.h"
#include "cmsis_os2.h"
#include <stdbool.h>
#include "dc_motor_config.h"

extern volatile bool limsw;
extern TIM_HandleTypeDef htim4;
volatile uint16_t init_delay_time = 500;
volatile int init_speed = 200;
bool motion = false;
// extern osSemaphoreId_t limsw_sem;

void dc_motor_screen_init()
{
    limsw = false;
    // dc_motor(-1);
    dc_motor_v02( -1, init_speed);

    uint32_t timeout_counter = 0;
    const uint32_t MAX_TIMEOUT_MS = 7000;

    while (!limsw)
    {
        osDelay(1);
        timeout_counter++;

        if (timeout_counter >= MAX_TIMEOUT_MS)
        {
            // dc_motor(0);
            dc_motor_v02(0 , 0);
            return;
        }
    }
    // dc_motor(0);
    dc_motor_v02(0, 0);
    osDelay(400);

    // dc_motor(1);
    dc_motor_v02( 1, init_speed);
    osDelay(init_delay_time);
    // dc_motor(0);
    dc_motor_v02(0, 0);

    limsw = false;
}

void dc_motor_screen(int dir, float speed)
{
    uint32_t current_pwm = __HAL_TIM_GET_COMPARE(&htim4, TIM_CHANNEL_1);
    uint32_t target_pwm = 0;

    switch (dir)
    {
    case 0: 
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
        motion = false;
        target_pwm = 0;
        break;
    case 1: 
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
        motion = true;
        target_pwm = (uint32_t)speed;
        break;
    case -1:
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
        motion = true;
        target_pwm = (uint32_t)speed;
        break;
    default:
        return;
    }

    int32_t pwm_diff = target_pwm - current_pwm;
    if (pwm_diff == 0) return;

    for(int i = 1; i <= dc_period; i++)
    {
        uint32_t step_pwm = current_pwm + (pwm_diff * i / dc_period);
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, step_pwm);
        osDelay(1);
    }
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, target_pwm);
}