#include "tim_irq_map.h"


std::map<TIM_HandleTypeDef*, tim_irq_t> tim_irq_service;


void user_tim_handler(TIM_HandleTypeDef &timer) {
	if (tim_irq_service[&timer].irq_flag) {
		tim_irq_service[&timer].irq_flag = false;
		tim_irq_service[&timer].p_irq_processing();
	}
}

void add_tim_callback(TIM_HandleTypeDef &timer, void (*p_fcn) (void)) {
	tim_irq_service[&timer].p_irq_tim_func = p_fcn;
}

void add_tim_handler(TIM_HandleTypeDef &timer, void (*p_fcn) (void)) {
	tim_irq_service[&timer].p_irq_processing = p_fcn;
}

void tim_start(TIM_HandleTypeDef &timer) {
	__HAL_TIM_SET_COUNTER(&timer, 0);
	__HAL_TIM_CLEAR_FLAG(&timer, TIM_FLAG_UPDATE);
	HAL_TIM_Base_Start_IT(&timer);
}

void tim_stop(TIM_HandleTypeDef &timer) {
	HAL_TIM_Base_Stop_IT(&timer);
}

bool get_flag(TIM_HandleTypeDef &timer) {
	return tim_irq_service[&timer].irq_flag;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	tim_irq_service[htim].irq_flag = true;
	tim_irq_service[htim].p_irq_tim_func();
}
