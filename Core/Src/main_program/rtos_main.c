/*
 * rtos_main.c
 *
 *  Created on: Jul 15, 2026
 *      Author: hsuanjung
 */



#include "stm32h7xx_hal.h"
#include "uros_init.h"
#include "servo_monitor.hpp"
#include "dc_control.h"
#include "servo_motor_config.h"
#include "cmsis_os2.h"
#include <stdbool.h>

int task_remain = 0, task02;
volatile int mission = 0, angle = 47;
bool limsw = false;

extern TIM_HandleTypeDef htim2;
// extern TIM_HandleTypeDef htim3;


void StartDefaultTask(void *argument)
{
	HAL_TIM_Base_Start_IT(&htim2);
	servo_init();
	uros_init();
	dc_motor(0);
	for (;;)
	{
		uros_agent_status_check();
		osDelay(100/FREQUENCY);
	}
}

void StartTask02(void *argument)
{
	for (;;)
	{
		// __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 500 + angle * per_1);
		// __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 500 + angle * per_2);
		task02++;

		// 限位開關硬體事件 (由 HAL_GPIO_EXTI_Callback 觸發，跟 ROS 命令無關)
		switch (mission)
		{
		case 1:
			mission = 0;
			limsw = false;
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
			osDelay(1000);
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
			break;

		default:
			break;
		}

		// /mechanism/command 觸發的機構動作
		if (mechanism_command_pending)
		{
			mechanism_command_pending = false;

			switch (mechanism_command_id)
			{
			case 201:
				osDelay(1);
				pusher_extend();
				break;

			case 202:
				osDelay(1);
				pusher_retract();
				break;

			case 3:
				limsw = false;
				dc_motor(1);
				while (!limsw)
				{
					osDelay(1);
				}
				dc_motor(0);
				osDelay(500);
				dc_motor(-1);
				osDelay(200);
				limsw = false;
				while (!limsw)
				{
					osDelay(1);
				}
				dc_motor(0);
				osDelay(300);
				dc_motor(1);
				osDelay(100);
				dc_motor(0);
				break;

			default:
				break;
			}
		}

		task_remain = uxTaskGetStackHighWaterMark(NULL);
		osDelay(1);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (HAL_GPIO_ReadPin(GPIOB, GPIO_Pin) == GPIO_PIN_SET)
	{
		mission = 1;
		limsw = true;
	}
}
