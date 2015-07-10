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

#ifndef BASICTIMER_H
#define BASICTIMER_H

#include "rcc.h"

#ifdef stm32f4
#include "stm32f4types.h"

#include "stm32f4xx.h"
#endif

namespace ecpp {
    namespace stm32 {

        template<basictimer T>
        class BasicTimer {
        public:

            static void enable() {
                switch (T) {
                case basictimer::tim6:
                    rcc::enableClock<apb1enr::tim6>();
                    break;
                case basictimer::tim7:
                    rcc::enableClock<apb1enr::tim7>();
                    break;
                }
            }

            static void disable() {
                switch (T) {
                case basictimer::tim6:
                    rcc::disableClock<apb1enr::tim6>();
                    break;
                case basictimer::tim7:
                    rcc::disableClock<apb1enr::tim7>();
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

            // TODO: find templated way to do this. (More interrupt types)
            static void setUpdateInterruptEvent(bool enabled) {
                if (enabled == true) {
                    _timer->DIER |= TIM_DIER_UIE;
                } else {
                    _timer->DIER &= ~TIM_DIER_UIE;
                }
            }

            // TODO: find templated way to do this. (More interrupt types)
            static bool isUpdateInterruptFlag() {
                return (_timer->SR & TIM_SR_UIF);
            }

            // TODO: find templated way to do this. (More interrupt types)
            static void clearUpdateInterruptFlag() {
                _timer->SR &= ~TIM_SR_UIF;
            }

            static void setUpdateDmaEvent(bool enabled) {
                if (enabled == true) {
                    _timer->DIER |= TIM_DIER_UDE;
                } else {
                    _timer->DIER &= ~TIM_DIER_UDE;
                }
            }

            static void setPeriodBuffered(bool enabled) {
                if (enabled == true) {
                    _timer->CR1 |= TIM_CR1_ARPE;
                } else {
                    _timer->CR1 &= ~TIM_CR1_ARPE;
                }
            }

        private:
            static constexpr TIM_TypeDef *_timer = reinterpret_cast<TIM_TypeDef *>(T);

            BasicTimer() = delete;
        };
    }
}

#endif // BASICTIMER_H
