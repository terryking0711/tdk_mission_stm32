/*
 * servo_oop.cpp
 *
 *  Created on: Jul 24, 2026
 *      Author: hsuanjung
 */

#include "servo_oop.hpp"
#include "stm32h7xx.h"
#include "stm32h7xx_hal.h"
#include "cmsis_os2.h"

void servo::initial_servo(){
    HAL_TIM_PWM_Start( _pwm, _channel);
    __HAL_TIM_SET_COMPARE( _pwm, _channel, (uint32_t)(_min_pwm + _per * _prepare_angle));
}

void servo::set_angle(bool dir)
{

    if (dir)
    {
        _delta = _target_angle - _initial_angle;
        _unit = _delta / _period;
        _current_angle = _initial_angle;

        int32_t start_pulse = _min_pwm + (_initial_angle * _per);
        int32_t target_pulse = _min_pwm + (_target_angle * _per);

        for( int i = 1 ; i <= _period ; i ++ ){
            _pulse = start_pulse + (i * (target_pulse - start_pulse) / _period);
            __HAL_TIM_SET_COMPARE(_pwm, _channel, (uint32_t)_pulse);
            osDelay(1);
        }
        _current_angle = _target_angle;
    }
    else
    {
        _delta = _initial_angle - _target_angle;
        _unit = _delta / _period;
        _current_angle = _target_angle;

        int32_t start_pulse = _min_pwm + (_target_angle * _per);
        int32_t target_pulse = _min_pwm + (_initial_angle * _per);

        for( int i = 1 ; i <= _period ; i ++ ){
            _pulse = start_pulse + (i * (target_pulse - start_pulse) / _period);
            __HAL_TIM_SET_COMPARE(_pwm, _channel, (uint32_t)_pulse);
            osDelay(1);
        }
        _current_angle = _initial_angle;
    }
}
