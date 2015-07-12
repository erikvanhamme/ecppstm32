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

#ifdef stm32f3
#include "stm32f3xx.h"
#endif

#ifdef stm32f4
#include "stm32f4xx.h"
#endif

#include <cstdint>
#include <type_traits>

namespace ecpp {
    namespace stm32 {
        namespace irqen {

            enum class timer_basic_e {
                update = TIM_DIER_UIE,
            };

            enum class timer_general_purpose_e {
                update = TIM_DIER_UIE,
                // TODO: Add other interrupts supported by GP timer.
            };

            enum class timer_advanced_control_e {
                update = TIM_DIER_UIE,
                // TODO: add other interrupts supported by AC timer.
            };
        }

        namespace irqflag {

            enum class timer_basic_e {
                update = TIM_SR_UIF,
            };

            enum class timer_general_purpose_e {
                update = TIM_SR_UIF,
            };

            enum class timer_advanced_control_e {
                update = TIM_SR_UIF,
            };
        }

        enum class timer_e : std::uint32_t {
            tim1 = TIM1_BASE,
            // TODO: Add other timers.
            tim6 = TIM6_BASE,
            tim7 = TIM7_BASE,
            tim8 = TIM8_BASE,
            // TODO: Add other timers.
        };

        template<timer_e>
        struct is_basic : std::false_type {};

        template<>
        struct is_basic<timer_e::tim6> : std::true_type {};

        template<>
        struct is_basic<timer_e::tim7> : std::true_type {};

        template<timer_e>
        struct is_general_purpose : std::false_type {};

        // TODO: Add type traits for general purpose timers.

        template<timer_e>
        struct is_advanced_control : std::false_type {};

        // TODO: Add type traits for advanced control timers.

        template<timer_e T>
        class Timer {
        public:

            static_assert(is_basic<T>::value || is_general_purpose<T>::value || is_advanced_control<T>::value, "Unsupported timer.");

            /* This conditionally defines irqen_e to be:
             *      irqen::timer_advanced_control_e   if is_advanced_control<T>::value   == true;
             *      irqen::timer_general_purpose_e    if is_general_purpose<T>::value    == true;
             *      irqen::timer_basic_e              if is_basic<T>::value              == true;
             */
            typedef
                typename std::conditional<is_advanced_control<T>::value, irqen::timer_advanced_control_e,
                    typename std::conditional<is_general_purpose<T>::value, irqen::timer_general_purpose_e, irqen::timer_basic_e
                    >::type
                >::type
            irqen_e;

            /* This conditionally defines irqflag_e to be:
             *      irqflag::timer_advanced_control_e   if is_advanced_control<T>::value   == true;
             *      irqflag::timer_general_purpose_e    if is_general_purpose<T>::value    == true;
             *      irqflag::timer_basic_e              if is_basic<T>::value              == true;
             */
            typedef
                typename std::conditional<is_advanced_control<T>::value, irqflag::timer_advanced_control_e,
                    typename std::conditional<is_general_purpose<T>::value, irqflag::timer_general_purpose_e, irqflag::timer_basic_e
                    >::type
                >::type
            irqflag_e;

            static void enable() {
                switch (T) {
                case timer_e::tim6:
                    rcc::enableClock(apb1enr::tim6);
                    break;
                case timer_e::tim7:
                    rcc::enableClock(apb1enr::tim7);
                    break;
                }
            }

            static void disable() {
                switch (T) {
                case timer_e::tim6:
                    rcc::disableClock(apb1enr::tim6);
                    break;
                case timer_e::tim7:
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

            // TODO: handle this the same way as the irq's.
            static void setUpdateDmaEvent(bool enabled) {
                if (enabled == true) {
                    _timer->DIER |= TIM_DIER_UDE;
                } else {
                    _timer->DIER &= ~TIM_DIER_UDE;
                }
            }

            // TODO: Find good way to handle this.
            static void setPeriodBuffered(bool enabled) {
                if (enabled == true) {
                    _timer->CR1 |= TIM_CR1_ARPE;
                } else {
                    _timer->CR1 &= ~TIM_CR1_ARPE;
                }
            }

            static void enableIrq(irqen_e irq) {
                _timer->DIER |= static_cast<std::uint32_t>(irq);
            }

            static void disableIrq(irqen_e irq) {
                _timer->DIER &= ~static_cast<std::uint32_t>(irq);
            }

            static bool isSet(irqflag_e irqflag) {
                return _timer->SR & static_cast<std::uint32_t>(irqflag);
            }

            static void clear(irqflag_e irqflag) {
                _timer->SR &= ~static_cast<std::uint32_t>(irqflag);
            }

        private:
            static constexpr TIM_TypeDef *_timer = reinterpret_cast<TIM_TypeDef *>(T);

            Timer() = delete;
        };
    }

    template<>
    struct is_bitmask<ecpp::stm32::irqen::timer_basic_e> : std::true_type {};
}

#endif // TIMER_H
