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
volatile int angle = 47;
volatile bool limsw = false;
// osSemaphoreId_t limsw_sem;
volatile bool Prepared = false;

volatile test_angle_1 = 90, test_angle_2 = 90;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

void StartDefaultTask(void *argument)
{
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
		// /mechanism/command 觸發的機構動作 (command_id 由 mechanism_command_cb 更新)
		switch (mechanism_command_id)
		{
		case 2000:	// initialize and set motor mid
			mechanism_command_id = 0;
			MS_2_init();
			break;
		case 2001:	// 順時針 down
			mechanism_command_id = 0;
			MS_2_CW_down();
			break;
		case 204:	// 順時針 rotate
			mechanism_command_id = 0;
			MS_2_CW_rotate();
			break;
		 case 205:	// 翻回去
		 	mechanism_command_id = 0;
		 	MS_2_CCW_rotate();
		 	break;
		case 203:	// servo 咬住 box
			mechanism_command_id = 0;
			MS_2_close_blue();
			break;
		case 206: // servo 放開 box
			mechanism_command_id = 0;
			MS_2_open_blue();
			break;

		case 207: //
			mechanism_command_id = 0;
			MS_2_middle();
			break;
		case 201: // pusher extend
			mechanism_command_id = 0;
			pusher_extend();
			break;
		case 202:
			mechanism_command_id = 0;
			pusher_retract();
			break;

//		 case 10: // servo 放開 box 鏡像
//				mechanism_command_id = 0;
//				MS_2_open_pink();
//				break;
//		 case 4:
//			mechanism_command_id = 0;
//			MS_2_CCW_down();
//			break;
//		 case 6:
//				 	mechanism_command_id = 0;
//				 	MS_2_CCW_rotate();
//				 	break;
//		 case 8:	// servo 咬住 box 鏡像
//		 	mechanism_command_id = 0;
//		 	MS_2_close_pink();
//		 	break;


		// case YOUR_COMMAND_ID: // Mission 2 逆時針降下
		// 	mechanism_command_id = 0;
		// 	MS_2_CCW_down();
		// 	break;


		// case YOUR_COMMAND_ID: // 執行手臂動作腳本
		// 	mechanism_command_id = 0;
		// 	cpp_arm_test();
		// 	break;

		default:
			break;
		}

		task_remain = uxTaskGetStackHighWaterMark(NULL);
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
