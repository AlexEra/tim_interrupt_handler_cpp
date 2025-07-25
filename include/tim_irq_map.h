#pragma once

#include <map>
#include <functional>
#include "tim.h"

namespace TimersManager {
	typedef struct {
		/**
		 * Interrupt flag (0 - no interrupt, 1 - interrupt occured)
		 */
		volatile bool irq_flag;
		/**
		 * User callback function, using within interrupt routine
		 */
		std::function<void(void)> p_irq_tim_func;
		/**
		 * User interrupt handler function, using outside 
		 * interrupt routine (task or while(1) for instance)
		 */
		std::function<void(void)> p_irq_processing;
	} tim_irq_t;

	/**
	 * @brief Method to call within interrupt handler
	 */
	void execute_callback(TIM_HandleTypeDef *p_tim);

	/**
	 * @brief Function for calling user handler function in the loop code
	 * @param timer Link to HAL timer structure
	 */
	void tim_interrupt_handler(TIM_HandleTypeDef &timer);

	/**
	 * @brief Add user callback function
	 * @param timer Link to HAL timer structure
	 * @param p_fcn Pointer or lambda to user callback function
	 */
	void add_tim_callback(
		TIM_HandleTypeDef &timer,
		std::function<void(void)> p_fcn
	);

	/**
	 * @brief Add user handler function
	 * @param timer Link to HAL timer structure
	 * @param p_fcn Pointer or lambda to user handler function
	 */
	void add_tim_handler(
		TIM_HandleTypeDef &timer,
		std::function<void(void)> p_fcn
	);
	/**
	 * @brief Starting timer interrupt mode
	 * @param timer Link to HAL timer structure
	 */
	void tim_start(TIM_HandleTypeDef &timer);

	/**
	 * @brief Stopping timer interrupt mode
	 * @param timer Link to HAL timer structure
	 */
	void tim_stop(TIM_HandleTypeDef &timer);
	/**
	 * @brief Get the interrupt flag
	 * @param timer Link to HAL timer structure
	 * @return Flag status if timer added, 0xFF otherwise
	 */
	bool get_flag(TIM_HandleTypeDef &timer);
};
