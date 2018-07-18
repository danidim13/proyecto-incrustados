/*
 * main.hpp
 *
 *  Created on: Aug 31, 2016
 *      Author: eortiz
 */

#ifndef MAIN_HPP_
#define MAIN_HPP_
//#define TIMER32_COUNT 0x0000BB80  // ~1ms with 48 MHz clock
#define TIMER32_COUNT 0x00002EE0  // 0.25ms with 48 MHz clock

// The main Setup function for the application
void Setup(void);

#endif /* MAIN_HPP_ */
