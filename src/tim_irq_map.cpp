#include "tim_irq_map.h"


namespace TimersManager {
	std::map<TIM_HandleTypeDef*, tim_irq_t> timers_callbacks;
	void tim_interrupt_handler(TIM_HandleTypeDef &timer) {
		if (
			timers_callbacks[&timer].irq_flag
			&& timers_callbacks[&timer].p_irq_processing != nullptr
		) {
			timers_callbacks[&timer].irq_flag = false;
			timers_callbacks[&timer].p_irq_processing();
		}
	}
	void add_tim_callback(
		TIM_HandleTypeDef &timer,
		std::function<void(void)> p_fcn
	) {
		timers_callbacks[&timer].p_irq_tim_func = p_fcn;
	}

	void add_tim_handler(
		TIM_HandleTypeDef &timer,
		std::function<void(void)> p_fcn
	) {
		timers_callbacks[&timer].p_irq_processing = p_fcn;
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
		return timers_callbacks[&timer].irq_flag;
	}

	void execute_callback(TIM_HandleTypeDef *p_tim) {
		timers_callbacks[p_tim].irq_flag = true;
		if (timers_callbacks[p_tim].p_irq_tim_func != nullptr) {
			timers_callbacks[p_tim].p_irq_tim_func();
		}
	}
};

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	TimersManager::execute_callback(htim);
}
