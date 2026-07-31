/*
 * servo_monitor.cpp
 *
 *  Created on: Jul 24, 2026
 *      Author: hsuanjung
 */


#include "servo_oop.hpp"
#include "servo_monitor.hpp"
#include "servo_motor_config.h"
#include "dc_motor_config.h"
#include "dc_driver_oop.hpp"
#include "ms_2.hpp"
#include "cmsis_os2.h"

extern TIM_HandleTypeDef htim3;
extern volatile bool limsw;
extern dc_driver screen;

volatile uint8_t mission_delay_time = 100;
volatile int target_speed = 400;

//                pwm      channel     prepare_angle   initial_angle   target_angle   period   per   min_pwm   max_pwm
servo servo_2_1(&htim3, TIM_CHANNEL_1,      0 ,              0,            185,        500,    7.3 ,   500,     2500);
servo servo_2_2(&htim3, TIM_CHANNEL_2,     42,              42,            126,        500,    6.65,   500,     2500);
servo servo_2_3(&htim3, TIM_CHANNEL_3,     47,              47,            128,        100,    7.3 ,   500,     2500);

void servo_init(){
    servo_2_1.initial_servo();
    servo_2_2.initial_servo();
    servo_2_3.initial_servo();
}

void pusher(){
    screen.cw();
    limsw = false;

    uint32_t timeout_counter = 0;
    const uint32_t MAX_TIMEOUT_MS = 10000;
    while(!limsw){
        osDelay(1);
        timeout_counter++;

        if( timeout_counter >= MAX_TIMEOUT_MS ){ //Timeout Protection
            screen.stop();
            return;
        }
    }

    screen.stop();
    osDelay(100);
    screen.ccw();
    osDelay(300);
    screen.stop();

    osDelay(300);

    servo_2_2.set_angle(1);
    osDelay(500);
    servo_2_1.set_angle(1);
    osDelay(2000);
    servo_2_1.set_angle(0);
    osDelay(500);
    servo_2_2.set_angle(0);
}