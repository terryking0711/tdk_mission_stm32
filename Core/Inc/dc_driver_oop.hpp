/*
 * dc_driver_oop.hpp
 *
 *  Created on: Jul 29, 2026
 *      Author: hsuanjung
 */

#ifndef INC_DC_DRIVER_OOP_HPP_
#define INC_DC_DRIVER_OOP_HPP_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32h7xx_hal.h"
#include "stm32h7xx.h"
#include "stm32h7xx_it.h"
#include "stm32h723xx.h"

#include <stdbool.h>

class dc_driver
{
public:
    dc_driver(TIM_HandleTypeDef *pwm, uint32_t channel, GPIO_TypeDef *dir_gpio, uint16_t dir_pin, uint16_t period, int speed)
    :_pwm(pwm), _channel(channel), _dir_gpio(dir_gpio), _dir_pin(dir_pin), _period(period), _speed(speed) {}
    ~dc_driver() = default;

    bool init_dc_driver(); //Start PWM mode
    void stop();
    bool cw();
    bool ccw();

private:
    TIM_HandleTypeDef *_pwm;
    uint32_t _channel;
    GPIO_TypeDef *_dir_gpio;
    uint16_t _dir_pin;
    uint16_t _period; 
    int _speed;
    uint32_t _current_pwm;
    uint32_t _target_pwm;
    int32_t _diff_pwm;
    uint32_t _step_pwm;
};

#ifdef __cplusplus
}
#endif



#endif /* INC_DC_DRIVER_OOP_HPP_ */
