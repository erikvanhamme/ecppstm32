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

#ifndef STM32F4TYPES_H
#define STM32F4TYPES_H

#ifdef stm32f4

#include "utils.h"

#include "stm32f4xx.h"

#include <cstdint>
#include <type_traits>

namespace ecpp {
    namespace stm32 {

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
    }

    template<>
    struct is_bitmask<ecpp::stm32::ahb1enr> : std::true_type {};

    template<>
    struct is_bitmask<ecpp::stm32::apb1enr> : std::true_type {};
}

#endif

#endif // STM32F4TYPES_H
