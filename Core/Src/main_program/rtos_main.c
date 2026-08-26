/*
 * rtos_main.c
 *
 *  Created on: Jul 15, 2026
 *      Author: hsuanjung
 */



#include "stm32h7xx_hal.h"
#include "uros_init.h"
#include "servo_monitor.hpp"
#include "arm_test.hpp"
#include "servo_motor_config.h"
#include "ms_2_monitor.h"
#include "cmsis_os2.h"
#include <stdbool.h>

int task_remain = 0, task02 = 0;
volatile int test_mission = 0, angle = 47;
volatile bool limsw = false;
volatile bool Prepared = false;

volatile test_angle_1 = 90, test_angle_2 = 90;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

void StartDefaultTask(void *argument)
{
//	while (!Prepared)
//	{
//		osDelay(1);
//	}
	HAL_TIM_Base_Start_IT(&htim2);
	servo_init();
	cpp_arm_init();
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

		// HAL_TIM_PWM_Start( &htim3, TIM_CHANNEL_1);
		// HAL_TIM_PWM_Start( &htim3, TIM_CHANNEL_2);
		// __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, (uint32_t)( 500 + 6.67 * test_angle_1 ));
		// __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, (uint32_t)( 500 + 6.67 * test_angle_2 ));

		switch (test_mission)
		{
		case 1:// Test Light
			test_mission = 0;	
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
			osDelay(1000);
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
			break;
		case 2:
			test_mission = 0;
			MS_2_init();
			break;
		case 3:
			test_mission = 0;
			MS_2_CW_down();
			break;
		case 4:
			test_mission = 0;
			MS_2_CCW_down();
			break;
		case 5:
			test_mission = 0;
			MS_2_CW_rotate();
			break;
		case 6:
			test_mission = 0;
			MS_2_CCW_rotate();
			break;
		case 7:
			test_mission = 0;
			MS_2_close_blue();
			break;
		case 8:
			test_mission = 0;
			MS_2_close_pink();
			break;
		case 9:
			test_mission = 0;
			MS_2_open_blue();
			break;
		case 10:
			test_mission = 0;
			MS_2_open_pink();
			break;
		case 11:
			test_mission = 0;
			pusher_extend();
			break;
		case 12:
			test_mission = 0;
			pusher_retract();
			break;
		case 13:
			test_mission = 0;
			cpp_arm_test();
			break;
		case 14:
			test_mission = 0;
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, (uint32_t)(500 + 6.67 * 215));
			break;
		case 15:
			test_mission = 0;
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, (uint32_t)(500 + 6.67 * 135));
			break;
		default:
			break;
		}
		// /mechanism/command 觸發的機構動作
		// if (mechanism_command_pending)
		// {
		// 	mechanism_command_pending = false;
		// 	switch (mechanism_command_id)
		// 	{
		// 	case 201:
		// 		osDelay(1);
		// 		pusher_extend();
		// 		break;

		// 	case 202:
		// 		osDelay(1);
		// 		pusher_retract();
		// 		break;

		// 	case 203:
		// 		screen();
		// 		break;

		// 	default:
		// 		break;
		// 	}
		// 	task_remain = uxTaskGetStackHighWaterMark(NULL);
		// 	osDelay(1);
		// }
	osDelay(1);
	}
}

void StartTask03(void *argument){
	for(;;){
		cpp_arm_update();
		osDelay(10);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (HAL_GPIO_ReadPin(GPIOB, GPIO_Pin) == GPIO_PIN_SET)
	{
		limsw = true;
	}

	if (HAL_GPIO_ReadPin(GPIOG, GPIO_Pin) == GPIO_PIN_SET)
	{
	}
}
