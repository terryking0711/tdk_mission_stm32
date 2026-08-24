/*
 * rtos_main.c
 *
 *  Created on: Jul 15, 2026
 *      Author: hsuanjung
 */



#include "stm32h7xx_hal.h"
#include "uros_init.h"
#include "servo_monitor.hpp"
#include "servo_motor_config.h"
#include "ms_2_monitor.h"
#include "cmsis_os2.h"
#include <stdbool.h>

int task_remain = 0, task02 = 0;
volatile int angle = 47;
volatile bool limsw = false;
// osSemaphoreId_t limsw_sem;
volatile bool Prepared = false;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;

void StartDefaultTask(void *argument)
{
//	while (!Prepared)
//	{
//		osDelay(1);
//	}
	HAL_TIM_Base_Start_IT(&htim2);
	servo_init();
	uros_init();
	for (;;)
	{
		uros_agent_status_check();
		osDelay(100 / FREQUENCY);
	}
}

void StartTask02(void *argument)
{
	for (;;)
	{
		task02++;

		// /mechanism/command 觸發的機構動作 (command_id 由 mechanism_command_cb 更新)
		switch (mechanism_command_id)
		{
		case 1:// Test Light
			mechanism_command_id = 0;
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
			osDelay(1000);
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
			break;
		case 2:
			mechanism_command_id = 0;
			MS_2_init();
			break;
		case 3:
			mechanism_command_id = 0;
			MS_2_CW_down();
			break;
		case 4:
			mechanism_command_id = 0;
			MS_2_CCW_down();
			break;
		case 5:
			mechanism_command_id = 0;
			MS_2_CW_rotate();
			break;
		case 6:
			mechanism_command_id = 0;
			MS_2_CCW_rotate();
			break;
		case 7:
			mechanism_command_id = 0;
			MS_2_close_blue();
			break;
		case 8:
			mechanism_command_id = 0;
			MS_2_close_pink();
			break;
		case 9:
			mechanism_command_id = 0;
			MS_2_open_blue();
			break;
		case 10:
			mechanism_command_id = 0;
			MS_2_open_pink();
			break;
		case 11:
			mechanism_command_id = 0;
			pusher_extend();
			break;
		case 12:
			mechanism_command_id = 0;
			pusher_retract();
			break;
		default:
			break;
		}

		task_remain = uxTaskGetStackHighWaterMark(NULL);
		osDelay(1);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (HAL_GPIO_ReadPin(GPIOB, GPIO_Pin) == GPIO_PIN_SET)
	{
		limsw = true;
	}
}
