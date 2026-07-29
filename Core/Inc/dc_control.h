/*
 * dc_control.h
 *
 *  Created on: Jul 20, 2026
 *      Author: hsuanjung
 */

#ifndef INC_DC_CONTROL_H_
#define INC_DC_CONTROL_H_


void dc_motor_screen_init();
void dc_motor_screen( int dir, float speed);

// pin define: dir->PA4, PWM->TIM4 CH1 PD12


#endif /* INC_DC_CONTROL_H_ */
