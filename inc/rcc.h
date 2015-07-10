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

#include "utils.h"

#ifdef stm32f3
#include "stm32f3xx.h"
#endif

#ifdef stm32f4
#include "stm32f4xx.h"
#endif

#include <cstdint>

namespace ecpp {
    namespace stm32 {

#ifdef stm32f3
        enum class ahbenr : std::uint32_t {
            gpioa = RCC_AHBENR_GPIOAEN,
            gpiob = RCC_AHBENR_GPIOBEN,
            gpioc = RCC_AHBENR_GPIOCEN,
            gpiod = RCC_AHBENR_GPIODEN,
            gpioe = RCC_AHBENR_GPIOEEN,
            gpiof = RCC_AHBENR_GPIOFEN,
            // TODO: add other peripheral bits
        };

#endif

#ifdef stm32f4
        enum class ahb1enr : std::uint32_t {
            gpioa = RCC_AHB1ENR_GPIOAEN,
            gpiob = RCC_AHB1ENR_GPIOBEN,
            gpioc = RCC_AHB1ENR_GPIOCEN,
            gpiod = RCC_AHB1ENR_GPIODEN,
            gpioe = RCC_AHB1ENR_GPIOEEN,
            gpiof = RCC_AHB1ENR_GPIOFEN,
            gpiog = RCC_AHB1ENR_GPIOGEN,
            gpioh = RCC_AHB1ENR_GPIOHEN,
            gpioi = RCC_AHB1ENR_GPIOIEN
            // TODO: add other peripheral bits
        };

        enum class apb1enr : std::uint32_t {
            tim6 = RCC_APB1ENR_TIM6EN,
            tim7 = RCC_APB1ENR_TIM7EN
            // TODO: add other peripheral bits
        };
#endif

        namespace rcc {

#ifdef stm32f3
            static void enableClock(ahbenr clocks) {
                RCC->AHBENR |= static_cast<std::uint32_t>(clocks);
            }

            static void disableClock(ahbenr clocks) {
                RCC->AHBENR &= ~static_cast<std::uint32_t>(clocks);
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

#ifdef stm32f3
    template<>
    struct is_bitmask<ecpp::stm32::ahbenr> : std::true_type {};

#endif

#ifdef stm32f4
    template<>
    struct is_bitmask<ecpp::stm32::ahb1enr> : std::true_type {};

    template<>
    struct is_bitmask<ecpp::stm32::apb1enr> : std::true_type {};

#endif
}
#endif // RCC_H
