/*
 * ms2_config.h
 *
 *  Created on: Aug 13, 2026
 *      Author: hsuanjung
 */

#ifndef SRC_MAIN_PROGRAM_MISSION_2_MS_2_CONFIG_H_
#define SRC_MAIN_PROGRAM_MISSION_2_MS_2_CONFIG_H_

#define init_reverse_distance 1080000
#define down_reverse_distance 40000
#define rotate_distance 2700000

#define Speed_210 400

#define init_reverse_time (init_reverse_distance/Speed_210)
#define down_reverse_time (down_reverse_distance/Speed_210)
#define rotate_time (rotate_distance/Speed_210)

#endif /* SRC_MAIN_PROGRAM_MISSION_2_MS_2_CONFIG_H_ */
