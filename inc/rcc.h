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

#ifndef RCC_H
#define RCC_H

#include "stm32types.h"

#ifdef stm32f3
#include "stm32f3types.h"

#include "stm32f3xx.h"
#endif

#ifdef stm32f4
#include "stm32f4types.h"

#include "stm32f4xx.h"
#endif

#include <cstdint>

namespace ecpp {
    namespace stm32 {
        namespace rcc {

#ifdef stm32f3
            template<ahbenr... M>
            static void enableClock() {
                RCC->AHBENR |= ahbenr_mask<M...>::value;
            }

            template<ahbenr... M>
            static void disableClock() {
                RCC->AHBENR &= ~ahbenr_mask<M...>::value;
            }
#endif

#ifdef stm32f4
            static void enableClock(ahb1enr clocks) {
                RCC->AHB1ENR |= static_cast<std::uint32_t>(clocks);
            }

            static void disableClock(ahb1enr clocks) {
                RCC->AHB1ENR &= ~static_cast<std::uint32_t>(clocks);
            }

            static void enableClock(apb1enr clocks) {
                RCC->APB1ENR |= static_cast<std::uint32_t>(clocks);
            }

            static void disableClock(apb1enr clocks) {
                RCC->APB1ENR &= ~static_cast<std::uint32_t>(clocks);
            }
#endif
        }
    }
}
#endif // RCC_H
