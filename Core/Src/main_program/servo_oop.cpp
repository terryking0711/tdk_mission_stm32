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

void servo::set_angle(servo servo_1, servo servo_2, bool dir)
{

    if (dir)
    {
        servo_1._delta = servo_1._target_angle - servo_1._initial_angle;
        servo_1._unit = servo_1._delta / servo_1._period;
        servo_1._current_angle = servo_1._initial_angle;

        servo_2._delta = servo_2._target_angle - servo_2._initial_angle;
        servo_2._unit = servo_2._delta / servo_2._period;
        servo_2._current_angle = servo_2._initial_angle;

        int32_t start_pulse_1 = servo_1._min_pwm + (servo_1._initial_angle * servo_1._per);
        int32_t target_pulse_1 = servo_1._min_pwm + (servo_1._target_angle * servo_1._per);

        int32_t start_pulse_2 = servo_2._min_pwm + (servo_2._initial_angle * servo_2._per);
        int32_t target_pulse_2 = servo_2._min_pwm + (servo_2._target_angle * servo_2._per);

        for( int i = 1 ; i <= _period ; i ++ ){
            servo_1._pulse = start_pulse_1 + (i * (target_pulse_1 - start_pulse_1) / servo_1._period);
            __HAL_TIM_SET_COMPARE(servo_1._pwm, servo_1._channel, (uint32_t)servo_1._pulse);
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

void servo::set_angle_sync(servo &servo_1, servo &servo_2, bool dir){

    if (dir)
    {
        servo_1._delta = servo_1._target_angle - servo_1._initial_angle;
        servo_1._unit = servo_1._delta / servo_1._period;
        servo_1._current_angle = servo_1._initial_angle;

        servo_2._delta = servo_2._target_angle - servo_2._initial_angle;
        servo_2._unit = servo_2._delta / servo_2._period;
        servo_2._current_angle = servo_2._initial_angle;

        int32_t start_pulse_1 = servo_1._min_pwm + (servo_1._initial_angle * servo_1._per);
        int32_t target_pulse_1 = servo_1._min_pwm + (servo_1._target_angle * servo_1._per);

        int32_t start_pulse_2 = servo_2._min_pwm + (servo_2._initial_angle * servo_2._per);
        int32_t target_pulse_2 = servo_2._min_pwm + (servo_2._target_angle * servo_2._per);

        for( int i = 1 ; i <= servo_1._period ; i ++ ){
            servo_1._pulse = start_pulse_1 + (i * (target_pulse_1 - start_pulse_1) / servo_1._period);
            servo_2._pulse = start_pulse_2 + (i * (target_pulse_2 - start_pulse_2) / servo_2._period);
            __HAL_TIM_SET_COMPARE(servo_1._pwm, servo_1._channel, (uint32_t)servo_1._pulse);
            __HAL_TIM_SET_COMPARE(servo_2._pwm, servo_2._channel, (uint32_t)servo_2._pulse);
            osDelay(1);
        }
        servo_1._current_angle = servo_1._target_angle;
        servo_2._current_angle = servo_2._target_angle;
    }
    else
    {
        servo_1._delta = servo_1._initial_angle - servo_1._target_angle;
        servo_1._unit = servo_1._delta / servo_1._period;
        servo_1._current_angle = servo_1._target_angle;

        servo_2._delta = servo_2._initial_angle - servo_2._target_angle;
        servo_2._unit = servo_2._delta / servo_2._period;
        servo_2._current_angle = servo_2._target_angle;

        int32_t start_pulse_1 = servo_1._min_pwm + (servo_1._target_angle * servo_1._per);
        int32_t target_pulse_1 = servo_1._min_pwm + (servo_1._initial_angle * servo_1._per);

        int32_t start_pulse_2 = servo_2._min_pwm + (servo_2._target_angle * servo_2._per);
        int32_t target_pulse_2 = servo_2._min_pwm + (servo_2._initial_angle * servo_2._per);

        for( int i = 1 ; i <= servo_1._period ; i ++ ){
            servo_1._pulse = start_pulse_1 + (i * (target_pulse_1 - start_pulse_1) / servo_1._period);
            servo_2._pulse = start_pulse_2 + (i * (target_pulse_2 - start_pulse_2) / servo_2._period);
            __HAL_TIM_SET_COMPARE(servo_1._pwm, servo_1._channel, (uint32_t)servo_1._pulse);
            __HAL_TIM_SET_COMPARE(servo_2._pwm, servo_2._channel, (uint32_t)servo_2._pulse);
            osDelay(1);
        }
        servo_1._current_angle = servo_1._initial_angle;
        servo_2._current_angle = servo_2._initial_angle;
    }
}