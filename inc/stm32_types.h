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
    TIMER2 = TIM2_BASE,
    TIMER3 = TIM3_BASE,
    TIMER4 = TIM4_BASE,
    TIMER5 = TIM5_BASE,
    TIMER6 = TIM6_BASE,
    TIMER7 = TIM7_BASE,
    TIMER8 = TIM8_BASE,
    TIMER9 = TIM9_BASE,
    TIMER10 = TIM10_BASE,
    TIMER11 = TIM11_BASE,
    TIMER12 = TIM12_BASE,
    TIMER13 = TIM13_BASE,
    TIMER14 = TIM14_BASE
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
