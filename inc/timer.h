/*
 * Copyright 2015 Erik Van Hamme
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TIMER_H
#define TIMER_H

#include "rcc.h"
#include "stm32_types.h"
#include "stm32_traits.h"

#ifdef stm32f3
#include "stm32f3xx.h"
#endif

#ifdef stm32f4
#include "stm32f4xx.h"
#endif

#include <cstdint>

namespace ecpp {
namespace stm32 {

template<Timer_e T>
class Timer final {
public:

    static_assert(is_advanced_control<T>::value || is_general_purpose<T>::value || is_basic<T>::value, "Unsupported timer specified.");

    static void enable() {
        switch (T) {
        case Timer_e::TIMER6:
            rcc::enableClock(apb1enr::tim6);
            break;
        case Timer_e::TIMER7:
            rcc::enableClock(apb1enr::tim7);
            break;
        }
    }

    static void disable() {
        switch (T) {
        case Timer_e::TIMER6:
            rcc::disableClock(apb1enr::tim6);
            break;
        case Timer_e::TIMER7:
            rcc::disableClock(apb1enr::tim7);
            break;
        }
    }

    static void start() {
        _timer->CR1 |= TIM_CR1_CEN;
    }

    static void stop() {
        _timer->CR2 &= ~TIM_CR1_CEN;
    }

    static void configure(unsigned int period, unsigned int prescaler = 0) {
        _timer->ARR = static_cast<std::uint32_t>(period) & 0xffff;
        _timer->PSC = static_cast<std::uint32_t>(prescaler) & 0xffff;
    }

    static void updatePeriod(unsigned int period) {
        _timer->ARR = static_cast<std::uint32_t>(period) & 0xffff;
    }

    static void generateUpdateEvent() {
        _timer->EGR = TIM_EGR_UG;
    }

    // TODO: Find good way to handle this.
    static void setPeriodBuffered(bool enabled) {
        if (enabled == true) {
            _timer->CR1 |= TIM_CR1_ARPE;
        } else {
            _timer->CR1 &= ~TIM_CR1_ARPE;
        }
    }

    template<TimerIrq_e irq>
    static void enableIrq() {
        static_assert((irq & ~_irq) == 0, "Irq passed which is not supported by this timer type.");
        _timer->DIER |= static_cast<std::uint32_t>(irq);
    }

    template<TimerIrq_e irq>
    static void disableIrq() {
        static_assert((irq & ~_irq) == 0, "Irq passed which is not supported by this timer type.");
        _timer->DIER &= ~static_cast<std::uint32_t>(irq);
    }

    template<TimerFlag_e flag>
    static bool isSet() {
        return _timer->SR & static_cast<std::uint32_t>(flag);
    }

    template<TimerFlag_e flag>
    static void clear() {
        _timer->SR &= ~static_cast<std::uint32_t>(flag);
    }

    template<TimerDmarq_e dmarq>
    static void enableDmarq() {
        static_assert((dmarq & ~_dmarq) == 0, "Dmarq passed which is not supported by this timer type.");
        _timer->DIER |= static_cast<std::uint32_t>(dmarq);
    }

    template<TimerDmarq_e dmarq>
    static void disableDmarq() {
        static_assert((dmarq & ~_dmarq) == 0, "Dmarq passed which is not supported by this timer type.");
        _timer->DIER &= ~static_cast<std::uint32_t>(dmarq);
    }

private:
    static constexpr TIM_TypeDef *_timer = reinterpret_cast<TIM_TypeDef *>(T);

    // TODO: Complete allowed irq's.
    static constexpr TimerIrq_e _irq_basic = TimerIrq_e::UPDATE;
    static constexpr TimerIrq_e _irq_general_purpose = _irq_basic | TimerIrq_e::TRIGGER;
    static constexpr TimerIrq_e _irq_advanced_control = _irq_general_purpose;

    static constexpr TimerIrq_e _irq = is_advanced_control<T>::value ? _irq_advanced_control :
                                        is_general_purpose<T>::value ? _irq_general_purpose :
                                        _irq_basic;

    // TODO: Complete allowed dmarq's.
    static constexpr TimerDmarq_e _dmarq_basic = TimerDmarq_e::UPDATE;
    static constexpr TimerDmarq_e _dmarq_general_purpose = _dmarq_basic | TimerDmarq_e::TRIGGER;
    static constexpr TimerDmarq_e _dmarq_advanced_control = _dmarq_general_purpose;

    static constexpr TimerDmarq_e _dmarq = is_dmarq_capable<T>::value ?
                is_advanced_control<T>::value ? _dmarq_advanced_control :
                is_general_purpose<T>::value ? _dmarq_general_purpose :
                _dmarq_basic : TimerDmarq_e(0);


    Timer() = delete;
};
} // end of ecpp::stm32
} // end of ecpp

#endif // TIMER_H
