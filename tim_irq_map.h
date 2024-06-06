#pragma once

#include <map>
#include <stdint.h>
#include "tim.h"


typedef struct {
	void (*p_irq_tim_func) (void); // pointer to user callback function
	void (*p_irq_processing) (void); // pointer to user interrupt handler function
	volatile bool irq_flag; // interrupt flag (0 - no interrupt, 1 - interrupt occured)
} tim_irq_t;


extern std::map<TIM_HandleTypeDef*, tim_irq_t> tim_irq_service;

/**
 * @brief Function for calling user handler function in the loop code
 * @param timer Link to HAL timer structure
 */
void user_tim_handler(TIM_HandleTypeDef &timer);

/*
 * @brief Add user callback function
 * @param timer Link to HAL timer structure
 * @param p_fcn Pointer to user callback function
 * */
void add_tim_callback(TIM_HandleTypeDef &timer, void (*p_fcn) (void));

/*
 * @brief Add user handler function
 * @param timer Link to HAL timer structure
 * @param p_fcn Pointer to user handler function
 * */
void add_tim_handler(TIM_HandleTypeDef &timer, void (*p_fcn) (void));

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
