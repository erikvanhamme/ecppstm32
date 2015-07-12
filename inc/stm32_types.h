#ifndef STM32_TYPES_H
#define STM32_TYPES_H

#ifdef stm32f3
#include "stm32f3xx.h"
#endif

#ifdef stm32f4
#include "stm32f4xx.h"
#endif

#include <cstdint>

namespace ecpp {
namespace stm32 {

// TODO: Figure out if the enums should subclass std::uint32_t.

enum class Timer_e : std::uint32_t {
    TIMER1 = TIM1_BASE,
    // TODO: Add other timers.
    TIMER6 = TIM6_BASE,
    TIMER7 = TIM7_BASE,
    TIMER8 = TIM8_BASE,
    // TODO: Add other timers.
};

enum class TimerIrq_e : std::uint32_t {
    UPDATE = TIM_DIER_UIE,
    TRIGGER = TIM_DIER_TIE,
    // TODO: complete
};

enum class TimerDmarq_e : std::uint32_t {
    UPDATE = TIM_DIER_UDE,
    TRIGGER = TIM_DIER_TDE,
    // TODO: complete
};

enum class TimerFlag_e : std::uint32_t {
    UPDATE = TIM_SR_UIF,
    TRIGGER = TIM_SR_TIF,
    // TODO: complete
};

} // end of ecpp::stm32
} // end of ecpp

#endif // STM32_TYPES_H
