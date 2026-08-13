/*
 * ms_2.cpp
 *
 *  Created on: Jul 29, 2026
 *      Author: hsuanjung
 */

#include "ms_2.hpp"
#include "dc_driver_oop.hpp"
#include "servo_oop.hpp"
#include "dc_control.h"
#include "cmsis_os2.h"

extern dc_driver screen;
extern servo servo_2_3;
extern volatile bool limsw;

void screen_rotate(){

    dc_motor_screen_init();

//----------------------------------------------------------Left to Right Pos

    osDelay(10000);
    servo_2_3.set_angle(1);
    osDelay(400);
    screen.cw();
    limsw = false;

    uint32_t timeout_counter = 0;
    const uint32_t MAX_TIMEOUT_MS = 10000;

    timeout_counter = 0;
    while(!limsw){
        osDelay(1);
        timeout_counter++;

        if( timeout_counter >= MAX_TIMEOUT_MS ){
            screen.stop();
            return;
        }
    }

    screen.stop();
    osDelay(300);
    screen.ccw();
    osDelay(300);
    screen.stop();

//------------------------------------------------------------Right to Left Pos

    osDelay(3000);
    screen.ccw();
    limsw = false;

    timeout_counter = 0;
    while(!limsw){
        osDelay(1);
        timeout_counter++;

        if( timeout_counter >= MAX_TIMEOUT_MS ){
            screen.stop();
            return;
        }
    }
    screen.stop();
    osDelay(300);
    screen.cw();
    osDelay(300);
    screen.stop();
    osDelay(1000);
    servo_2_3.set_angle(0);
}
