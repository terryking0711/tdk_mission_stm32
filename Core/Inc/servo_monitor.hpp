/*
 * motor_monitor.hpp
 *
 *  Created on: Jul 24, 2026
 *      Author: hsuanjung
 */

#ifndef INC_SERVO_MONITOR_HPP_
#define INC_SERVO_MONITOR_HPP_

#ifdef __cplusplus
extern "C"{
#endif

#include "dc_control.h"

void servo_init();
void pusher_extend();
void pusher_retract();
// void screen();

#ifdef __cplusplus
}
#endif



#endif /* INC_SERVO_MONITOR_HPP_ */
